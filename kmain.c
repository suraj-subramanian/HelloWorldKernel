#include "io.h"

/* The I/O ports */
#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT 0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND 15

/*Frame buffer*/
#define FRAME_BUFFER 0x000B8000
#define FB_GREEN 2
#define FB_DARK_GREY 8

void fb_write_cell(unsigned int, char, unsigned char, unsigned char);
void fb_move_cursor(unsigned short);
void print_to_fb(char *);

char *fb = (char *)FRAME_BUFFER;

int kmain()
{
   char arr[] = "Hello World !!!";
   print_to_fb(arr);
   fb_move_cursor(10);
   return 0;
}

/** fb_write_cell:
* Writes a character with the given foreground and background to position i
* in the framebuffer.
*
* @param i The location in the framebuffer
* @param c The character
* @param fg The foreground color
* @param bg The background color
*/
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
   fb[i] = c;
   fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

/** fb_move_cursor:
* Moves the cursor of the framebuffer to the given position
*
* @param pos The new position of the cursor
*/
void fb_move_cursor(unsigned short pos)
{
   outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
   outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
   outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
   outb(FB_DATA_PORT, pos & 0x00FF);
}

/**
*  print_to_fb:
*  Prints the string pointed by the pointer to Frame Buffer
*  @param c Pointer to the string
*/
void print_to_fb(char *c)
{
   int i = 0;
   while (*c != '\0')
   {
      fb_write_cell(i, *c++, FB_GREEN, FB_DARK_GREY);
      i = i + 2;
   }
}