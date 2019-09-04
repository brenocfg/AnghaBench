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
struct ws16c48_gpio {unsigned long* io_state; unsigned int* out_state; int /*<<< orphan*/  lock; scalar_t__ base; } ;
struct gpio_chip {unsigned int ngpio; } ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 size_t BIT_WORD (unsigned int) ; 
 struct ws16c48_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ws16c48_gpio_set_multiple(struct gpio_chip *chip,
	unsigned long *mask, unsigned long *bits)
{
	struct ws16c48_gpio *const ws16c48gpio = gpiochip_get_data(chip);
	unsigned int i;
	const unsigned int gpio_reg_size = 8;
	unsigned int port;
	unsigned int iomask;
	unsigned int bitmask;
	unsigned long flags;

	/* set bits are evaluated a gpio register size at a time */
	for (i = 0; i < chip->ngpio; i += gpio_reg_size) {
		/* no more set bits in this mask word; skip to the next word */
		if (!mask[BIT_WORD(i)]) {
			i = (BIT_WORD(i) + 1) * BITS_PER_LONG - gpio_reg_size;
			continue;
		}

		port = i / gpio_reg_size;

		/* mask out GPIO configured for input */
		iomask = mask[BIT_WORD(i)] & ~ws16c48gpio->io_state[port];
		bitmask = iomask & bits[BIT_WORD(i)];

		raw_spin_lock_irqsave(&ws16c48gpio->lock, flags);

		/* update output state data and set device gpio register */
		ws16c48gpio->out_state[port] &= ~iomask;
		ws16c48gpio->out_state[port] |= bitmask;
		outb(ws16c48gpio->out_state[port], ws16c48gpio->base + port);

		raw_spin_unlock_irqrestore(&ws16c48gpio->lock, flags);

		/* prepare for next gpio register set */
		mask[BIT_WORD(i)] >>= gpio_reg_size;
		bits[BIT_WORD(i)] >>= gpio_reg_size;
	}
}