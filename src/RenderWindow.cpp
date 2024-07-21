#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_width, int p_height)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_width, p_height, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::LoadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if(texture == NULL)
		std::cout << "Failed to load a texture" << SDL_GetError() << std::endl;

	return texture;
}

void RenderWindow::Cleanup() 
{
	SDL_DestroyWindow(window);
}

void RenderWindow::Clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::Render(Entity& p_entity)
{
	SDL_Rect src;
	src.x = p_entity.GetCurrentFrame().x;
	src.y = p_entity.GetCurrentFrame().y;
	src.w = p_entity.GetCurrentFrame().w;
	src.h = p_entity.GetCurrentFrame().h;

	SDL_Rect dest;
	dest.x = p_entity.GetX();
	dest.y = p_entity.GetY();
	dest.w = p_entity.GetCurrentFrame().w;
	dest.h = p_entity.GetCurrentFrame().h;

	SDL_RenderCopy(renderer, p_entity.GetTexture(), &src, &dest);
}

void RenderWindow::Display()
{
	SDL_RenderPresent(renderer);
}
