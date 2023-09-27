// Code adapted from www.learnopengl.com, www.glfw.org

#include <iostream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_interpolation.hpp>

#include "shader.h"

int main(void)
{
	//++++create a glfw window+++++++++++++++++++++++++++++++++++++++
	GLFWwindow* window;

	if (!glfwInit()) //Initialize the library
		return -1;

	window = glfwCreateWindow( 640, 640, "OpenGL Window", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);//Make the window's context current

	//++++Initialize GLEW to setup the OpenGL Function pointers+++++++
	glewExperimental = GL_TRUE;
	glewInit();

	//++++Define the viewport dimensions++++++++++++++++++++++++++++
	glViewport(0, 0, 640, 640);

	//Set up vertex data (and buffer(s)) and attribute pointers+++++++++
	GLfloat firstTriangle[] = {
		//position ,      colour 
	   -0.0f, -0.0f, 0.0f, 1.0f, 0.0f, 1.0f,// Left 
	   -0.4f, -0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // Right
	   -0.2f, -0.2f, 0.0f, 1.0f, 0.0f, 1.0f, // Top 
	};
	GLfloat secondTriangle[] = {
		 -0.4f, -0.0f, 0.0f,  0.0f, 1.0f, 1.0f,// Left
		 -0.2f, -0.2f, 0.0f,  0.0f, 1.0f, 1.0f,// Right
		 -0.4f, -0.4f, 0.0f,  0.0f, 1.0f, 1.0f,// Top 
	};
	GLfloat thirdTriangle[] = {
	  -0.0f, -0.0f, 0.0f,  0.0f, 1.0f, 0.0f,// Left
	  -0.1f, -0.1f, 0.0f,  0.0f, 1.0f, 0.0f,// Right
	  -0.0f, -0.2f, 0.0f,  0.0f, 1.0f, 0.0f,// Top 
	};
	GLfloat fourthTriangle[] = {
	  -0.0f, -0.2f, 0.0f,  1.0f, 1.0f, 0.0f,// Left
	  -0.0f, -0.4f, 0.0f,  1.0f, 1.0f, 0.0f,// Right
	  -0.2f, -0.4f, 0.0f,  1.0f, 1.0f, 0.0f,// Top 
	};
	GLfloat fifthTriangle[] = {
	  -0.2f, -0.2f, 0.0f,  1.0f, 0.5f, 0.0f,// Left
	  -0.1f, -0.3f, 0.0f,  1.0f, 0.5f, 0.0f,// Right
	  -0.3f, -0.3f, 0.0f,  1.0f, 0.5f, 0.0f,// Top 
	};
	GLfloat vertices1[] = {
	  -0.1f, -0.1f, 0.0f,  0.0f, 0.0f, 1.0f,// top right
	  -0.0f, -0.2f, 0.0f,  0.0f, 0.0f, 1.0f,// bottom right
	  -0.1f, -0.3f, 0.0f,  0.0f, 0.0f, 1.0f,// bottom left

	};
	GLfloat vertices2[] = {
		-0.1f, -0.1f, 0.0f, 0.0f, 0.0f, 1.0f, //top right
		-0.2f, -0.2f, 0.0f, 0.0f, 0.0f, 1.0f, //left 
		-0.1f, -0.3f, 0.0f, 0.0f, 0.0f, 1.0f, //bottom left 
	};
	GLfloat rhombus[] = {
		-0.1f, -0.3f, 0.0f, 1.0f, 0.0f, 0.0f, //top right
		-0.3f, -0.3f, 0.0f, 1.0f, 0.0f, 0.0f, //top left 
		-0.2f, -0.4f, 0.0f, 1.0f, 0.0f, 0.0f, //bottom right
	};
	GLfloat rhombus2[] = {
		-0.3f, -0.3f, 0.0f, 1.0f, 0.0f, 0.0f, //top left
		-0.4f, -0.4f, 0.0f, 1.0f, 0.0f, 0.0f, //bttom left 
		-0.2f, -0.4f, 0.0f, 1.0f, 0.0f, 0.0f, //bottom right 
	};

	GLuint VBOs[9], VAOs[9];
	glGenVertexArrays(9, VAOs);
	glGenBuffers(9, VBOs);

	// Triangle1 setup
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);	// Vertex attributes stay the same
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))); // Color attribute
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	// Triangle2 setup
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);	// Vertex attributes stay the same
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))); // Color attribute
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

// Triangle3 setup
	glBindVertexArray(VAOs[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(thirdTriangle), thirdTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);	// Vertex attributes stay the same
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))); // Color attribute
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

// Triangle4 setup
	glBindVertexArray(VAOs[3]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fourthTriangle), fourthTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);	// Vertex attributes stay the same
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))); // Color attribute
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

// Triangle5 setup
	glBindVertexArray(VAOs[4]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fifthTriangle), fifthTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);	// Vertex attributes stay the same
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))); // Color attribute
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

// Triangle6 setup
	glBindVertexArray(VAOs[5]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[5]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);	// Vertex attributes stay the same
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))); // Color attribute
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

// Triangle7 setup
	glBindVertexArray(VAOs[6]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[6]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);	// Vertex attributes stay the same
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))); // Color attribute
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

// Triangle8 setup
	glBindVertexArray(VAOs[7]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[7]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rhombus), rhombus, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);	// Vertex attributes stay the same
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))); // Color attribute
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

