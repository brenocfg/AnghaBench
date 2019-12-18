#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct kyrofb_info {int* palette; } ;
struct TYPE_2__ {int bits_per_pixel; } ;
struct fb_info {TYPE_1__ var; struct kyrofb_info* par; } ;

/* Variables and functions */

__attribute__((used)) static int kyrofb_setcolreg(u_int regno, u_int red, u_int green,
			    u_int blue, u_int transp, struct fb_info *info)
{
	struct kyrofb_info *par = info->par;

	if (regno > 255)
		return 1;	/* Invalid register */

	if (regno < 16) {
		switch (info->var.bits_per_pixel) {
		case 16:
			par->palette[regno] =
			     (red   & 0xf800) |
			    ((green & 0xfc00) >> 5) |
			    ((blue  & 0xf800) >> 11);
			break;
		case 32:
			red >>= 8; green >>= 8; blue >>= 8; transp >>= 8;
			par->palette[regno] =
			    (transp << 24) | (red << 16) | (green << 8) | blue;
			break;
		}
	}

	return 0;
}