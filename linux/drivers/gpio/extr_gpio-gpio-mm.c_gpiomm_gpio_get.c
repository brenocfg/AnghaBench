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
struct gpiomm_gpio {unsigned int const* io_state; int /*<<< orphan*/  lock; scalar_t__ base; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 unsigned int BIT (unsigned int) ; 
 int EINVAL ; 
 struct gpiomm_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 unsigned int inb (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int gpiomm_gpio_get(struct gpio_chip *chip, unsigned int offset)
{
	struct gpiomm_gpio *const gpiommgpio = gpiochip_get_data(chip);
	const unsigned int port = offset / 8;
	const unsigned int mask = BIT(offset % 8);
	const unsigned int in_port = (port > 2) ? port + 1 : port;
	unsigned long flags;
	unsigned int port_state;

	spin_lock_irqsave(&gpiommgpio->lock, flags);

	/* ensure that GPIO is set for input */
	if (!(gpiommgpio->io_state[port] & mask)) {
		spin_unlock_irqrestore(&gpiommgpio->lock, flags);
		return -EINVAL;
	}

	port_state = inb(gpiommgpio->base + in_port);

	spin_unlock_irqrestore(&gpiommgpio->lock, flags);

	return !!(port_state & mask);
}