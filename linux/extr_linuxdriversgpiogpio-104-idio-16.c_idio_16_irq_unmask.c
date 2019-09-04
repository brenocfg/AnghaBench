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
struct irq_data {int dummy; } ;
struct idio_16_gpio {unsigned long irq_mask; int /*<<< orphan*/  lock; scalar_t__ base; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 unsigned long BIT (int /*<<< orphan*/ ) ; 
 struct idio_16_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void idio_16_irq_unmask(struct irq_data *data)
{
	struct gpio_chip *chip = irq_data_get_irq_chip_data(data);
	struct idio_16_gpio *const idio16gpio = gpiochip_get_data(chip);
	const unsigned long mask = BIT(irqd_to_hwirq(data));
	const unsigned long prev_irq_mask = idio16gpio->irq_mask;
	unsigned long flags;

	idio16gpio->irq_mask |= mask;

	if (!prev_irq_mask) {
		raw_spin_lock_irqsave(&idio16gpio->lock, flags);

		inb(idio16gpio->base + 2);

		raw_spin_unlock_irqrestore(&idio16gpio->lock, flags);
	}
}