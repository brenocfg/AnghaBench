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
typedef  int u_int ;
struct TYPE_4__ {int offset; int length; scalar_t__ msb_right; } ;
struct TYPE_3__ {int offset; int length; scalar_t__ msb_right; } ;
struct fb_var_screeninfo {int bits_per_pixel; TYPE_2__ transp; TYPE_1__ blue; TYPE_1__ green; TYPE_1__ red; } ;
struct fb_info {int /*<<< orphan*/  monspecs; } ;

/* Variables and functions */
 int EINVAL ; 
 int acornfb_adjust_timing (struct fb_info*,struct fb_var_screeninfo*,int) ; 
 int /*<<< orphan*/  acornfb_valid_pixrate (struct fb_var_screeninfo*) ; 
 int acornfb_validate_timing (struct fb_var_screeninfo*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
acornfb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
	u_int fontht;
	int err;

	/*
	 * FIXME: Find the font height
	 */
	fontht = 8;

	var->red.msb_right = 0;
	var->green.msb_right = 0;
	var->blue.msb_right = 0;
	var->transp.msb_right = 0;

	switch (var->bits_per_pixel) {
	case 1:	case 2:	case 4:	case 8:
		var->red.offset    = 0;
		var->red.length    = var->bits_per_pixel;
		var->green         = var->red;
		var->blue          = var->red;
		var->transp.offset = 0;
		var->transp.length = 0;
		break;

#ifdef HAS_VIDC20
	case 16:
		var->red.offset    = 0;
		var->red.length    = 5;
		var->green.offset  = 5;
		var->green.length  = 5;
		var->blue.offset   = 10;
		var->blue.length   = 5;
		var->transp.offset = 15;
		var->transp.length = 1;
		break;

	case 32:
		var->red.offset    = 0;
		var->red.length    = 8;
		var->green.offset  = 8;
		var->green.length  = 8;
		var->blue.offset   = 16;
		var->blue.length   = 8;
		var->transp.offset = 24;
		var->transp.length = 4;
		break;
#endif
	default:
		return -EINVAL;
	}

	/*
	 * Check to see if the pixel rate is valid.
	 */
	if (!acornfb_valid_pixrate(var))
		return -EINVAL;

	/*
	 * Validate and adjust the resolution to
	 * match the video generator hardware.
	 */
	err = acornfb_adjust_timing(info, var, fontht);
	if (err)
		return err;

	/*
	 * Validate the timing against the
	 * monitor hardware.
	 */
	return acornfb_validate_timing(var, &info->monspecs);
}