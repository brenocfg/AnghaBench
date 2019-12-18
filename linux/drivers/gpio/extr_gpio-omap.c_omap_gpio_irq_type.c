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
struct irq_data {unsigned int hwirq; } ;
struct gpio_bank {int /*<<< orphan*/  lock; TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  leveldetect0; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int IRQ_TYPE_EDGE_FALLING ; 
 unsigned int IRQ_TYPE_EDGE_RISING ; 
 unsigned int IRQ_TYPE_LEVEL_HIGH ; 
 unsigned int IRQ_TYPE_LEVEL_LOW ; 
 unsigned int IRQ_TYPE_SENSE_MASK ; 
 int /*<<< orphan*/  handle_level_irq ; 
 int /*<<< orphan*/  handle_simple_irq ; 
 int /*<<< orphan*/  irq_set_handler_locked (struct irq_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_gpio_init_irq (struct gpio_bank*,unsigned int) ; 
 int /*<<< orphan*/  omap_gpio_is_input (struct gpio_bank*,unsigned int) ; 
 struct gpio_bank* omap_irq_data_get_bank (struct irq_data*) ; 
 int omap_set_gpio_triggering (struct gpio_bank*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int omap_gpio_irq_type(struct irq_data *d, unsigned type)
{
	struct gpio_bank *bank = omap_irq_data_get_bank(d);
	int retval;
	unsigned long flags;
	unsigned offset = d->hwirq;

	if (type & ~IRQ_TYPE_SENSE_MASK)
		return -EINVAL;

	if (!bank->regs->leveldetect0 &&
		(type & (IRQ_TYPE_LEVEL_LOW|IRQ_TYPE_LEVEL_HIGH)))
		return -EINVAL;

	raw_spin_lock_irqsave(&bank->lock, flags);
	retval = omap_set_gpio_triggering(bank, offset, type);
	if (retval) {
		raw_spin_unlock_irqrestore(&bank->lock, flags);
		goto error;
	}
	omap_gpio_init_irq(bank, offset);
	if (!omap_gpio_is_input(bank, offset)) {
		raw_spin_unlock_irqrestore(&bank->lock, flags);
		retval = -EINVAL;
		goto error;
	}
	raw_spin_unlock_irqrestore(&bank->lock, flags);

	if (type & (IRQ_TYPE_LEVEL_LOW | IRQ_TYPE_LEVEL_HIGH))
		irq_set_handler_locked(d, handle_level_irq);
	else if (type & (IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_EDGE_RISING))
		/*
		 * Edge IRQs are already cleared/acked in irq_handler and
		 * not need to be masked, as result handle_edge_irq()
		 * logic is excessed here and may cause lose of interrupts.
		 * So just use handle_simple_irq.
		 */
		irq_set_handler_locked(d, handle_simple_irq);

	return 0;

error:
	return retval;
}