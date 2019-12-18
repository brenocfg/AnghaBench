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
struct gpiomm_gpio {unsigned long* out_state; int /*<<< orphan*/  lock; scalar_t__ base; } ;
struct gpio_chip {unsigned int ngpio; } ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 size_t BIT_WORD (unsigned int) ; 
 struct gpiomm_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  outb (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void gpiomm_gpio_set_multiple(struct gpio_chip *chip,
	unsigned long *mask, unsigned long *bits)
{
	struct gpiomm_gpio *const gpiommgpio = gpiochip_get_data(chip);
	unsigned int i;
	const unsigned int gpio_reg_size = 8;
	unsigned int port;
	unsigned int out_port;
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
		out_port = (port > 2) ? port + 1 : port;
		bitmask = mask[BIT_WORD(i)] & bits[BIT_WORD(i)];

		spin_lock_irqsave(&gpiommgpio->lock, flags);

		/* update output state data and set device gpio register */
		gpiommgpio->out_state[port] &= ~mask[BIT_WORD(i)];
		gpiommgpio->out_state[port] |= bitmask;
		outb(gpiommgpio->out_state[port], gpiommgpio->base + out_port);

		spin_unlock_irqrestore(&gpiommgpio->lock, flags);

		/* prepare for next gpio register set */
		mask[BIT_WORD(i)] >>= gpio_reg_size;
		bits[BIT_WORD(i)] >>= gpio_reg_size;
	}
}