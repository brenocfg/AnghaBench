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
struct drm_device {unsigned int num_crtcs; int /*<<< orphan*/  vbl_lock; struct drm_vblank_crtc* vblank; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  drm_reset_vblank_timestamp (struct drm_device*,unsigned int) ; 
 int /*<<< orphan*/  drm_vblank_put (struct drm_device*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void drm_legacy_vblank_post_modeset(struct drm_device *dev,
					   unsigned int pipe)
{
	struct drm_vblank_crtc *vblank = &dev->vblank[pipe];
	unsigned long irqflags;

	/* vblank is not initialized (IRQ not installed ?), or has been freed */
	if (!dev->num_crtcs)
		return;

	if (WARN_ON(pipe >= dev->num_crtcs))
		return;

	if (vblank->inmodeset) {
		spin_lock_irqsave(&dev->vbl_lock, irqflags);
		drm_reset_vblank_timestamp(dev, pipe);
		spin_unlock_irqrestore(&dev->vbl_lock, irqflags);

		if (vblank->inmodeset & 0x2)
			drm_vblank_put(dev, pipe);

		vblank->inmodeset = 0;
	}
}