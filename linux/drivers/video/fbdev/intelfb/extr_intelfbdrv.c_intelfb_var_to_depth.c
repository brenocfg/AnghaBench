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
struct TYPE_2__ {int length; } ;
struct fb_var_screeninfo {int bits_per_pixel; TYPE_1__ green; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_MSG (char*,int,int) ; 

__inline__ int intelfb_var_to_depth(const struct fb_var_screeninfo *var)
{
	DBG_MSG("intelfb_var_to_depth: bpp: %d, green.length is %d\n",
		var->bits_per_pixel, var->green.length);

	switch (var->bits_per_pixel) {
	case 16:
		return (var->green.length == 6) ? 16 : 15;
	case 32:
		return 24;
	default:
		return var->bits_per_pixel;
	}
}