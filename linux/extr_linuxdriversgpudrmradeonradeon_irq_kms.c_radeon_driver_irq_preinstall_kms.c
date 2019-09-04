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
struct TYPE_2__ {int dpm_thermal; int* hpd; int* crtc_vblank_int; int* afmt; int /*<<< orphan*/  lock; int /*<<< orphan*/ * pflip; int /*<<< orphan*/ * ring_int; } ;
struct radeon_device {TYPE_1__ irq; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 unsigned int RADEON_MAX_CRTCS ; 
 unsigned int RADEON_MAX_HPD_PINS ; 
 unsigned int RADEON_NUM_RINGS ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_irq_process (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_irq_set (struct radeon_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void radeon_driver_irq_preinstall_kms(struct drm_device *dev)
{
	struct radeon_device *rdev = dev->dev_private;
	unsigned long irqflags;
	unsigned i;

	spin_lock_irqsave(&rdev->irq.lock, irqflags);
	/* Disable *all* interrupts */
	for (i = 0; i < RADEON_NUM_RINGS; i++)
		atomic_set(&rdev->irq.ring_int[i], 0);
	rdev->irq.dpm_thermal = false;
	for (i = 0; i < RADEON_MAX_HPD_PINS; i++)
		rdev->irq.hpd[i] = false;
	for (i = 0; i < RADEON_MAX_CRTCS; i++) {
		rdev->irq.crtc_vblank_int[i] = false;
		atomic_set(&rdev->irq.pflip[i], 0);
		rdev->irq.afmt[i] = false;
	}
	radeon_irq_set(rdev);
	spin_unlock_irqrestore(&rdev->irq.lock, irqflags);
	/* Clear bits */
	radeon_irq_process(rdev);
}