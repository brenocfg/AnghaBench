#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  unsigned int u32 ;
struct fb_info {scalar_t__ pseudo_palette; } ;

/* Variables and functions */

__attribute__((used)) static int ffb_setcolreg(unsigned regno,
			 unsigned red, unsigned green, unsigned blue,
			 unsigned transp, struct fb_info *info)
{
	u32 value;

	if (regno >= 16)
		return 1;

	red >>= 8;
	green >>= 8;
	blue >>= 8;

	value = (blue << 16) | (green << 8) | red;
	((u32 *)info->pseudo_palette)[regno] = value;

	return 0;
}