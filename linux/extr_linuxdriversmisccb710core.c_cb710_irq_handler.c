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
struct cb710_slot {scalar_t__ (* irq_handler ) (struct cb710_slot*) ;} ;
struct cb710_chip {unsigned int slots; int /*<<< orphan*/  irq_lock; struct cb710_slot* slot; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  scalar_t__ (* cb710_irq_handler_t ) (struct cb710_slot*) ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t cb710_irq_handler(int irq, void *data)
{
	struct cb710_chip *chip = data;
	struct cb710_slot *slot = &chip->slot[0];
	irqreturn_t handled = IRQ_NONE;
	unsigned nr;

	spin_lock(&chip->irq_lock); /* incl. smp_rmb() */

	for (nr = chip->slots; nr; ++slot, --nr) {
		cb710_irq_handler_t handler_func = slot->irq_handler;
		if (handler_func && handler_func(slot))
			handled = IRQ_HANDLED;
	}

	spin_unlock(&chip->irq_lock);

	return handled;
}