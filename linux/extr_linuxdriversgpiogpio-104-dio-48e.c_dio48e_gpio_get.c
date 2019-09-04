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
struct gpio_chip {int dummy; } ;
struct dio48e_gpio {unsigned int const* io_state; int /*<<< orphan*/  lock; scalar_t__ base; } ;

/* Variables and functions */
 unsigned int BIT (unsigned int) ; 
 int EINVAL ; 
 struct dio48e_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 unsigned int inb (scalar_t__) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dio48e_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	struct dio48e_gpio *const dio48egpio = gpiochip_get_data(chip);
	const unsigned port = offset / 8;
	const unsigned mask = BIT(offset % 8);
	const unsigned in_port = (port > 2) ? port + 1 : port;
	unsigned long flags;
	unsigned port_state;

	raw_spin_lock_irqsave(&dio48egpio->lock, flags);

	/* ensure that GPIO is set for input */
	if (!(dio48egpio->io_state[port] & mask)) {
		raw_spin_unlock_irqrestore(&dio48egpio->lock, flags);
		return -EINVAL;
	}

	port_state = inb(dio48egpio->base + in_port);

	raw_spin_unlock_irqrestore(&dio48egpio->lock, flags);

	return !!(port_state & mask);
}