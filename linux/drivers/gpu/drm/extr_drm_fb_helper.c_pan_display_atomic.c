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
struct fb_var_screeninfo {int /*<<< orphan*/  yoffset; int /*<<< orphan*/  xoffset; } ;
struct TYPE_2__ {int /*<<< orphan*/  yoffset; int /*<<< orphan*/  xoffset; } ;
struct fb_info {TYPE_1__ var; struct drm_fb_helper* par; } ;
struct drm_fb_helper {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int drm_client_modeset_commit_force (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pan_set (struct drm_fb_helper*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pan_display_atomic(struct fb_var_screeninfo *var,
			      struct fb_info *info)
{
	struct drm_fb_helper *fb_helper = info->par;
	int ret;

	pan_set(fb_helper, var->xoffset, var->yoffset);

	ret = drm_client_modeset_commit_force(&fb_helper->client);
	if (!ret) {
		info->var.xoffset = var->xoffset;
		info->var.yoffset = var->yoffset;
	} else
		pan_set(fb_helper, info->var.xoffset, info->var.yoffset);

	return ret;
}