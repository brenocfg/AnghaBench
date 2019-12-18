#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct fb_var_screeninfo {unsigned int yres_virtual; unsigned int yres; int bits_per_pixel; int yoffset; int xoffset; } ;
struct fb_fix_screeninfo {unsigned int line_length; } ;

/* Variables and functions */
 int FB_ROTATE_CCW ; 
 int FB_ROTATE_CW ; 
 int FB_ROTATE_UD ; 
 int FB_ROTATE_UR ; 

__attribute__((used)) static unsigned calc_rotation_offset_vrfb(const struct fb_var_screeninfo *var,
		const struct fb_fix_screeninfo *fix, int rotation)
{
	unsigned offset;

	if (rotation == FB_ROTATE_UD)
		offset = (var->yres_virtual - var->yres) *
			fix->line_length;
	else if (rotation == FB_ROTATE_CW)
		offset = (var->yres_virtual - var->yres) *
			(var->bits_per_pixel >> 3);
	else
		offset = 0;

	if (rotation == FB_ROTATE_UR)
		offset += var->yoffset * fix->line_length +
			var->xoffset * (var->bits_per_pixel >> 3);
	else if (rotation == FB_ROTATE_UD)
		offset -= var->yoffset * fix->line_length +
			var->xoffset * (var->bits_per_pixel >> 3);
	else if (rotation == FB_ROTATE_CW)
		offset -= var->xoffset * fix->line_length +
			var->yoffset * (var->bits_per_pixel >> 3);
	else if (rotation == FB_ROTATE_CCW)
		offset += var->xoffset * fix->line_length +
			var->yoffset * (var->bits_per_pixel >> 3);

	return offset;
}