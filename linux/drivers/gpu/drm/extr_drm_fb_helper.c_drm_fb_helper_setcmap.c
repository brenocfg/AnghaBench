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
struct TYPE_3__ {scalar_t__ visual; } ;
struct fb_info {TYPE_1__ fix; struct drm_fb_helper* par; } ;
struct fb_cmap {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  modeset_mutex; } ;
struct drm_fb_helper {int /*<<< orphan*/  lock; TYPE_2__ client; struct drm_device* dev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ FB_VISUAL_TRUECOLOR ; 
 scalar_t__ drm_drv_uses_atomic_modeset (struct drm_device*) ; 
 int /*<<< orphan*/  drm_master_internal_acquire (struct drm_device*) ; 
 int /*<<< orphan*/  drm_master_internal_release (struct drm_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ oops_in_progress ; 
 int setcmap_atomic (struct fb_cmap*,struct fb_info*) ; 
 int setcmap_legacy (struct fb_cmap*,struct fb_info*) ; 
 int setcmap_pseudo_palette (struct fb_cmap*,struct fb_info*) ; 

int drm_fb_helper_setcmap(struct fb_cmap *cmap, struct fb_info *info)
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

	mutex_lock(&fb_helper->client.modeset_mutex);
	if (info->fix.visual == FB_VISUAL_TRUECOLOR)
		ret = setcmap_pseudo_palette(cmap, info);
	else if (drm_drv_uses_atomic_modeset(fb_helper->dev))
		ret = setcmap_atomic(cmap, info);
	else
		ret = setcmap_legacy(cmap, info);
	mutex_unlock(&fb_helper->client.modeset_mutex);

	drm_master_internal_release(dev);
unlock:
	mutex_unlock(&fb_helper->lock);

	return ret;
}