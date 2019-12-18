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
typedef  int u32 ;
struct fb_var_screeninfo {int bits_per_pixel; } ;
struct fb_info {int dummy; } ;
struct fb_blit_caps {int x; int y; int len; } ;

/* Variables and functions */

void svga_get_caps(struct fb_info *info, struct fb_blit_caps *caps,
		   struct fb_var_screeninfo *var)
{
	if (var->bits_per_pixel == 0) {
		/* can only support 256 8x16 bitmap */
		caps->x = 1 << (8 - 1);
		caps->y = 1 << (16 - 1);
		caps->len = 256;
	} else {
		caps->x = (var->bits_per_pixel == 4) ? 1 << (8 - 1) : ~(u32)0;
		caps->y = ~(u32)0;
		caps->len = ~(u32)0;
	}
}