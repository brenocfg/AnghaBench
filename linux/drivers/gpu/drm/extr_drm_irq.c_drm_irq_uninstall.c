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
struct drm_vblank_crtc {int /*<<< orphan*/  queue; int /*<<< orphan*/  enabled; } ;
struct drm_device {int irq_enabled; int num_crtcs; int /*<<< orphan*/  irq; TYPE_1__* driver; int /*<<< orphan*/  pdev; int /*<<< orphan*/  vbl_lock; struct drm_vblank_crtc* vblank; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* irq_uninstall ) (struct drm_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_LEGACY ; 
 int /*<<< orphan*/  DRIVER_MODESET ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  WARN_ON (scalar_t__) ; 
 scalar_t__ drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_vblank_disable_and_save (struct drm_device*,int) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct drm_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct drm_device*) ; 
 int /*<<< orphan*/  vga_client_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int drm_irq_uninstall(struct drm_device *dev)
{
	unsigned long irqflags;
	bool irq_enabled;
	int i;

	irq_enabled = dev->irq_enabled;
	dev->irq_enabled = false;

	/*
	 * Wake up any waiters so they don't hang. This is just to paper over
	 * issues for UMS drivers which aren't in full control of their
	 * vblank/irq handling. KMS drivers must ensure that vblanks are all
	 * disabled when uninstalling the irq handler.
	 */
	if (dev->num_crtcs) {
		spin_lock_irqsave(&dev->vbl_lock, irqflags);
		for (i = 0; i < dev->num_crtcs; i++) {
			struct drm_vblank_crtc *vblank = &dev->vblank[i];

			if (!vblank->enabled)
				continue;

			WARN_ON(drm_core_check_feature(dev, DRIVER_MODESET));

			drm_vblank_disable_and_save(dev, i);
			wake_up(&vblank->queue);
		}
		spin_unlock_irqrestore(&dev->vbl_lock, irqflags);
	}

	if (!irq_enabled)
		return -EINVAL;

	DRM_DEBUG("irq=%d\n", dev->irq);

	if (drm_core_check_feature(dev, DRIVER_LEGACY))
		vga_client_register(dev->pdev, NULL, NULL, NULL);

	if (dev->driver->irq_uninstall)
		dev->driver->irq_uninstall(dev);

	free_irq(dev->irq, dev);

	return 0;
}