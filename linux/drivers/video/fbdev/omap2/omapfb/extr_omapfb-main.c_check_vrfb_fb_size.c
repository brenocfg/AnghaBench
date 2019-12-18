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
struct fb_var_screeninfo {int bits_per_pixel; int /*<<< orphan*/  yres_virtual; int /*<<< orphan*/  xres_virtual; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long omap_vrfb_min_phys_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int check_vrfb_fb_size(unsigned long region_size,
		const struct fb_var_screeninfo *var)
{
	unsigned long min_phys_size = omap_vrfb_min_phys_size(var->xres_virtual,
		var->yres_virtual, var->bits_per_pixel >> 3);

	return min_phys_size > region_size ? -EINVAL : 0;
}