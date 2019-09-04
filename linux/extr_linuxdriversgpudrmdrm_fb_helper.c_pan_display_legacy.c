#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fb_var_screeninfo {int /*<<< orphan*/  yoffset; int /*<<< orphan*/  xoffset; } ;
struct TYPE_4__ {int /*<<< orphan*/  yoffset; int /*<<< orphan*/  xoffset; } ;
struct fb_info {TYPE_2__ var; struct drm_fb_helper* par; } ;
struct drm_mode_set {scalar_t__ num_connectors; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct drm_fb_helper {int crtc_count; int /*<<< orphan*/  dev; TYPE_1__* crtc_info; } ;
struct TYPE_3__ {struct drm_mode_set mode_set; } ;

/* Variables and functions */
 int drm_mode_set_config_internal (struct drm_mode_set*) ; 
 int /*<<< orphan*/  drm_modeset_lock_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_modeset_unlock_all (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pan_display_legacy(struct fb_var_screeninfo *var,
			      struct fb_info *info)
{
	struct drm_fb_helper *fb_helper = info->par;
	struct drm_mode_set *modeset;
	int ret = 0;
	int i;

	drm_modeset_lock_all(fb_helper->dev);
	for (i = 0; i < fb_helper->crtc_count; i++) {
		modeset = &fb_helper->crtc_info[i].mode_set;

		modeset->x = var->xoffset;
		modeset->y = var->yoffset;

		if (modeset->num_connectors) {
			ret = drm_mode_set_config_internal(modeset);
			if (!ret) {
				info->var.xoffset = var->xoffset;
				info->var.yoffset = var->yoffset;
			}
		}
	}
	drm_modeset_unlock_all(fb_helper->dev);

	return ret;
}