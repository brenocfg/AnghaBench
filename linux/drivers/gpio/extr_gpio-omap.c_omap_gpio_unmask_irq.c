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
typedef  int u32 ;
struct irq_data {unsigned int hwirq; } ;
struct gpio_bank {int /*<<< orphan*/  lock; TYPE_1__* regs; } ;
struct TYPE_2__ {scalar_t__ wkup_en; scalar_t__ leveldetect0; } ;

/* Variables and functions */
 int IRQ_TYPE_LEVEL_HIGH ; 
 int IRQ_TYPE_LEVEL_LOW ; 
 int irqd_get_trigger_type (struct irq_data*) ; 
 int /*<<< orphan*/  omap_clear_gpio_irqstatus (struct gpio_bank*,unsigned int) ; 
 struct gpio_bank* omap_irq_data_get_bank (struct irq_data*) ; 
 int /*<<< orphan*/  omap_set_gpio_irqenable (struct gpio_bank*,unsigned int,int) ; 
 int /*<<< orphan*/  omap_set_gpio_triggering (struct gpio_bank*,unsigned int,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void omap_gpio_unmask_irq(struct irq_data *d)
{
	struct gpio_bank *bank = omap_irq_data_get_bank(d);
	unsigned offset = d->hwirq;
	u32 trigger = irqd_get_trigger_type(d);
	unsigned long flags;

	raw_spin_lock_irqsave(&bank->lock, flags);
	omap_set_gpio_irqenable(bank, offset, 1);

	/*
	 * For level-triggered GPIOs, clearing must be done after the source
	 * is cleared, thus after the handler has run. OMAP4 needs this done
	 * after enabing the interrupt to clear the wakeup status.
	 */
	if (bank->regs->leveldetect0 && bank->regs->wkup_en &&
	    trigger & (IRQ_TYPE_LEVEL_HIGH | IRQ_TYPE_LEVEL_LOW))
		omap_clear_gpio_irqstatus(bank, offset);

	if (trigger)
		omap_set_gpio_triggering(bank, offset, trigger);

	raw_spin_unlock_irqrestore(&bank->lock, flags);
}