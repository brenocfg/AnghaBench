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
struct irq_data {unsigned int hwirq; } ;
struct gpio_bank {int /*<<< orphan*/  lock; int /*<<< orphan*/  irq_usage; int /*<<< orphan*/  mod_usage; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int /*<<< orphan*/  LINE_USED (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  omap_enable_gpio_module (struct gpio_bank*,unsigned int) ; 
 int /*<<< orphan*/  omap_gpio_unmask_irq (struct irq_data*) ; 
 struct gpio_bank* omap_irq_data_get_bank (struct irq_data*) ; 
 int /*<<< orphan*/  omap_set_gpio_direction (struct gpio_bank*,unsigned int,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned int omap_gpio_irq_startup(struct irq_data *d)
{
	struct gpio_bank *bank = omap_irq_data_get_bank(d);
	unsigned long flags;
	unsigned offset = d->hwirq;

	raw_spin_lock_irqsave(&bank->lock, flags);

	if (!LINE_USED(bank->mod_usage, offset))
		omap_set_gpio_direction(bank, offset, 1);
	omap_enable_gpio_module(bank, offset);
	bank->irq_usage |= BIT(offset);

	raw_spin_unlock_irqrestore(&bank->lock, flags);
	omap_gpio_unmask_irq(d);

	return 0;
}