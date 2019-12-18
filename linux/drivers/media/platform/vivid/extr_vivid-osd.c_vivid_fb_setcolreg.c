#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct TYPE_5__ {int length; } ;
struct TYPE_6__ {int bits_per_pixel; TYPE_2__ green; } ;
struct TYPE_4__ {unsigned int len; } ;
struct fb_info {unsigned int* pseudo_palette; TYPE_3__ var; TYPE_1__ cmap; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int vivid_fb_setcolreg(unsigned regno, unsigned red, unsigned green,
				unsigned blue, unsigned transp,
				struct fb_info *info)
{
	u32 color, *palette;

	if (regno >= info->cmap.len)
		return -EINVAL;

	color = ((transp & 0xFF00) << 16) | ((red & 0xFF00) << 8) |
		 (green & 0xFF00) | ((blue & 0xFF00) >> 8);
	if (regno >= 16)
		return -EINVAL;

	palette = info->pseudo_palette;
	if (info->var.bits_per_pixel == 16) {
		switch (info->var.green.length) {
		case 6:
			color = (red & 0xf800) |
				((green & 0xfc00) >> 5) |
				((blue & 0xf800) >> 11);
			break;
		case 5:
			color = ((red & 0xf800) >> 1) |
				((green & 0xf800) >> 6) |
				((blue & 0xf800) >> 11) |
				(transp ? 0x8000 : 0);
			break;
		}
	}
	palette[regno] = color;
	return 0;
}