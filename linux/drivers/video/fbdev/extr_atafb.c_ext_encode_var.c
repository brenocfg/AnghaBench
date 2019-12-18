#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ msb_right; scalar_t__ length; scalar_t__ offset; } ;
struct TYPE_3__ {int length; scalar_t__ msb_right; scalar_t__ offset; } ;
struct fb_var_screeninfo {int pixclock; int left_margin; int right_margin; int upper_margin; int lower_margin; int hsync_len; int vsync_len; int height; int width; int bits_per_pixel; int /*<<< orphan*/  vmode; scalar_t__ activate; scalar_t__ nonstd; scalar_t__ yoffset; scalar_t__ xoffset; int /*<<< orphan*/  yres; int /*<<< orphan*/  yres_virtual; TYPE_2__ transp; TYPE_1__ red; TYPE_1__ green; TYPE_1__ blue; int /*<<< orphan*/  xres_virtual; int /*<<< orphan*/  xres; scalar_t__ sync; scalar_t__ grayscale; } ;
struct atafb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FB_VMODE_NONINTERLACED ; 
 int external_bitspercol ; 
 int external_depth ; 
 int external_pmode ; 
 scalar_t__ external_vgaiobase ; 
 int /*<<< orphan*/  external_xres ; 
 int /*<<< orphan*/  external_xres_virtual ; 
 int /*<<< orphan*/  external_yres ; 
 int /*<<< orphan*/  memset (struct fb_var_screeninfo*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ext_encode_var(struct fb_var_screeninfo *var, struct atafb_par *par)
{
	memset(var, 0, sizeof(struct fb_var_screeninfo));
	var->red.offset = 0;
	var->red.length = (external_pmode == -1) ? external_depth / 3 :
			(external_vgaiobase ? external_bitspercol : 0);
	var->red.msb_right = 0;
	var->grayscale = 0;

	var->pixclock = 31041;
	var->left_margin = 120;		/* these are surely incorrect */
	var->right_margin = 100;
	var->upper_margin = 8;
	var->lower_margin = 16;
	var->hsync_len = 140;
	var->vsync_len = 30;

	var->height = -1;
	var->width = -1;

	var->sync = 0;

	var->xres = external_xres;
	var->yres = external_yres;
	var->xres_virtual = external_xres_virtual;
	var->bits_per_pixel = external_depth;

	var->blue = var->green = var->red;
	var->transp.offset = 0;
	var->transp.length = 0;
	var->transp.msb_right = 0;
	var->yres_virtual = var->yres;
	var->xoffset = 0;
	var->yoffset = 0;
	var->nonstd = 0;
	var->activate = 0;
	var->vmode = FB_VMODE_NONINTERLACED;
	return 0;
}