// Triangle9 setup
	glBindVertexArray(VAOs[8]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[8]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rhombus2), rhombus2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);	// Vertex attributes stay the same
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat))); // Color attribute
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	//Build and compile shader program
	GLuint shaderProgram = initShader("vert.glsl", "frag.glsl");


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		GLint transformLoc;
		double t = 0.21f;
		GLfloat time = (GLfloat)glfwGetTime() * 0.2f;

		// Draw Triangle1

		glm::mat4 transform1;
		glm::mat4 identity1;

		if ((GLfloat)glfwGetTime() * 0.2f >= t) {
			transform1 = glm::translate(transform1, glm::vec3(0.0f, 0.0f, 0.0f));
			transform1 = glm::rotate(transform1, (GLfloat)(3.14), glm::vec3(0.0f, -0.5f, 0.0f));

			if ((GLfloat)glfwGetTime() * 0.2f <= 1.0)
				transform1 = glm::mix(identity1, transform1, (GLfloat)glfwGetTime() * 0.2f); //the last parameter should be between 0-1 to interpolate
		}
		// Get matrix's uniform location and set matrix
		transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform1));

		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		// Draw Triangle2
		glm::mat4 transform2;
		glm::mat4 identity2;
		if ((GLfloat)glfwGetTime() * 0.2f >= t) {
			transform2 = glm::translate(transform2, glm::vec3(0.4f, 0.4f, 0.0f));
			transform2 = glm::rotate(transform2, (GLfloat)(3.14), glm::vec3(0.5f, 0.5f, 0.0f));

			if ((GLfloat)glfwGetTime() * 0.2f <= 1.0)
				transform2 = glm::mix(identity2, transform2, (GLfloat)glfwGetTime() * 0.2f); //the last parameter should be between 0-1 to interpolate
		}

		// Get matrix's uniform location and set matrix
		transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform2));

		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Draw Triangle3
		glm::mat4 transform3;
		glm::mat4 identity3;
		if ((GLfloat)glfwGetTime() * 0.2f >= t) {
			transform3 = glm::translate(transform3, glm::vec3(0.2f, -0.2f, 0.0f));
			transform3 = glm::rotate(transform3, (GLfloat)(3.14 ), glm::vec3(0.2f, -0.4500f, 0.0f));

			if ((GLfloat)glfwGetTime() * 0.2f <= 1.0)
				transform3 = glm::mix(identity3, transform3, (GLfloat)glfwGetTime() * 0.2f); //the last parameter should be between 0-1 to interpolate
		}
		// Get matrix's uniform location and set matrix
		transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform3));

		glBindVertexArray(VAOs[2]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Draw Triangle4
		glm::mat4 transform4;
		glm::mat4 identity4;
		if ((GLfloat)glfwGetTime() * 0.2f >= t) {
			transform4 = glm::translate(transform4, glm::vec3(-0.2f, 0.4f, 0.0f));
			transform4 = glm::rotate(transform4, (GLfloat)(3.14), glm::vec3(0.0f, 0.9f, 0.0f));

			if ((GLfloat)glfwGetTime() * 0.2f <= 1.0)
				transform4 = glm::mix(identity4, transform4, (GLfloat)glfwGetTime() * 0.2f); //the last parameter should be between 0-1 to interpolate
		}
		// Get matrix's uniform location and set matrix
		transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform4));

		glBindVertexArray(VAOs[3]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Draw Triangle5
		glm::mat4 transform5;
		glm::mat4 identity5;
		if ((GLfloat)glfwGetTime() * 0.2f >= t) {
			transform5 = glm::translate(transform5, glm::vec3(-0.2200f, -0.1900f, 0.0f));
			transform5 = glm::rotate(transform5, (GLfloat)(3.14), glm::vec3(0.3f, -0.7500f, 0.0f));

			if ((GLfloat)glfwGetTime() * 0.2f <= 1.0)
				transform5 = glm::mix(identity5, transform5, (GLfloat)glfwGetTime() * 0.2f); //the last parameter should be between 0-1 to interpolate
		}
		// Get matrix's uniform location and set matrix
		transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform5));


		glBindVertexArray(VAOs[4]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Draw Triangle6
		glm::mat4 transform6;
		glm::mat4 identity6;
		if ((GLfloat)glfwGetTime() * 0.2f >= t) {
			transform6 = glm::translate(transform6, glm::vec3(0.1f, 0.5f, 0.0f));
			transform6 = glm::rotate(transform6, (GLfloat)(3.14), glm::vec3(0.0f, 0.7f, 0.0f));

			if ((GLfloat)glfwGetTime() * 0.2f <= 1.0)
				transform6 = glm::mix(identity6, transform6, (GLfloat)glfwGetTime() * 0.2f); //the last parameter should be between 0-1 to interpolate
		}
		// Get matrix's uniform location and set matrix
		transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform6));

		glBindVertexArray(VAOs[5]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Draw Triangle7

		glBindVertexArray(VAOs[6]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Draw Triangle8
		glm::mat4 transform8;
		glm::mat4 identity8;
		if ((GLfloat)glfwGetTime() * 0.2f >= t) {
			transform8 = glm::translate(transform8, glm::vec3(0.9200f, 0.2100f, 0.0f));
			transform8 = glm::rotate(transform8, (GLfloat)(3.14), glm::vec3(0.6f, 0.4f, 0.0f));

			if ((GLfloat)glfwGetTime() * 0.2f <= 1.0)
				transform8 = glm::mix(identity8, transform8, (GLfloat)glfwGetTime() * 0.2f); //the last parameter should be between 0-1 to interpolate
		}
		// Get matrix's uniform location and set matrix
		transformLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform8));


		glBindVertexArray(VAOs[7]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Draw Triangle9

		glBindVertexArray(VAOs[8]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	// Properly de-allocate all resources once they've outlived their purpose
	glDeleteVertexArrays(9, VAOs);
	glDeleteBuffers(9, VBOs);

	glfwTerminate();
	return 0;
}