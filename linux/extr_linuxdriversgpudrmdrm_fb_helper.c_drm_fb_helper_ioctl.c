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
struct fb_info {struct drm_fb_helper* par; } ;
struct drm_mode_set {struct drm_crtc* crtc; } ;
struct drm_fb_helper {int /*<<< orphan*/  lock; TYPE_1__* crtc_info; } ;
struct drm_crtc {int dummy; } ;
struct TYPE_2__ {struct drm_mode_set mode_set; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOTTY ; 
#define  FBIO_WAITFORVSYNC 128 
 int drm_crtc_vblank_get (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_vblank_put (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_wait_one_vblank (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_fb_helper_is_bound (struct drm_fb_helper*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int drm_fb_helper_ioctl(struct fb_info *info, unsigned int cmd,
			unsigned long arg)
{
	struct drm_fb_helper *fb_helper = info->par;
	struct drm_mode_set *mode_set;
	struct drm_crtc *crtc;
	int ret = 0;

	mutex_lock(&fb_helper->lock);
	if (!drm_fb_helper_is_bound(fb_helper)) {
		ret = -EBUSY;
		goto unlock;
	}

	switch (cmd) {
	case FBIO_WAITFORVSYNC:
		/*
		 * Only consider the first CRTC.
		 *
		 * This ioctl is supposed to take the CRTC number as
		 * an argument, but in fbdev times, what that number
		 * was supposed to be was quite unclear, different
		 * drivers were passing that argument differently
		 * (some by reference, some by value), and most of the
		 * userspace applications were just hardcoding 0 as an
		 * argument.
		 *
		 * The first CRTC should be the integrated panel on
		 * most drivers, so this is the best choice we can
		 * make. If we're not smart enough here, one should
		 * just consider switch the userspace to KMS.
		 */
		mode_set = &fb_helper->crtc_info[0].mode_set;
		crtc = mode_set->crtc;

		/*
		 * Only wait for a vblank event if the CRTC is
		 * enabled, otherwise just don't do anythintg,
		 * not even report an error.
		 */
		ret = drm_crtc_vblank_get(crtc);
		if (!ret) {
			drm_crtc_wait_one_vblank(crtc);
			drm_crtc_vblank_put(crtc);
		}

		ret = 0;
		goto unlock;
	default:
		ret = -ENOTTY;
	}

unlock:
	mutex_unlock(&fb_helper->lock);
	return ret;
}