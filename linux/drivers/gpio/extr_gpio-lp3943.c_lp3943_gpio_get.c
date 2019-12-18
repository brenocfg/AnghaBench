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
struct lp3943_gpio {int input_mask; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 struct lp3943_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int lp3943_get_gpio_in_status (struct lp3943_gpio*,struct gpio_chip*,unsigned int) ; 
 int lp3943_get_gpio_out_status (struct lp3943_gpio*,struct gpio_chip*,unsigned int) ; 

__attribute__((used)) static int lp3943_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	struct lp3943_gpio *lp3943_gpio = gpiochip_get_data(chip);

	/*
	 * Limitation:
	 *   LP3943 doesn't have the GPIO direction register. It provides
	 *   only input and output status registers.
	 *   So, direction info is required to handle the 'get' operation.
	 *   This variable is updated whenever the direction is changed and
	 *   it is used here.
	 */

	if (lp3943_gpio->input_mask & BIT(offset))
		return lp3943_get_gpio_in_status(lp3943_gpio, chip, offset);
	else
		return lp3943_get_gpio_out_status(lp3943_gpio, chip, offset);
}