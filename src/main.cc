#include <string>
#include <vector>
#include <variant>
#include <iostream>
#include <cstring>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include "graphics/opengl/index.hh"
#include "graphics/window.hh"
#include "graphics/primitives.hh"
#include "unit.hh"
#include "config.hh"
#include "color.hh"
#include "fonts.hh"
#include "defer.hh"

using namespace config;
using namespace color;
using namespace fonts;
using namespace err;
using namespace defer;
using namespace window;

static const Config conf(
	{"Iosevka Term"},
	RGBColor(255, 255, 255),
	RGBColor(30, 30, 30),
	2,
	16
);

Result<Unit> run() {
	using namespace std::literals;

	try(auto font_path, get_closest_font_match(conf.fonts));

	Window window(800, 600, "cae");

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, primitives::triangle.size(), primitives::triangle.data(), GL_STATIC_DRAW);

	while (!glfwWindowShouldClose(window.handle)) {
		glfwSwapBuffers(window.handle);
		glfwPollEvents();
	}

	return unit;
}

int main(int argc, char* argv[]) {
	(void)argc;
	(void)argv;

	auto out = run();
	if (std::holds_alternative<Err>(out)) {
		std::cerr << "Error: " << std::get<Err>(out) << std::endl;
	}
	return 0;
}
