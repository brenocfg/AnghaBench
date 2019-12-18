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
struct fb_videomode {int dummy; } ;
struct fb_var_screeninfo {int xres; int yres; } ;
struct TYPE_2__ {int smem_len; } ;
struct fb_info {TYPE_1__ fix; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  fb_var_to_videomode (struct fb_videomode*,struct fb_var_screeninfo*) ; 
 int /*<<< orphan*/  ufx_is_valid_mode (struct fb_videomode*,struct fb_info*) ; 
 int /*<<< orphan*/  ufx_var_color_format (struct fb_var_screeninfo*) ; 

__attribute__((used)) static int ufx_ops_check_var(struct fb_var_screeninfo *var,
				struct fb_info *info)
{
	struct fb_videomode mode;

	/* TODO: support dynamically changing framebuffer size */
	if ((var->xres * var->yres * 2) > info->fix.smem_len)
		return -EINVAL;

	/* set device-specific elements of var unrelated to mode */
	ufx_var_color_format(var);

	fb_var_to_videomode(&mode, var);

	if (!ufx_is_valid_mode(&mode, info))
		return -EINVAL;

	return 0;
}