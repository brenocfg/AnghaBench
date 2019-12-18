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
struct TYPE_8__ {int offset; int length; scalar_t__ msb_right; } ;
struct TYPE_7__ {int length; scalar_t__ msb_right; int /*<<< orphan*/  offset; } ;
struct TYPE_6__ {int offset; int length; scalar_t__ msb_right; } ;
struct TYPE_5__ {int offset; int length; scalar_t__ msb_right; } ;
struct fb_var_screeninfo {int bits_per_pixel; int xres_virtual; unsigned long yres_virtual; unsigned long yres; int xres; int xoffset; unsigned long yoffset; int /*<<< orphan*/  pixclock; TYPE_4__ transp; TYPE_3__ blue; TYPE_2__ green; TYPE_1__ red; int /*<<< orphan*/  nonstd; } ;
struct fb_info {struct da8xx_fb_par* par; } ;
struct da8xx_fb_par {unsigned long vram_size; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FB_NONSTD_REV_PIX_IN_B ; 
 scalar_t__ LCD_VERSION_1 ; 
 int /*<<< orphan*/  da8xx_fb_round_clk (struct da8xx_fb_par*,int /*<<< orphan*/ ) ; 
 scalar_t__ lcd_revision ; 

__attribute__((used)) static int fb_check_var(struct fb_var_screeninfo *var,
			struct fb_info *info)
{
	int err = 0;
	struct da8xx_fb_par *par = info->par;
	int bpp = var->bits_per_pixel >> 3;
	unsigned long line_size = var->xres_virtual * bpp;

	if (var->bits_per_pixel > 16 && lcd_revision == LCD_VERSION_1)
		return -EINVAL;

	switch (var->bits_per_pixel) {
	case 1:
	case 8:
		var->red.offset = 0;
		var->red.length = 8;
		var->green.offset = 0;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		var->transp.offset = 0;
		var->transp.length = 0;
		var->nonstd = 0;
		break;
	case 4:
		var->red.offset = 0;
		var->red.length = 4;
		var->green.offset = 0;
		var->green.length = 4;
		var->blue.offset = 0;
		var->blue.length = 4;
		var->transp.offset = 0;
		var->transp.length = 0;
		var->nonstd = FB_NONSTD_REV_PIX_IN_B;
		break;
	case 16:		/* RGB 565 */
		var->red.offset = 11;
		var->red.length = 5;
		var->green.offset = 5;
		var->green.length = 6;
		var->blue.offset = 0;
		var->blue.length = 5;
		var->transp.offset = 0;
		var->transp.length = 0;
		var->nonstd = 0;
		break;
	case 24:
		var->red.offset = 16;
		var->red.length = 8;
		var->green.offset = 8;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		var->nonstd = 0;
		break;
	case 32:
		var->transp.offset = 24;
		var->transp.length = 8;
		var->red.offset = 16;
		var->red.length = 8;
		var->green.offset = 8;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		var->nonstd = 0;
		break;
	default:
		err = -EINVAL;
	}

	var->red.msb_right = 0;
	var->green.msb_right = 0;
	var->blue.msb_right = 0;
	var->transp.msb_right = 0;

	if (line_size * var->yres_virtual > par->vram_size)
		var->yres_virtual = par->vram_size / line_size;

	if (var->yres > var->yres_virtual)
		var->yres = var->yres_virtual;

	if (var->xres > var->xres_virtual)
		var->xres = var->xres_virtual;

	if (var->xres + var->xoffset > var->xres_virtual)
		var->xoffset = var->xres_virtual - var->xres;
	if (var->yres + var->yoffset > var->yres_virtual)
		var->yoffset = var->yres_virtual - var->yres;

	var->pixclock = da8xx_fb_round_clk(par, var->pixclock);

	return err;
}