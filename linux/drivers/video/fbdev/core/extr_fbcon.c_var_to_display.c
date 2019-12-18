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
struct fbcon_display {int /*<<< orphan*/ * mode; int /*<<< orphan*/  rotate; int /*<<< orphan*/  transp; int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; int /*<<< orphan*/  width; int /*<<< orphan*/  height; int /*<<< orphan*/  accel_flags; int /*<<< orphan*/  nonstd; int /*<<< orphan*/  grayscale; int /*<<< orphan*/  bits_per_pixel; int /*<<< orphan*/  yres_virtual; int /*<<< orphan*/  xres_virtual; } ;
struct fb_var_screeninfo {int /*<<< orphan*/  rotate; int /*<<< orphan*/  transp; int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; int /*<<< orphan*/  width; int /*<<< orphan*/  height; int /*<<< orphan*/  accel_flags; int /*<<< orphan*/  nonstd; int /*<<< orphan*/  grayscale; int /*<<< orphan*/  bits_per_pixel; int /*<<< orphan*/  yres_virtual; int /*<<< orphan*/  xres_virtual; } ;
struct fb_info {int /*<<< orphan*/  modelist; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/ * fb_match_mode (struct fb_var_screeninfo*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int var_to_display(struct fbcon_display *disp,
			  struct fb_var_screeninfo *var,
			  struct fb_info *info)
{
	disp->xres_virtual = var->xres_virtual;
	disp->yres_virtual = var->yres_virtual;
	disp->bits_per_pixel = var->bits_per_pixel;
	disp->grayscale = var->grayscale;
	disp->nonstd = var->nonstd;
	disp->accel_flags = var->accel_flags;
	disp->height = var->height;
	disp->width = var->width;
	disp->red = var->red;
	disp->green = var->green;
	disp->blue = var->blue;
	disp->transp = var->transp;
	disp->rotate = var->rotate;
	disp->mode = fb_match_mode(var, &info->modelist);
	if (disp->mode == NULL)
		/* This should not happen */
		return -EINVAL;
	return 0;
}