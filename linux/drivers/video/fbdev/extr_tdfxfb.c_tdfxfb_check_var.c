#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tdfx_par {scalar_t__ max_pixclock; } ;
struct TYPE_8__ {int length; int offset; } ;
struct TYPE_7__ {int offset; int length; } ;
struct fb_var_screeninfo {int bits_per_pixel; int xres; int xres_virtual; int yres; int yres_virtual; int vmode; int width; int height; int /*<<< orphan*/  accel_flags; TYPE_4__ blue; TYPE_4__ green; TYPE_4__ red; TYPE_3__ transp; int /*<<< orphan*/  pixclock; scalar_t__ yoffset; scalar_t__ xoffset; } ;
struct TYPE_6__ {int smem_len; } ;
struct TYPE_5__ {scalar_t__ dclkmax; scalar_t__ vfmax; scalar_t__ hfmax; } ;
struct fb_info {TYPE_2__ fix; TYPE_1__ monspecs; struct tdfx_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FB_ACCELF_TEXT ; 
 int FB_VMODE_INTERLACED ; 
 int FB_VMODE_MASK ; 
 scalar_t__ PICOS2KHZ (int /*<<< orphan*/ ) ; 
 scalar_t__ VOODOO3_MAX_PIXCLOCK ; 
 scalar_t__ fb_validate_mode (struct fb_var_screeninfo*,struct fb_info*) ; 

__attribute__((used)) static int tdfxfb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
	struct tdfx_par *par = info->par;
	u32 lpitch;

	if (var->bits_per_pixel != 8  && var->bits_per_pixel != 16 &&
	    var->bits_per_pixel != 24 && var->bits_per_pixel != 32) {
		DPRINTK("depth not supported: %u\n", var->bits_per_pixel);
		return -EINVAL;
	}

	if (var->xres != var->xres_virtual)
		var->xres_virtual = var->xres;

	if (var->yres > var->yres_virtual)
		var->yres_virtual = var->yres;

	if (var->xoffset) {
		DPRINTK("xoffset not supported\n");
		return -EINVAL;
	}
	var->yoffset = 0;

	/*
	 * Banshee doesn't support interlace, but Voodoo4/5 and probably
	 * Voodoo3 do.
	 * no direct information about device id now?
	 *  use max_pixclock for this...
	 */
	if (((var->vmode & FB_VMODE_MASK) == FB_VMODE_INTERLACED) &&
	    (par->max_pixclock < VOODOO3_MAX_PIXCLOCK)) {
		DPRINTK("interlace not supported\n");
		return -EINVAL;
	}

	if (info->monspecs.hfmax && info->monspecs.vfmax &&
	    info->monspecs.dclkmax && fb_validate_mode(var, info) < 0) {
		DPRINTK("mode outside monitor's specs\n");
		return -EINVAL;
	}

	var->xres = (var->xres + 15) & ~15; /* could sometimes be 8 */
	lpitch = var->xres * ((var->bits_per_pixel + 7) >> 3);

	if (var->xres < 320 || var->xres > 2048) {
		DPRINTK("width not supported: %u\n", var->xres);
		return -EINVAL;
	}

	if (var->yres < 200 || var->yres > 2048) {
		DPRINTK("height not supported: %u\n", var->yres);
		return -EINVAL;
	}

	if (lpitch * var->yres_virtual > info->fix.smem_len) {
		var->yres_virtual = info->fix.smem_len / lpitch;
		if (var->yres_virtual < var->yres) {
			DPRINTK("no memory for screen (%ux%ux%u)\n",
				var->xres, var->yres_virtual,
				var->bits_per_pixel);
			return -EINVAL;
		}
	}

	if (PICOS2KHZ(var->pixclock) > par->max_pixclock) {
		DPRINTK("pixclock too high (%ldKHz)\n",
			PICOS2KHZ(var->pixclock));
		return -EINVAL;
	}

	var->transp.offset = 0;
	var->transp.length = 0;
	switch (var->bits_per_pixel) {
	case 8:
		var->red.length = 8;
		var->red.offset = 0;
		var->green = var->red;
		var->blue = var->red;
		break;
	case 16:
		var->red.offset   = 11;
		var->red.length   = 5;
		var->green.offset = 5;
		var->green.length = 6;
		var->blue.offset  = 0;
		var->blue.length  = 5;
		break;
	case 32:
		var->transp.offset = 24;
		var->transp.length = 8;
		/* fall through */
	case 24:
		var->red.offset = 16;
		var->green.offset = 8;
		var->blue.offset = 0;
		var->red.length = var->green.length = var->blue.length = 8;
		break;
	}
	var->width = -1;
	var->height = -1;

	var->accel_flags = FB_ACCELF_TEXT;

	DPRINTK("Checking graphics mode at %dx%d depth %d\n",
		var->xres, var->yres, var->bits_per_pixel);
	return 0;
}