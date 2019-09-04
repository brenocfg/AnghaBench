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
struct wake_irq {int status; int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {struct wake_irq* wakeirq; } ;
struct device {TYPE_1__ power; } ;

/* Variables and functions */
 int WAKE_IRQ_DEDICATED_MANAGED ; 
 int WAKE_IRQ_DEDICATED_MASK ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 

void dev_pm_enable_wake_irq_check(struct device *dev,
				  bool can_change_status)
{
	struct wake_irq *wirq = dev->power.wakeirq;

	if (!wirq || !((wirq->status & WAKE_IRQ_DEDICATED_MASK)))
		return;

	if (likely(wirq->status & WAKE_IRQ_DEDICATED_MANAGED)) {
		goto enable;
	} else if (can_change_status) {
		wirq->status |= WAKE_IRQ_DEDICATED_MANAGED;
		goto enable;
	}

	return;

enable:
	enable_irq(wirq->irq);
}