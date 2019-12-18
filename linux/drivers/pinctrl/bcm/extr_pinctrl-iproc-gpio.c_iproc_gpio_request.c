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
struct iproc_gpio {int /*<<< orphan*/  pinmux_is_supported; } ;
struct gpio_chip {unsigned int base; } ;

/* Variables and functions */
 struct iproc_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int pinctrl_gpio_request (unsigned int) ; 

__attribute__((used)) static int iproc_gpio_request(struct gpio_chip *gc, unsigned offset)
{
	struct iproc_gpio *chip = gpiochip_get_data(gc);
	unsigned gpio = gc->base + offset;

	/* not all Iproc GPIO pins can be muxed individually */
	if (!chip->pinmux_is_supported)
		return 0;

	return pinctrl_gpio_request(gpio);
}