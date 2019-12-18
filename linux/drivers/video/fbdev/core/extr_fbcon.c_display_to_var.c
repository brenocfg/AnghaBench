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
struct fbcon_display {int /*<<< orphan*/  rotate; int /*<<< orphan*/  transp; int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; int /*<<< orphan*/  width; int /*<<< orphan*/  height; int /*<<< orphan*/  accel_flags; int /*<<< orphan*/  nonstd; int /*<<< orphan*/  grayscale; int /*<<< orphan*/  bits_per_pixel; int /*<<< orphan*/  yres_virtual; int /*<<< orphan*/  xres_virtual; int /*<<< orphan*/  mode; } ;
struct fb_var_screeninfo {int /*<<< orphan*/  rotate; int /*<<< orphan*/  transp; int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; int /*<<< orphan*/  width; int /*<<< orphan*/  height; int /*<<< orphan*/  accel_flags; int /*<<< orphan*/  nonstd; int /*<<< orphan*/  grayscale; int /*<<< orphan*/  bits_per_pixel; int /*<<< orphan*/  yres_virtual; int /*<<< orphan*/  xres_virtual; } ;

/* Variables and functions */
 int /*<<< orphan*/  fb_videomode_to_var (struct fb_var_screeninfo*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void display_to_var(struct fb_var_screeninfo *var,
			   struct fbcon_display *disp)
{
	fb_videomode_to_var(var, disp->mode);
	var->xres_virtual = disp->xres_virtual;
	var->yres_virtual = disp->yres_virtual;
	var->bits_per_pixel = disp->bits_per_pixel;
	var->grayscale = disp->grayscale;
	var->nonstd = disp->nonstd;
	var->accel_flags = disp->accel_flags;
	var->height = disp->height;
	var->width = disp->width;
	var->red = disp->red;
	var->green = disp->green;
	var->blue = disp->blue;
	var->transp = disp->transp;
	var->rotate = disp->rotate;
}