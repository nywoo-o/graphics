// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <Windows.h>
#include <time.h>
// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>

#include <glut.h>


std::vector<GLfloat> makeConeVertices(vec3 center, GLfloat radius, GLint numTriangle);
void drawObject(GLuint MatrixID, mat4 MVP, GLuint vertexbuffer, GLuint colorbuffer, GLenum mode, int arrsz);

int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "Tutorial 0 - Keyboard and Mouse", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
    glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited mouvement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Set the mouse at the center of the screen
    glfwPollEvents();
    glfwSetCursorPos(window, 1024/2, 768/2);

	// Dark blue background
	glClearColor(0.3f, 0.5f, 1.0f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader" );

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	
	// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	//뚜껑
	std::vector<GLfloat> vertex_buffer_vector = makeConeVertices(vec3(0, 0, 0), 1, 36);
	static const GLfloat g_color_buffer_data[] = {
		0.8f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f

		 };
	
	//땅
	static const GLfloat g_ground_buffer_data[] = {
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, -1.0f,
		-1.0f, 0.0f, -1.0f,
		-1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		-1.0f, 0.0f, -1.0f,
	};
	static const GLfloat g_ground_color_buffer_data[] = {
		0.38f, 0.19f, 0.0f,
		0.38f, 0.19f, 0.0f,
		0.38f, 0.19f, 0.0f,
		0.38f, 0.19f, 0.0f,
		0.38f, 0.19f, 0.0f,
		0.38f, 0.19f, 0.0f,
	};

	//로켓 날개
	static const GLfloat g_rocket_wing_buffer_data[] = {
		-1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f
	};
	static const GLfloat g_rocket_wing_color_buffer_data[] = {
		0.7f, 0.7f, 0.0f,
		0.7f, 0.7f, 0.0f,
		1.0f, 1.0f, 0.0f
	};

	//로켓 몸통
	static const GLfloat g_rocket_body_buffer_data[] = {
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,

		1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,

		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,

		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,

		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,

		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,

		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,

		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,

		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,

		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,

		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,

		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};
	static const GLfloat g_rocket_body_color_buffer_data[] = {
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f
	};
	
	//낙하산
	static const GLfloat g_parachute_buffer_data[] = {
		0.0f, 2.0f, 0.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, -1.0f,
		-1.0f, 0.0f, -1.0f,
		-1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
	};
	static const GLfloat g_parachute_color_buffer_data[] = {
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};

	//낙하산 끈
	static const GLfloat g_para_body_buffer_data[] = {
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,

		1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,

		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,

		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,

		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,

		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,

		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,

		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,

		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,

		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,

		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,

		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};
	static const GLfloat g_para_body_color_buffer_data[] = {
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f

	};

	//게이지 바
	static const GLfloat g_gauge_body_buffer_data[] = {
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,

		1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,

		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,

		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,

		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,

		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,

		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,

		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,

		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,

		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,

		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,

		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};
	static const GLfloat g_gauge_body_color_buffer_data[] = {
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f,
		0.6f, 0.2f, 1.0f
	};

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*vertex_buffer_vector.size(), &vertex_buffer_vector[0], GL_STATIC_DRAW);

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);


	//땅
	GLuint groundbuffer;
	glGenBuffers(1, &groundbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, groundbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_ground_buffer_data), g_ground_buffer_data, GL_STATIC_DRAW);
	GLuint groundcolorbuffer;
	glGenBuffers(1, &groundcolorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, groundcolorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_ground_color_buffer_data), g_ground_color_buffer_data, GL_STATIC_DRAW);

	//로켓 날개
	GLuint rocket_wing_buffer;
	glGenBuffers(1, &rocket_wing_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, rocket_wing_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_rocket_wing_buffer_data), g_rocket_wing_buffer_data, GL_STATIC_DRAW);
	GLuint rocket_wing_colorbuffer;
	glGenBuffers(1, &rocket_wing_colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, rocket_wing_colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_rocket_wing_color_buffer_data), g_rocket_wing_color_buffer_data, GL_STATIC_DRAW);

	//로켓 몸통
	GLuint rocket_body_buffer;
	glGenBuffers(1, &rocket_body_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, rocket_body_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_rocket_body_buffer_data), g_rocket_body_buffer_data, GL_STATIC_DRAW);
	GLuint rocket_body_colorbuffer;
	glGenBuffers(1, &rocket_body_colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, rocket_body_colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_rocket_body_color_buffer_data), g_rocket_body_color_buffer_data, GL_STATIC_DRAW);

	//낙하산
	GLuint parachute_buffer;
	glGenBuffers(1, &parachute_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, parachute_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_parachute_buffer_data), g_parachute_buffer_data, GL_STATIC_DRAW);
	GLuint parachute_colorbuffer;
	glGenBuffers(1, &parachute_colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, parachute_colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_parachute_color_buffer_data), g_parachute_color_buffer_data, GL_STATIC_DRAW);

	//낙하산 끈
	GLuint para_buffer;
	glGenBuffers(1, &para_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, para_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_para_body_buffer_data), g_para_body_buffer_data, GL_STATIC_DRAW);
	GLuint para_colorbuffer;
	glGenBuffers(1, &para_colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, para_colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_para_body_color_buffer_data), g_para_body_color_buffer_data, GL_STATIC_DRAW);

	//게이지 바
	GLuint gauge_buffer;
	glGenBuffers(1, &gauge_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, gauge_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_gauge_body_buffer_data), g_gauge_body_buffer_data, GL_STATIC_DRAW);
	GLuint gauge_colorbuffer;
	glGenBuffers(1, &gauge_colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, gauge_colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_gauge_body_color_buffer_data), g_gauge_body_color_buffer_data, GL_STATIC_DRAW);

	double Radius = 0.0f;
	float PI = 3.141592f;
	float theta = 0.0f;
	float add = 0.0f;
	int space_end = 0, para_start = 0;
	vec3 gPosition1(-Radius, 0.0f, 0.0f);

	do{
		//space bar가 눌리는 상태인지 체크
		//눌렸던 적이 있고(Radius > 0.0f) 더이상 눌리지 않으면 space_end = 1로 해서 발사를 시작함
		if (GetAsyncKeyState(VK_SPACE) & 0X8000 && theta == 0.0f) {
			Radius += 0.02f;	
		}
		else if (Radius > 0.0f && space_end == 0) { //if Radius > 0 and space key isn't pushed anymore then start rocket
			space_end = 1;
			printf("%lf\n", Radius);
		}

		//Radius가 5.0이상이고 theta가 0.7f이상이면 낙하산을 펼친다.
		if (Radius > 5.0f && theta > 0.7f) para_start = 1;
		
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		// Compute the MVP matrix from keyboard and mouse input
		computeMatricesFromInputs();
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		
		//로켓 뚜껑
		gPosition1.x = -Radius;
		glm::mat4 TranslationMatrix1 = translate(mat4(), gPosition1);
		glm::mat4 RotationMatrix1 = rotate(mat4(), theta*PI, vec3(0.0f, 0.0f, -1.0f)); 
		glm::mat4 ScalingMatrix1 = scale(mat4(), vec3(0.8f, 1.2f, 0.8f));
		glm::mat4 TranslationMatrix2 = translate(mat4(), vec3(Radius, 0.0f, 0.0f));
		glm::mat4  Model = glm::mat4(1.0f);
		Model = Model * TranslationMatrix2 * RotationMatrix1 * TranslationMatrix1 * ScalingMatrix1;
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * Model;

		//로켓 원형으로 움직이기 , 낙하산이 펴지면 각도가 더 느리게 증가함
		if (theta < 1.0f && add < 1.0f && Radius >= 1.0f && space_end) {
			add += (0.0005f + pow(add - 0.5, 8))*(!para_start) + (0.0002f + pow(add - 0.5, 16))*para_start;
			if (add < 0.5f) {
				theta = 0.5 * sin(PI*add);
			}
			else {
				theta = 0.5 * sin((1.0 + add)*PI) + 1.0;
			}
		}

		//땅!!
		glm::mat4 TranslationMatrix3 = translate(mat4(), vec3(0.0f, -1.0f, 0.0f));
		glm::mat4 ScalingMatrix2 = scale(mat4(), vec3(100000.0f, 0.0f, 100000.0f));
		glm::mat4 Ground = glm::mat4(1.0f);
		Ground = Ground * TranslationMatrix3 * ScalingMatrix2;
		glm::mat4 MVP2 = ProjectionMatrix * ViewMatrix * Ground;

		//로켓 날개
		glm::mat4 ScalingMatrix_rocket_wing = scale(mat4(), vec3(2.0f, 2.0f, 1.0f));
		glm::mat4 RocketWing = glm::mat4(1.0f);
		RocketWing = RocketWing * TranslationMatrix2 * RotationMatrix1 * TranslationMatrix1 * ScalingMatrix_rocket_wing;
		glm::mat4 MVP3 = ProjectionMatrix *ViewMatrix * RocketWing;

		//로켓 몸통
		glm::mat4 ScalingMatrix_rocket_body = scale(mat4(), vec3(0.8f, 1.3f, 0.8f));
		glm::mat4 RocketBody = glm::mat4(1.0f);
		RocketBody = RocketBody * TranslationMatrix2 * RotationMatrix1 * TranslationMatrix1 * ScalingMatrix_rocket_body;
		glm::mat4 MVP4 = ProjectionMatrix * ViewMatrix * RocketBody;

		//낙하산 
		glm::mat4 Rotation_para = rotate(mat4(), PI, vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 Translation_para = translate(mat4(), vec3(-Radius, -3.5f, 0.0f));
		glm::mat4 ScalingMatrix_parachute = scale(mat4(), vec3(2.0f, 1.0f, 2.0f));
		glm::mat4 Parachute = glm::mat4(1.0f);
		Parachute = Parachute * TranslationMatrix2 * RotationMatrix1 * Translation_para * ScalingMatrix_parachute * Rotation_para;
		glm::mat4 MVP5 = ProjectionMatrix * ViewMatrix * Parachute;

		//낙하산 끈
		glm::mat4 Translation_parac = translate(mat4(), vec3(-Radius, -3.0f, 0.0f));
		glm::mat4 ScalingMatrix_para = scale(mat4(), vec3(0.1f, 2.0f, 0.1f));
		glm::mat4 Parachute_body = glm::mat4(1.0f);
		Parachute_body = Parachute_body * TranslationMatrix2 * RotationMatrix1 * Translation_parac * ScalingMatrix_para;
		glm::mat4 MVP6 = ProjectionMatrix * ViewMatrix * Parachute_body;

		//게이지바
		glm::mat4 Translation_gauge = translate(mat4(), vec3(-5.0f, 0.0f, 0.0f));
		glm::mat4 ScalingMatrix_gauge = scale(mat4(), vec3(0.5f, 1.0f*Radius, 0.5f));
		glm::mat4 Gauge = glm::mat4(1.0f);
		Gauge = Gauge * Translation_gauge * ScalingMatrix_gauge;
		glm::mat4 MVP7 = ProjectionMatrix * ViewMatrix * Gauge;

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		//로켓 뚜껑 그리기
		drawObject(MatrixID, MVP, vertexbuffer, colorbuffer, GL_TRIANGLE_FAN, vertex_buffer_vector.size());

		//땅 그리기
		drawObject(MatrixID, MVP2, groundbuffer, groundcolorbuffer, GL_TRIANGLES, 6 * 3);

		//날개그리기
		drawObject(MatrixID, MVP3, rocket_wing_buffer, rocket_wing_colorbuffer, GL_TRIANGLES, 3 * 3);

		//로켓몸통 그리기
		drawObject(MatrixID, MVP4, rocket_body_buffer, rocket_body_colorbuffer, GL_TRIANGLES, 12 * 3 );

		//낙하산 그리기
		if (para_start) {
			drawObject(MatrixID, MVP5, parachute_buffer, parachute_colorbuffer, GL_TRIANGLE_FAN, 6 * 3);
			drawObject(MatrixID, MVP6, para_buffer, para_colorbuffer, GL_TRIANGLES, 12 * 3);
		}

		//게이지 바
		drawObject(MatrixID, MVP7, gauge_buffer, gauge_colorbuffer, GL_TRIANGLES, 12 * 3);
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &colorbuffer);
	glDeleteProgram(programID);
	//glDeleteTextures(1, &TextureID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}


std::vector<GLfloat> makeConeVertices(vec3 center, GLfloat radius, GLint numTriangle) {
	std::vector<vec3> coneVectors;
	//push circle's center
	vec3 tmpcenter = center;
	tmpcenter.y += 3;
	coneVectors.push_back(tmpcenter);

	//vertices = size + 1
	for (int i = 0; i < numTriangle + 1; ++i) {
		const GLfloat DOUBLE_PI = 2.0f * 3.141592f;
		float relativeI = (float)i / (float)numTriangle;
		float x = center.x + (radius * cos(relativeI * DOUBLE_PI));
		float y = center.y;
		float z = center.z + (radius * sin(relativeI * DOUBLE_PI));
		coneVectors.push_back(vec3(x, y, z));
	}

	//need to transform the type opengl wants
	std::vector<GLfloat> coneVertices;
	for (int i = 0; i < coneVectors.size(); ++i) {
		vec3 vertex = coneVectors[i];
		coneVertices.push_back(vertex.x);
		coneVertices.push_back(vertex.y);
		coneVertices.push_back(vertex.z);
	}
	return coneVertices;
}

void drawObject(GLuint MatrixID, mat4 MVP, GLuint vertexbuffer, GLuint colorbuffer, GLenum mode, int arrsz) {
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,		  // attribute. No particular reason for 0, but must match the layout in the shader.
		3,		  // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0,		  // stride
		(void *)0 // array buffer offset
	);

	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(
		1,		  // attribute. No particular reason for 1, but must match the layout in the shader.
		3,		  // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0,		  // stride
		(void *)0 // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(mode, 0, arrsz); // 12*3 indices starting at 0 -> 12 triangles

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

}
