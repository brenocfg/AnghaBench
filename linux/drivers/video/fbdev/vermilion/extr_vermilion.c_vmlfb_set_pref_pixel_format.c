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
struct TYPE_7__ {int offset; int length; scalar_t__ msb_right; } ;
struct TYPE_6__ {int offset; int length; scalar_t__ msb_right; } ;
struct TYPE_5__ {int length; scalar_t__ msb_right; int /*<<< orphan*/  offset; } ;
struct fb_var_screeninfo {int bits_per_pixel; TYPE_4__ transp; TYPE_3__ red; TYPE_2__ green; TYPE_1__ blue; } ;

/* Variables and functions */

__attribute__((used)) static void vmlfb_set_pref_pixel_format(struct fb_var_screeninfo *var)
{
	switch (var->bits_per_pixel) {
	case 16:
		var->blue.offset = 0;
		var->blue.length = 5;
		var->green.offset = 5;
		var->green.length = 5;
		var->red.offset = 10;
		var->red.length = 5;
		var->transp.offset = 15;
		var->transp.length = 1;
		break;
	case 32:
		var->blue.offset = 0;
		var->blue.length = 8;
		var->green.offset = 8;
		var->green.length = 8;
		var->red.offset = 16;
		var->red.length = 8;
		var->transp.offset = 24;
		var->transp.length = 0;
		break;
	default:
		break;
	}

	var->blue.msb_right = var->green.msb_right =
	    var->red.msb_right = var->transp.msb_right = 0;
}