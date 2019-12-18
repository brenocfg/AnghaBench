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
struct TYPE_10__ {int length; int offset; scalar_t__ msb_right; } ;
struct TYPE_9__ {int length; scalar_t__ offset; scalar_t__ msb_right; } ;
struct TYPE_8__ {int length; scalar_t__ offset; scalar_t__ msb_right; } ;
struct fb_var_screeninfo {int bits_per_pixel; TYPE_5__ green; TYPE_4__ blue; TYPE_3__ red; int /*<<< orphan*/  transp; } ;
struct clcd_fb {TYPE_2__* panel; TYPE_1__* board; } ;
struct TYPE_7__ {int caps; int cntl; } ;
struct TYPE_6__ {int caps; } ;

/* Variables and functions */
 int CLCD_CAP_444 ; 
 int CLCD_CAP_5551 ; 
 int CLCD_CAP_565 ; 
 int CLCD_CAP_888 ; 
 int CLCD_CAP_BGR ; 
 int CLCD_CAP_RGB ; 
 int CNTL_BGR ; 
 int CNTL_LCDTFT ; 
 int EINVAL ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
clcdfb_set_bitfields(struct clcd_fb *fb, struct fb_var_screeninfo *var)
{
	u32 caps;
	int ret = 0;

	if (fb->panel->caps && fb->board->caps)
		caps = fb->panel->caps & fb->board->caps;
	else {
		/* Old way of specifying what can be used */
		caps = fb->panel->cntl & CNTL_BGR ?
			CLCD_CAP_BGR : CLCD_CAP_RGB;
		/* But mask out 444 modes as they weren't supported */
		caps &= ~CLCD_CAP_444;
	}

	/* Only TFT panels can do RGB888/BGR888 */
	if (!(fb->panel->cntl & CNTL_LCDTFT))
		caps &= ~CLCD_CAP_888;

	memset(&var->transp, 0, sizeof(var->transp));

	var->red.msb_right = 0;
	var->green.msb_right = 0;
	var->blue.msb_right = 0;

	switch (var->bits_per_pixel) {
	case 1:
	case 2:
	case 4:
	case 8:
		/* If we can't do 5551, reject */
		caps &= CLCD_CAP_5551;
		if (!caps) {
			ret = -EINVAL;
			break;
		}

		var->red.length		= var->bits_per_pixel;
		var->red.offset		= 0;
		var->green.length	= var->bits_per_pixel;
		var->green.offset	= 0;
		var->blue.length	= var->bits_per_pixel;
		var->blue.offset	= 0;
		break;

	case 16:
		/* If we can't do 444, 5551 or 565, reject */
		if (!(caps & (CLCD_CAP_444 | CLCD_CAP_5551 | CLCD_CAP_565))) {
			ret = -EINVAL;
			break;
		}

		/*
		 * Green length can be 4, 5 or 6 depending whether
		 * we're operating in 444, 5551 or 565 mode.
		 */
		if (var->green.length == 4 && caps & CLCD_CAP_444)
			caps &= CLCD_CAP_444;
		if (var->green.length == 5 && caps & CLCD_CAP_5551)
			caps &= CLCD_CAP_5551;
		else if (var->green.length == 6 && caps & CLCD_CAP_565)
			caps &= CLCD_CAP_565;
		else {
			/*
			 * PL110 officially only supports RGB555,
			 * but may be wired up to allow RGB565.
			 */
			if (caps & CLCD_CAP_565) {
				var->green.length = 6;
				caps &= CLCD_CAP_565;
			} else if (caps & CLCD_CAP_5551) {
				var->green.length = 5;
				caps &= CLCD_CAP_5551;
			} else {
				var->green.length = 4;
				caps &= CLCD_CAP_444;
			}
		}

		if (var->green.length >= 5) {
			var->red.length = 5;
			var->blue.length = 5;
		} else {
			var->red.length = 4;
			var->blue.length = 4;
		}
		break;
	case 32:
		/* If we can't do 888, reject */
		caps &= CLCD_CAP_888;
		if (!caps) {
			ret = -EINVAL;
			break;
		}

		var->red.length = 8;
		var->green.length = 8;
		var->blue.length = 8;
		break;
	default:
		ret = -EINVAL;
		break;
	}

	/*
	 * >= 16bpp displays have separate colour component bitfields
	 * encoded in the pixel data.  Calculate their position from
	 * the bitfield length defined above.
	 */
	if (ret == 0 && var->bits_per_pixel >= 16) {
		bool bgr, rgb;

		bgr = caps & CLCD_CAP_BGR && var->blue.offset == 0;
		rgb = caps & CLCD_CAP_RGB && var->red.offset == 0;

		if (!bgr && !rgb)
			/*
			 * The requested format was not possible, try just
			 * our capabilities.  One of BGR or RGB must be
			 * supported.
			 */
			bgr = caps & CLCD_CAP_BGR;

		if (bgr) {
			var->blue.offset = 0;
			var->green.offset = var->blue.offset + var->blue.length;
			var->red.offset = var->green.offset + var->green.length;
		} else {
			var->red.offset = 0;
			var->green.offset = var->red.offset + var->red.length;
			var->blue.offset = var->green.offset + var->green.length;
		}
	}

	return ret;
}