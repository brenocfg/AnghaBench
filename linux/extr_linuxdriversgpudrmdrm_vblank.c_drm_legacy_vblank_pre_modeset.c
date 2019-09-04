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
struct drm_vblank_crtc {int inmodeset; } ;
struct drm_device {unsigned int num_crtcs; struct drm_vblank_crtc* vblank; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ drm_vblank_get (struct drm_device*,unsigned int) ; 

__attribute__((used)) static void drm_legacy_vblank_pre_modeset(struct drm_device *dev,
					  unsigned int pipe)
{
	struct drm_vblank_crtc *vblank = &dev->vblank[pipe];

	/* vblank is not initialized (IRQ not installed ?), or has been freed */
	if (!dev->num_crtcs)
		return;

	if (WARN_ON(pipe >= dev->num_crtcs))
		return;

	/*
	 * To avoid all the problems that might happen if interrupts
	 * were enabled/disabled around or between these calls, we just
	 * have the kernel take a reference on the CRTC (just once though
	 * to avoid corrupting the count if multiple, mismatch calls occur),
	 * so that interrupts remain enabled in the interim.
	 */
	if (!vblank->inmodeset) {
		vblank->inmodeset = 0x1;
		if (drm_vblank_get(dev, pipe) == 0)
			vblank->inmodeset |= 0x2;
	}
}