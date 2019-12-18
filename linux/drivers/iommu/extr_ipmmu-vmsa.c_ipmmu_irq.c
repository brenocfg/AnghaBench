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
struct ipmmu_vmsa_device {unsigned int num_ctx; int /*<<< orphan*/  lock; int /*<<< orphan*/ * domains; } ;
typedef  scalar_t__ irqreturn_t ;

/* Variables and functions */
 scalar_t__ IRQ_HANDLED ; 
 scalar_t__ IRQ_NONE ; 
 scalar_t__ ipmmu_domain_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t ipmmu_irq(int irq, void *dev)
{
	struct ipmmu_vmsa_device *mmu = dev;
	irqreturn_t status = IRQ_NONE;
	unsigned int i;
	unsigned long flags;

	spin_lock_irqsave(&mmu->lock, flags);

	/*
	 * Check interrupts for all active contexts.
	 */
	for (i = 0; i < mmu->num_ctx; i++) {
		if (!mmu->domains[i])
			continue;
		if (ipmmu_domain_irq(mmu->domains[i]) == IRQ_HANDLED)
			status = IRQ_HANDLED;
	}

	spin_unlock_irqrestore(&mmu->lock, flags);

	return status;
}