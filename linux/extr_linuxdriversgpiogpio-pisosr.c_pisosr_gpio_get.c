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
struct pisosr_gpio {unsigned int* buffer; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct pisosr_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  pisosr_gpio_refresh (struct pisosr_gpio*) ; 

__attribute__((used)) static int pisosr_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	struct pisosr_gpio *gpio = gpiochip_get_data(chip);

	/* Refresh may not always be needed */
	pisosr_gpio_refresh(gpio);

	return (gpio->buffer[offset / 8] >> (offset % 8)) & 0x1;
}