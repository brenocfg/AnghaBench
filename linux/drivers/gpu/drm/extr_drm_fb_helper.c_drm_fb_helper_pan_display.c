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
struct fb_var_screeninfo {int dummy; } ;
struct fb_info {struct drm_fb_helper* par; } ;
struct drm_fb_helper {int /*<<< orphan*/  lock; struct drm_device* dev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ drm_drv_uses_atomic_modeset (struct drm_device*) ; 
 int /*<<< orphan*/  drm_master_internal_acquire (struct drm_device*) ; 
 int /*<<< orphan*/  drm_master_internal_release (struct drm_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ oops_in_progress ; 
 int pan_display_atomic (struct fb_var_screeninfo*,struct fb_info*) ; 
 int pan_display_legacy (struct fb_var_screeninfo*,struct fb_info*) ; 

int drm_fb_helper_pan_display(struct fb_var_screeninfo *var,
			      struct fb_info *info)
{
	struct drm_fb_helper *fb_helper = info->par;
	struct drm_device *dev = fb_helper->dev;
	int ret;

	if (oops_in_progress)
		return -EBUSY;

	mutex_lock(&fb_helper->lock);
	if (!drm_master_internal_acquire(dev)) {
		ret = -EBUSY;
		goto unlock;
	}

	if (drm_drv_uses_atomic_modeset(dev))
		ret = pan_display_atomic(var, info);
	else
		ret = pan_display_legacy(var, info);

	drm_master_internal_release(dev);
unlock:
	mutex_unlock(&fb_helper->lock);

	return ret;
}