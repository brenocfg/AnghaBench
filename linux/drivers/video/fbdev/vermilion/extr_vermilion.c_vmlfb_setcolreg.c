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
typedef  int u_int ;
typedef  int u32 ;
struct TYPE_11__ {int offset; int /*<<< orphan*/  length; } ;
struct TYPE_10__ {int offset; int /*<<< orphan*/  length; } ;
struct TYPE_9__ {int offset; int /*<<< orphan*/  length; } ;
struct TYPE_8__ {int offset; int /*<<< orphan*/  length; } ;
struct TYPE_12__ {int bits_per_pixel; TYPE_5__ transp; TYPE_4__ blue; TYPE_3__ green; TYPE_2__ red; scalar_t__ grayscale; } ;
struct TYPE_7__ {scalar_t__ visual; } ;
struct fb_info {scalar_t__ pseudo_palette; TYPE_6__ var; TYPE_1__ fix; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FB_VISUAL_TRUECOLOR ; 
 int VML_TOHW (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vmlfb_setcolreg(u_int regno, u_int red, u_int green, u_int blue,
			   u_int transp, struct fb_info *info)
{
	u32 v;

	if (regno >= 16)
		return -EINVAL;

	if (info->var.grayscale) {
		red = green = blue = (red * 77 + green * 151 + blue * 28) >> 8;
	}

	if (info->fix.visual != FB_VISUAL_TRUECOLOR)
		return -EINVAL;

	red = VML_TOHW(red, info->var.red.length);
	blue = VML_TOHW(blue, info->var.blue.length);
	green = VML_TOHW(green, info->var.green.length);
	transp = VML_TOHW(transp, info->var.transp.length);

	v = (red << info->var.red.offset) |
	    (green << info->var.green.offset) |
	    (blue << info->var.blue.offset) |
	    (transp << info->var.transp.offset);

	switch (info->var.bits_per_pixel) {
	case 16:
		((u32 *) info->pseudo_palette)[regno] = v;
		break;
	case 24:
	case 32:
		((u32 *) info->pseudo_palette)[regno] = v;
		break;
	}
	return 0;
}