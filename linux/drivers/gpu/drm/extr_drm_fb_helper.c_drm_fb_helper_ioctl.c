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
struct fb_info {struct drm_fb_helper* par; } ;
struct TYPE_4__ {TYPE_1__* modesets; } ;
struct drm_fb_helper {int /*<<< orphan*/  lock; TYPE_2__ client; struct drm_device* dev; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {int dummy; } ;
struct TYPE_3__ {struct drm_crtc* crtc; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOTTY ; 
#define  FBIO_WAITFORVSYNC 128 
 int drm_crtc_vblank_get (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_vblank_put (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_wait_one_vblank (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_master_internal_acquire (struct drm_device*) ; 
 int /*<<< orphan*/  drm_master_internal_release (struct drm_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int drm_fb_helper_ioctl(struct fb_info *info, unsigned int cmd,
			unsigned long arg)
{
	struct drm_fb_helper *fb_helper = info->par;
	struct drm_device *dev = fb_helper->dev;
	struct drm_crtc *crtc;
	int ret = 0;

	mutex_lock(&fb_helper->lock);
	if (!drm_master_internal_acquire(dev)) {
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
		crtc = fb_helper->client.modesets[0].crtc;

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
		break;
	default:
		ret = -ENOTTY;
	}

	drm_master_internal_release(dev);
unlock:
	mutex_unlock(&fb_helper->lock);
	return ret;
}