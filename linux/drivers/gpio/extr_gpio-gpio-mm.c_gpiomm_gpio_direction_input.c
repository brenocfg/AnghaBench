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
struct gpiomm_gpio {int base; int* io_state; unsigned int* control; int /*<<< orphan*/  lock; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 unsigned int BIT (int) ; 
 struct gpiomm_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  outb (unsigned int,unsigned int const) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int gpiomm_gpio_direction_input(struct gpio_chip *chip,
	unsigned int offset)
{
	struct gpiomm_gpio *const gpiommgpio = gpiochip_get_data(chip);
	const unsigned int io_port = offset / 8;
	const unsigned int control_port = io_port / 3;
	const unsigned int control_addr = gpiommgpio->base + 3 + control_port*4;
	unsigned long flags;
	unsigned int control;

	spin_lock_irqsave(&gpiommgpio->lock, flags);

	/* Check if configuring Port C */
	if (io_port == 2 || io_port == 5) {
		/* Port C can be configured by nibble */
		if (offset % 8 > 3) {
			gpiommgpio->io_state[io_port] |= 0xF0;
			gpiommgpio->control[control_port] |= BIT(3);
		} else {
			gpiommgpio->io_state[io_port] |= 0x0F;
			gpiommgpio->control[control_port] |= BIT(0);
		}
	} else {
		gpiommgpio->io_state[io_port] |= 0xFF;
		if (io_port == 0 || io_port == 3)
			gpiommgpio->control[control_port] |= BIT(4);
		else
			gpiommgpio->control[control_port] |= BIT(1);
	}

	control = BIT(7) | gpiommgpio->control[control_port];
	outb(control, control_addr);

	spin_unlock_irqrestore(&gpiommgpio->lock, flags);

	return 0;
}