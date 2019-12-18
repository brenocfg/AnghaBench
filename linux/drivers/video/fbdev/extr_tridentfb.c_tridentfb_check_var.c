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
struct tridentfb_par {int chip_id; scalar_t__ flatpanel; } ;
struct TYPE_4__ {int offset; int length; } ;
struct fb_var_screeninfo {int bits_per_pixel; int xres; int xres_virtual; int yres; int yres_virtual; int /*<<< orphan*/  pixclock; TYPE_2__ blue; TYPE_2__ green; TYPE_2__ red; } ;
struct TYPE_3__ {int smem_len; } ;
struct fb_info {int flags; TYPE_1__ fix; struct tridentfb_par* par; } ;

/* Variables and functions */
#define  CYBER9320 134 
#define  CYBER9382 133 
#define  CYBER9385 132 
#define  CYBER9388 131 
 int EINVAL ; 
 int FBINFO_HWACCEL_DISABLED ; 
 int PICOS2KHZ (int /*<<< orphan*/ ) ; 
#define  PROVIDIA9685 130 
#define  TGUI9440 129 
#define  TGUI9660 128 
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  is3Dchip (int) ; 
 scalar_t__ is_xp (int) ; 
 int nativex ; 

__attribute__((used)) static int tridentfb_check_var(struct fb_var_screeninfo *var,
			       struct fb_info *info)
{
	struct tridentfb_par *par = info->par;
	int bpp = var->bits_per_pixel;
	int line_length;
	int ramdac = 230000; /* 230MHz for most 3D chips */
	debug("enter\n");

	/* check color depth */
	if (bpp == 24)
		bpp = var->bits_per_pixel = 32;
	if (bpp != 8 && bpp != 16 && bpp != 32)
		return -EINVAL;
	if (par->chip_id == TGUI9440 && bpp == 32)
		return -EINVAL;
	/* check whether resolution fits on panel and in memory */
	if (par->flatpanel && nativex && var->xres > nativex)
		return -EINVAL;
	/* various resolution checks */
	var->xres = (var->xres + 7) & ~0x7;
	if (var->xres > var->xres_virtual)
		var->xres_virtual = var->xres;
	if (var->yres > var->yres_virtual)
		var->yres_virtual = var->yres;
	if (var->xres_virtual > 4095 || var->yres > 2048)
		return -EINVAL;
	/* prevent from position overflow for acceleration */
	if (var->yres_virtual > 0xffff)
		return -EINVAL;
	line_length = var->xres_virtual * bpp / 8;

	if (!is3Dchip(par->chip_id) &&
	    !(info->flags & FBINFO_HWACCEL_DISABLED)) {
		/* acceleration requires line length to be power of 2 */
		if (line_length <= 512)
			var->xres_virtual = 512 * 8 / bpp;
		else if (line_length <= 1024)
			var->xres_virtual = 1024 * 8 / bpp;
		else if (line_length <= 2048)
			var->xres_virtual = 2048 * 8 / bpp;
		else if (line_length <= 4096)
			var->xres_virtual = 4096 * 8 / bpp;
		else if (line_length <= 8192)
			var->xres_virtual = 8192 * 8 / bpp;
		else
			return -EINVAL;

		line_length = var->xres_virtual * bpp / 8;
	}

	/* datasheet specifies how to set panning only up to 4 MB */
	if (line_length * (var->yres_virtual - var->yres) > (4 << 20))
		var->yres_virtual = ((4 << 20) / line_length) + var->yres;

	if (line_length * var->yres_virtual > info->fix.smem_len)
		return -EINVAL;

	switch (bpp) {
	case 8:
		var->red.offset = 0;
		var->red.length = 8;
		var->green = var->red;
		var->blue = var->red;
		break;
	case 16:
		var->red.offset = 11;
		var->green.offset = 5;
		var->blue.offset = 0;
		var->red.length = 5;
		var->green.length = 6;
		var->blue.length = 5;
		break;
	case 32:
		var->red.offset = 16;
		var->green.offset = 8;
		var->blue.offset = 0;
		var->red.length = 8;
		var->green.length = 8;
		var->blue.length = 8;
		break;
	default:
		return -EINVAL;
	}

	if (is_xp(par->chip_id))
		ramdac = 350000;

	switch (par->chip_id) {
	case TGUI9440:
		ramdac = (bpp >= 16) ? 45000 : 90000;
		break;
	case CYBER9320:
	case TGUI9660:
		ramdac = 135000;
		break;
	case PROVIDIA9685:
	case CYBER9388:
	case CYBER9382:
	case CYBER9385:
		ramdac = 170000;
		break;
	}

	/* The clock is doubled for 32 bpp */
	if (bpp == 32)
		ramdac /= 2;

	if (PICOS2KHZ(var->pixclock) > ramdac)
		return -EINVAL;

	debug("exit\n");

	return 0;

}