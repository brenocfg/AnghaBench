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
struct TYPE_2__ {scalar_t__ visual; } ;
struct fb_info {TYPE_1__ fix; struct drm_fb_helper* par; } ;
struct fb_cmap {int dummy; } ;
struct drm_fb_helper {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ FB_VISUAL_TRUECOLOR ; 
 scalar_t__ drm_drv_uses_atomic_modeset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fb_helper_is_bound (struct drm_fb_helper*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ oops_in_progress ; 
 int setcmap_atomic (struct fb_cmap*,struct fb_info*) ; 
 int setcmap_legacy (struct fb_cmap*,struct fb_info*) ; 
 int setcmap_pseudo_palette (struct fb_cmap*,struct fb_info*) ; 

int drm_fb_helper_setcmap(struct fb_cmap *cmap, struct fb_info *info)
{
	struct drm_fb_helper *fb_helper = info->par;
	int ret;

	if (oops_in_progress)
		return -EBUSY;

	mutex_lock(&fb_helper->lock);

	if (!drm_fb_helper_is_bound(fb_helper)) {
		ret = -EBUSY;
		goto out;
	}

	if (info->fix.visual == FB_VISUAL_TRUECOLOR)
		ret = setcmap_pseudo_palette(cmap, info);
	else if (drm_drv_uses_atomic_modeset(fb_helper->dev))
		ret = setcmap_atomic(cmap, info);
	else
		ret = setcmap_legacy(cmap, info);

out:
	mutex_unlock(&fb_helper->lock);

	return ret;
}