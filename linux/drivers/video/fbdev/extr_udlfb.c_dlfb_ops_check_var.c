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
struct fb_videomode {int dummy; } ;
struct fb_var_screeninfo {int dummy; } ;
struct fb_info {struct dlfb_data* par; } ;
struct dlfb_data {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dlfb_is_valid_mode (struct fb_videomode*,struct dlfb_data*) ; 
 int /*<<< orphan*/  dlfb_var_color_format (struct fb_var_screeninfo*) ; 
 int /*<<< orphan*/  fb_var_to_videomode (struct fb_videomode*,struct fb_var_screeninfo*) ; 

__attribute__((used)) static int dlfb_ops_check_var(struct fb_var_screeninfo *var,
				struct fb_info *info)
{
	struct fb_videomode mode;
	struct dlfb_data *dlfb = info->par;

	/* set device-specific elements of var unrelated to mode */
	dlfb_var_color_format(var);

	fb_var_to_videomode(&mode, var);

	if (!dlfb_is_valid_mode(&mode, dlfb))
		return -EINVAL;

	return 0;
}