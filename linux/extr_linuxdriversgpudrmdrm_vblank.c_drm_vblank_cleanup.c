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
struct drm_vblank_crtc {int /*<<< orphan*/  disable_timer; int /*<<< orphan*/  enabled; } ;
struct drm_device {unsigned int num_crtcs; struct drm_vblank_crtc* vblank; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_MODESET ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct drm_vblank_crtc*) ; 

void drm_vblank_cleanup(struct drm_device *dev)
{
	unsigned int pipe;

	/* Bail if the driver didn't call drm_vblank_init() */
	if (dev->num_crtcs == 0)
		return;

	for (pipe = 0; pipe < dev->num_crtcs; pipe++) {
		struct drm_vblank_crtc *vblank = &dev->vblank[pipe];

		WARN_ON(READ_ONCE(vblank->enabled) &&
			drm_core_check_feature(dev, DRIVER_MODESET));

		del_timer_sync(&vblank->disable_timer);
	}

	kfree(dev->vblank);

	dev->num_crtcs = 0;
}