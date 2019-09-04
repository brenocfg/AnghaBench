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
struct gpio_chip {scalar_t__ base; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  have_gpio (int /*<<< orphan*/ ,unsigned int) ; 
 int pinctrl_gpio_request (scalar_t__) ; 

__attribute__((used)) static int aspeed_gpio_request(struct gpio_chip *chip, unsigned int offset)
{
	if (!have_gpio(gpiochip_get_data(chip), offset))
		return -ENODEV;

	return pinctrl_gpio_request(chip->base + offset);
}