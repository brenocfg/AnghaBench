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
struct fb_info {struct drm_fb_helper* par; } ;
struct drm_fb_helper {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DRM_MODE_DPMS_ON ; 
 int /*<<< orphan*/  dpms_legacy (struct drm_fb_helper*,int) ; 
 scalar_t__ drm_drv_uses_atomic_modeset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fb_helper_is_bound (struct drm_fb_helper*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  restore_fbdev_mode_atomic (struct drm_fb_helper*,int) ; 

__attribute__((used)) static void drm_fb_helper_dpms(struct fb_info *info, int dpms_mode)
{
	struct drm_fb_helper *fb_helper = info->par;

	/*
	 * For each CRTC in this fb, turn the connectors on/off.
	 */
	mutex_lock(&fb_helper->lock);
	if (!drm_fb_helper_is_bound(fb_helper)) {
		mutex_unlock(&fb_helper->lock);
		return;
	}

	if (drm_drv_uses_atomic_modeset(fb_helper->dev))
		restore_fbdev_mode_atomic(fb_helper, dpms_mode == DRM_MODE_DPMS_ON);
	else
		dpms_legacy(fb_helper, dpms_mode);
	mutex_unlock(&fb_helper->lock);
}