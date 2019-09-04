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
struct TYPE_2__ {int /*<<< orphan*/  length; } ;
struct fb_var_screeninfo {int bits_per_pixel; TYPE_1__ transp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int EINVAL ; 

__attribute__((used)) static int vmw_fb_compute_depth(struct fb_var_screeninfo *var,
				int *depth)
{
	switch (var->bits_per_pixel) {
	case 32:
		*depth = (var->transp.length > 0) ? 32 : 24;
		break;
	default:
		DRM_ERROR("Bad bpp %u.\n", var->bits_per_pixel);
		return -EINVAL;
	}

	return 0;
}