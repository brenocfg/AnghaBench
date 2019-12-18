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
struct pxafb_mode_info {unsigned int xres; unsigned int yres; scalar_t__ bpp; } ;
struct pxafb_mach_info {unsigned int num_modes; struct pxafb_mode_info* modes; } ;
struct fb_var_screeninfo {unsigned int xres; unsigned int yres; scalar_t__ bits_per_pixel; } ;

/* Variables and functions */

__attribute__((used)) static struct pxafb_mode_info *pxafb_getmode(struct pxafb_mach_info *mach,
					     struct fb_var_screeninfo *var)
{
	struct pxafb_mode_info *mode = NULL;
	struct pxafb_mode_info *modelist = mach->modes;
	unsigned int best_x = 0xffffffff, best_y = 0xffffffff;
	unsigned int i;

	for (i = 0; i < mach->num_modes; i++) {
		if (modelist[i].xres >= var->xres &&
		    modelist[i].yres >= var->yres &&
		    modelist[i].xres < best_x &&
		    modelist[i].yres < best_y &&
		    modelist[i].bpp >= var->bits_per_pixel) {
			best_x = modelist[i].xres;
			best_y = modelist[i].yres;
			mode = &modelist[i];
		}
	}

	return mode;
}