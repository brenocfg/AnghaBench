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
typedef  unsigned int u32 ;
struct ivtv {TYPE_2__* osd_info; } ;
struct TYPE_7__ {int length; } ;
struct TYPE_8__ {int bits_per_pixel; TYPE_3__ green; } ;
struct TYPE_5__ {unsigned int len; } ;
struct fb_info {unsigned int* pseudo_palette; TYPE_4__ var; TYPE_1__ cmap; scalar_t__ par; } ;
struct TYPE_6__ {unsigned int* palette_cur; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  write_reg (unsigned int,int) ; 

__attribute__((used)) static int ivtvfb_setcolreg(unsigned regno, unsigned red, unsigned green,
				unsigned blue, unsigned transp,
				struct fb_info *info)
{
	u32 color, *palette;
	struct ivtv *itv = (struct ivtv *)info->par;

	if (regno >= info->cmap.len)
		return -EINVAL;

	color = ((transp & 0xFF00) << 16) |((red & 0xFF00) << 8) | (green & 0xFF00) | ((blue & 0xFF00) >> 8);
	if (info->var.bits_per_pixel <= 8) {
		write_reg(regno, 0x02a30);
		write_reg(color, 0x02a34);
		itv->osd_info->palette_cur[regno] = color;
		return 0;
	}
	if (regno >= 16)
		return -EINVAL;

	palette = info->pseudo_palette;
	if (info->var.bits_per_pixel == 16) {
		switch (info->var.green.length) {
			case 4:
				color = ((red & 0xf000) >> 4) |
					((green & 0xf000) >> 8) |
					((blue & 0xf000) >> 12);
				break;
			case 5:
				color = ((red & 0xf800) >> 1) |
					((green & 0xf800) >> 6) |
					((blue & 0xf800) >> 11);
				break;
			case 6:
				color = (red & 0xf800 ) |
					((green & 0xfc00) >> 5) |
					((blue & 0xf800) >> 11);
				break;
		}
	}
	palette[regno] = color;
	return 0;
}