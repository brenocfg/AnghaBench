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
struct fb_var_screeninfo {scalar_t__ bits_per_pixel; scalar_t__ xres; scalar_t__ xres_virtual; scalar_t__ yres; scalar_t__ xoffset; scalar_t__ yoffset; } ;
struct atafb_par {int next_line; } ;

/* Variables and functions */
 int EINVAL ; 
 struct fb_var_screeninfo* atafb_predefined ; 
 int external_depth ; 
 int external_xres_virtual ; 

__attribute__((used)) static int ext_decode_var(struct fb_var_screeninfo *var, struct atafb_par *par)
{
	struct fb_var_screeninfo *myvar = &atafb_predefined[0];

	if (var->bits_per_pixel > myvar->bits_per_pixel ||
	    var->xres > myvar->xres ||
	    var->xres_virtual > myvar->xres_virtual ||
	    var->yres > myvar->yres ||
	    var->xoffset > 0 ||
	    var->yoffset > 0)
		return -EINVAL;

	par->next_line = external_xres_virtual * external_depth / 8;
	return 0;
}