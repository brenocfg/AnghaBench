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
typedef  unsigned int u32 ;
struct TYPE_9__ {int length; unsigned int offset; } ;
struct TYPE_8__ {int length; unsigned int offset; } ;
struct TYPE_7__ {int length; unsigned int offset; } ;
struct TYPE_10__ {int bits_per_pixel; TYPE_4__ blue; TYPE_3__ green; TYPE_2__ red; } ;
struct TYPE_6__ {scalar_t__ visual; } ;
struct fb_info {TYPE_5__ var; TYPE_1__ fix; struct cirrusfb_info* par; } ;
struct cirrusfb_info {unsigned int* pseudo_palette; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FB_VISUAL_TRUECOLOR ; 
 int /*<<< orphan*/  WClut (struct cirrusfb_info*,unsigned int,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int cirrusfb_setcolreg(unsigned regno, unsigned red, unsigned green,
			      unsigned blue, unsigned transp,
			      struct fb_info *info)
{
	struct cirrusfb_info *cinfo = info->par;

	if (regno > 255)
		return -EINVAL;

	if (info->fix.visual == FB_VISUAL_TRUECOLOR) {
		u32 v;
		red >>= (16 - info->var.red.length);
		green >>= (16 - info->var.green.length);
		blue >>= (16 - info->var.blue.length);

		if (regno >= 16)
			return 1;
		v = (red << info->var.red.offset) |
		    (green << info->var.green.offset) |
		    (blue << info->var.blue.offset);

		cinfo->pseudo_palette[regno] = v;
		return 0;
	}

	if (info->var.bits_per_pixel == 8)
		WClut(cinfo, regno, red >> 10, green >> 10, blue >> 10);

	return 0;

}