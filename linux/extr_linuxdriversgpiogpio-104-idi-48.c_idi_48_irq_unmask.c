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
struct idi_48_gpio {unsigned int* irq_mask; unsigned int cos_enb; int /*<<< orphan*/  lock; scalar_t__ base; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 unsigned int BIT (unsigned int const) ; 
 struct idi_48_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 struct gpio_chip* irq_data_get_irq_chip_data (struct irq_data*) ; 
 unsigned int irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void idi_48_irq_unmask(struct irq_data *data)
{
	struct gpio_chip *chip = irq_data_get_irq_chip_data(data);
	struct idi_48_gpio *const idi48gpio = gpiochip_get_data(chip);
	const unsigned offset = irqd_to_hwirq(data);
	unsigned i;
	unsigned mask;
	unsigned boundary;
	unsigned prev_irq_mask;
	unsigned long flags;

	for (i = 0; i < 48; i += 8)
		if (offset < i + 8) {
			mask = BIT(offset - i);
			boundary = i / 8;
			prev_irq_mask = idi48gpio->irq_mask[boundary];

			idi48gpio->irq_mask[boundary] |= mask;

			if (!prev_irq_mask) {
				idi48gpio->cos_enb |= BIT(boundary);

				raw_spin_lock_irqsave(&idi48gpio->lock, flags);

				outb(idi48gpio->cos_enb, idi48gpio->base + 7);

				raw_spin_unlock_irqrestore(&idi48gpio->lock,
						           flags);
			}

			return;
		}
}