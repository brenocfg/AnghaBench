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
struct TYPE_12__ {void* visual; } ;
struct TYPE_10__ {int length; int /*<<< orphan*/  offset; } ;
struct TYPE_9__ {int offset; int length; } ;
struct TYPE_8__ {int offset; int length; } ;
struct TYPE_7__ {scalar_t__ length; scalar_t__ offset; } ;
struct TYPE_11__ {int bits_per_pixel; TYPE_4__ blue; TYPE_3__ green; TYPE_2__ red; TYPE_1__ transp; } ;
struct fb_info {TYPE_6__ fix; TYPE_5__ var; struct ep93xx_fbi* par; } ;
struct ep93xx_fbi {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EP93XXFB_PIXELMODE ; 
 unsigned int EP93XXFB_PIXELMODE_16BPP ; 
 unsigned int EP93XXFB_PIXELMODE_24BPP ; 
 unsigned int EP93XXFB_PIXELMODE_32BPP ; 
 unsigned int EP93XXFB_PIXELMODE_8BPP ; 
 unsigned int EP93XXFB_PIXELMODE_COLOR_555 ; 
 unsigned int EP93XXFB_PIXELMODE_COLOR_888 ; 
 unsigned int EP93XXFB_PIXELMODE_COLOR_LUT ; 
 unsigned int EP93XXFB_PIXELMODE_SHIFT_1P_18B ; 
 unsigned int EP93XXFB_PIXELMODE_SHIFT_1P_24B ; 
 void* FB_VISUAL_PSEUDOCOLOR ; 
 void* FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  ep93xxfb_writel (struct ep93xx_fbi*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ep93xxfb_set_pixelmode(struct fb_info *info)
{
	struct ep93xx_fbi *fbi = info->par;
	unsigned int val;

	info->var.transp.offset = 0;
	info->var.transp.length = 0;

	switch (info->var.bits_per_pixel) {
	case 8:
		val = EP93XXFB_PIXELMODE_8BPP | EP93XXFB_PIXELMODE_COLOR_LUT |
			EP93XXFB_PIXELMODE_SHIFT_1P_18B;

		info->var.red.offset	= 0;
		info->var.red.length	= 8;
		info->var.green.offset	= 0;
		info->var.green.length	= 8;
		info->var.blue.offset	= 0;
		info->var.blue.length	= 8;
		info->fix.visual 	= FB_VISUAL_PSEUDOCOLOR;
		break;

	case 16:
		val = EP93XXFB_PIXELMODE_16BPP | EP93XXFB_PIXELMODE_COLOR_555 |
			EP93XXFB_PIXELMODE_SHIFT_1P_18B;

		info->var.red.offset	= 11;
		info->var.red.length	= 5;
		info->var.green.offset	= 5;
		info->var.green.length	= 6;
		info->var.blue.offset	= 0;
		info->var.blue.length	= 5;
		info->fix.visual 	= FB_VISUAL_TRUECOLOR;
		break;

	case 24:
		val = EP93XXFB_PIXELMODE_24BPP | EP93XXFB_PIXELMODE_COLOR_888 |
			EP93XXFB_PIXELMODE_SHIFT_1P_24B;

		info->var.red.offset	= 16;
		info->var.red.length	= 8;
		info->var.green.offset	= 8;
		info->var.green.length	= 8;
		info->var.blue.offset	= 0;
		info->var.blue.length	= 8;
		info->fix.visual 	= FB_VISUAL_TRUECOLOR;
		break;

	case 32:
		val = EP93XXFB_PIXELMODE_32BPP | EP93XXFB_PIXELMODE_COLOR_888 |
			EP93XXFB_PIXELMODE_SHIFT_1P_24B;

		info->var.red.offset	= 16;
		info->var.red.length	= 8;
		info->var.green.offset	= 8;
		info->var.green.length	= 8;
		info->var.blue.offset	= 0;
		info->var.blue.length	= 8;
		info->fix.visual 	= FB_VISUAL_TRUECOLOR;
		break;

	default:
		return -EINVAL;
	}

	ep93xxfb_writel(fbi, val, EP93XXFB_PIXELMODE);
	return 0;
}