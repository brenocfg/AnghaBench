#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_9__ {unsigned int length; int offset; } ;
struct TYPE_8__ {unsigned int length; int offset; } ;
struct TYPE_7__ {unsigned int length; int offset; } ;
struct TYPE_6__ {unsigned int length; scalar_t__ offset; } ;
struct fb_var_screeninfo {unsigned int bits_per_pixel; int height; int width; int xres; int xres_virtual; int yres; int yres_virtual; int vmode; scalar_t__ accel_flags; int /*<<< orphan*/  pixclock; scalar_t__ xoffset; TYPE_4__ red; TYPE_3__ transp; TYPE_2__ green; TYPE_1__ blue; } ;
struct TYPE_10__ {int smem_len; } ;
struct fb_info {TYPE_5__ fix; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 int EINVAL ; 
 int FB_VMODE_INTERLACED ; 
 int FB_VMODE_MASK ; 
 int /*<<< orphan*/  PICOS2KHZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PM3_MAX_PIXCLOCK ; 

__attribute__((used)) static int pm3fb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
	u32 lpitch;
	unsigned bpp = var->red.length + var->green.length
			+ var->blue.length + var->transp.length;

	if (bpp != var->bits_per_pixel) {
		/* set predefined mode for bits_per_pixel settings */

		switch (var->bits_per_pixel) {
		case 8:
			var->red.length = 8;
			var->green.length = 8;
			var->blue.length = 8;
			var->red.offset = 0;
			var->green.offset = 0;
			var->blue.offset = 0;
			var->transp.offset = 0;
			var->transp.length = 0;
			break;
		case 16:
			var->red.length = 5;
			var->blue.length = 5;
			var->green.length = 6;
			var->transp.length = 0;
			break;
		case 32:
			var->red.length = 8;
			var->green.length = 8;
			var->blue.length = 8;
			var->transp.length = 8;
			break;
		default:
			DPRINTK("depth not supported: %u\n",
				var->bits_per_pixel);
			return -EINVAL;
		}
	}
	/* it is assumed BGRA order */
	if (var->bits_per_pixel > 8 ) {
		var->blue.offset = 0;
		var->green.offset = var->blue.length;
		var->red.offset = var->green.offset + var->green.length;
		var->transp.offset = var->red.offset + var->red.length;
	}
	var->height = -1;
	var->width = -1;

	if (var->xres != var->xres_virtual) {
		DPRINTK("virtual x resolution != "
			"physical x resolution not supported\n");
		return -EINVAL;
	}

	if (var->yres > var->yres_virtual) {
		DPRINTK("virtual y resolution < "
			"physical y resolution not possible\n");
		return -EINVAL;
	}

	if (var->xoffset) {
		DPRINTK("xoffset not supported\n");
		return -EINVAL;
	}

	if ((var->vmode & FB_VMODE_MASK) == FB_VMODE_INTERLACED) {
		DPRINTK("interlace not supported\n");
		return -EINVAL;
	}

	var->xres = (var->xres + 31) & ~31; /* could sometimes be 8 */
	lpitch = var->xres * ((var->bits_per_pixel + 7) >> 3);

	if (var->xres < 200 || var->xres > 2048) {
		DPRINTK("width not supported: %u\n", var->xres);
		return -EINVAL;
	}

	if (var->yres < 200 || var->yres > 4095) {
		DPRINTK("height not supported: %u\n", var->yres);
		return -EINVAL;
	}

	if (lpitch * var->yres_virtual > info->fix.smem_len) {
		DPRINTK("no memory for screen (%ux%ux%u)\n",
			var->xres, var->yres_virtual, var->bits_per_pixel);
		return -EINVAL;
	}

	if (PICOS2KHZ(var->pixclock) > PM3_MAX_PIXCLOCK) {
		DPRINTK("pixclock too high (%ldKHz)\n",
			PICOS2KHZ(var->pixclock));
		return -EINVAL;
	}

	var->accel_flags = 0;	/* Can't mmap if this is on */

	DPRINTK("Checking graphics mode at %dx%d depth %d\n",
		var->xres, var->yres, var->bits_per_pixel);
	return 0;
}