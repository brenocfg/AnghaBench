#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;
struct TYPE_11__ {int length; int /*<<< orphan*/  offset; } ;
struct TYPE_10__ {int offset; int length; } ;
struct TYPE_9__ {int offset; int length; } ;
struct fb_var_screeninfo {int xres; int xres_virtual; int yres; int bits_per_pixel; int yres_virtual; TYPE_6__ transp; TYPE_5__ blue; TYPE_4__ green; TYPE_3__ red; scalar_t__ yoffset; scalar_t__ xoffset; } ;
struct TYPE_8__ {int smem_len; } ;
struct TYPE_7__ {int xres; int yres; int bits_per_pixel; } ;
struct fb_info {TYPE_2__ fix; TYPE_1__ var; } ;

/* Variables and functions */

__attribute__((used)) static int hitfb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
{
	int maxy;

	var->xres = info->var.xres;
	var->xres_virtual = info->var.xres;
	var->yres = info->var.yres;

	if ((var->bits_per_pixel != 8) && (var->bits_per_pixel != 16))
		var->bits_per_pixel = info->var.bits_per_pixel;

	if (var->yres_virtual < var->yres)
		var->yres_virtual = var->yres;

	maxy = info->fix.smem_len / var->xres;

	if (var->bits_per_pixel == 16)
		maxy /= 2;

	if (var->yres_virtual > maxy)
		var->yres_virtual = maxy;

	var->xoffset = 0;
	var->yoffset = 0;

	switch (var->bits_per_pixel) {
	case 8:
		var->red.offset = 0;
		var->red.length = 8;
		var->green.offset = 0;
		var->green.length = 8;
		var->blue.offset = 0;
		var->blue.length = 8;
		var->transp.offset = 0;
		var->transp.length = 0;
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
		break;
	}

	return 0;
}