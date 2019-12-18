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
struct gpio_bank {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 struct gpio_bank* omap_irq_data_get_bank (struct irq_data*) ; 
 int /*<<< orphan*/  omap_set_gpio_irqenable (struct gpio_bank*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_set_gpio_triggering (struct gpio_bank*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void omap_gpio_mask_irq(struct irq_data *d)
{
	struct gpio_bank *bank = omap_irq_data_get_bank(d);
	unsigned offset = d->hwirq;
	unsigned long flags;

	raw_spin_lock_irqsave(&bank->lock, flags);
	omap_set_gpio_triggering(bank, offset, IRQ_TYPE_NONE);
	omap_set_gpio_irqenable(bank, offset, 0);
	raw_spin_unlock_irqrestore(&bank->lock, flags);
}