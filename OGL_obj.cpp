#pragma hdrstop
#pragma argsused

#include <tchar.h>
#include <stdio.h>
#include <conio.h>
#include <iostream.h>
#include <fstream.h>
#include <sstream>
#include <cstring>
#include <string.h>
#include <vector>
#include <windows.h>
#include "glut.h"
#include "glaux.h"



struct POINT_P
{
  float XX, YY, ZZ;
}
vertex;

vector < POINT_P > points;
vector < int > v;
struct POLYGON
{
	vector < POINT_P > points;
};

struct MODEL
{
	vector < POLYGON > POLYGONS;
};

MODEL Load_obj;

void IDLE()
{
	glutPostRedisplay();
}
void DrawObj(MODEL Model)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	for (int P=0; P<Model.POLYGONS.size(); P++)
	{
		glBegin(GL_POLYGON);
		for (int V=0; V< Model.POLYGONS[P].points.size(); V++)
		{
			glVertex3f(Model.POLYGONS[P].points[V].XX,
					   Model.POLYGONS[P].points[V].YY,
					   Model.POLYGONS[P].points[V].ZZ);
		}
		glEnd();
	}
}
void Display()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DrawObj(Load_obj);
	glPointSize(4);
	glBegin(GL_POINTS);
	for (int i=0; i<points.size(); i++)
	{
		glVertex3f(points[i].XX, points[i].YY, points[i].ZZ);
	}
	glEnd();
	glutSwapBuffers();
}


void parser(std::string LINE)
{
 v.clear();
 int v_buf=0;
  int param=0;
  string pars_to_point="";
  int Line_length=LINE.size();
  cout << LINE.c_str() << "\n";
  for (int i = 2; i <Line_length; i++)
  {
	if (LINE[i]==' ')
	{
		cout << " index point " << v_buf;
		param=0;
		pars_to_point="";
		if (v_buf !=0) v.push_back(v_buf-1);
	}
	if (LINE[i]=='/')
	{
		param++;
		cout << "\n" << param << " New param ";
		pars_to_point="";
	}
	if ((LINE[i]!='/')&&(LINE[i]!=' '))
	{
		pars_to_point+=LINE[i];
	}
	switch (param)
	{
		case 0: cout << " point " << sscanf(pars_to_point.c_str(), "%i", &v_buf); break;
		case 1: cout << " texture " << sscanf(pars_to_point.c_str(), "%i", &v_buf); break;
		case 2: cout << " normal " << sscanf(pars_to_point.c_str(), "%i", &v_buf); break;
    }
  }
  cout << "\n ";
}


void read_file(char* name)
{
  std::string Read_line;
  fstream file;
  file.open(name, ios::in);
  if (file.is_open())
  {
	  while (!file.eof())
	  {
		  getline(file, Read_line);

		  if (Read_line[0]=='v')
		  {
			 cout << "Coord ";
			  if(Read_line[1]==' ')
			  {
				cout << "point ";
				Read_line[0]=' ';
				Read_line[1]=' ';


				sscanf(Read_line.c_str(), "%f %f %f ", &vertex.XX,&vertex.YY,&vertex.ZZ);

				points.push_back(vertex);

			  }
			  if(Read_line[1]=='t')  cout << "texture ";
			  if(Read_line[1]=='n') 	cout << "normal ";

			  if (Read_line[0]=='f') cout << "Polygon \n " << Read_line.c_str() << "\n ";
		  }
		  if (Read_line[0]=='f')
		  {

			  parser(Read_line);
			  vector < POINT_P > tmp_point;
			  tmp_point.clear();
			  for (int i=0; i< v.size(); i++)

				  tmp_point.push_back(points[v[i]]);

			  POLYGON tmp_polygon;
			  for (int i=0; i< tmp_point.size(); i++)

				  tmp_polygon.points.push_back(tmp_point[i]);

			  Load_obj.POLYGONS.push_back(tmp_polygon);
		  }

		  for (int i = 0; i < Read_line.length(); i++)

			cout << Read_line[i];

		  cout << "\n"   ;
	  }
  }
}




void init_OpenGL()
{
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutInitWindowSize(640, 480);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Game");
  glutDisplayFunc(Display);
  glutIdleFunc(IDLE);
  glutMainLoop();
}




int _tmain(int argc, _TCHAR* argv[])
{
  // read_file("cube_tringle_texture_normal.obj");
   cout << "\n";
   read_file("cube_tringle.obj");
   for (int i =0; i < points.size(); i++)
   {
	 cout << i;
	 cout << "\tX ";
	 cout << points[i].XX;
	 cout << "\tY ";
	 cout << points[i].YY;
	 cout << "\tZ ";
	 cout << points[i].ZZ;
	 cout << "\n";
   }

   init_OpenGL();

	return 0;
}
