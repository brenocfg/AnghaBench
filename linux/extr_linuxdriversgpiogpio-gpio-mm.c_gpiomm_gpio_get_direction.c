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
struct gpiomm_gpio {unsigned int const* io_state; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 unsigned int BIT (unsigned int) ; 
 struct gpiomm_gpio* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static int gpiomm_gpio_get_direction(struct gpio_chip *chip,
	unsigned int offset)
{
	struct gpiomm_gpio *const gpiommgpio = gpiochip_get_data(chip);
	const unsigned int port = offset / 8;
	const unsigned int mask = BIT(offset % 8);

	return !!(gpiommgpio->io_state[port] & mask);
}