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
struct wake_irq {int status; struct wake_irq* name; int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; struct wake_irq* wakeirq; } ;
struct device {TYPE_1__ power; } ;

/* Variables and functions */
 int WAKE_IRQ_DEDICATED_ALLOCATED ; 
 int WAKE_IRQ_DEDICATED_MASK ; 
 int /*<<< orphan*/  device_wakeup_detach_irq (struct device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct wake_irq*) ; 
 int /*<<< orphan*/  kfree (struct wake_irq*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void dev_pm_clear_wake_irq(struct device *dev)
{
	struct wake_irq *wirq = dev->power.wakeirq;
	unsigned long flags;

	if (!wirq)
		return;

	spin_lock_irqsave(&dev->power.lock, flags);
	device_wakeup_detach_irq(dev);
	dev->power.wakeirq = NULL;
	spin_unlock_irqrestore(&dev->power.lock, flags);

	if (wirq->status & WAKE_IRQ_DEDICATED_ALLOCATED) {
		free_irq(wirq->irq, wirq);
		wirq->status &= ~WAKE_IRQ_DEDICATED_MASK;
	}
	kfree(wirq->name);
	kfree(wirq);
}