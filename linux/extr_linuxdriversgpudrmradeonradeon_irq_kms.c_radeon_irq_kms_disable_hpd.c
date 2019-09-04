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
struct TYPE_4__ {int* hpd; int /*<<< orphan*/  lock; } ;
struct radeon_device {TYPE_2__ irq; TYPE_1__* ddev; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq_enabled; } ;

/* Variables and functions */
 int RADEON_MAX_HPD_PINS ; 
 int /*<<< orphan*/  radeon_irq_set (struct radeon_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void radeon_irq_kms_disable_hpd(struct radeon_device *rdev, unsigned hpd_mask)
{
	unsigned long irqflags;
	int i;

	if (!rdev->ddev->irq_enabled)
		return;

	spin_lock_irqsave(&rdev->irq.lock, irqflags);
	for (i = 0; i < RADEON_MAX_HPD_PINS; ++i)
		rdev->irq.hpd[i] &= !(hpd_mask & (1 << i));
	radeon_irq_set(rdev);
	spin_unlock_irqrestore(&rdev->irq.lock, irqflags);
}