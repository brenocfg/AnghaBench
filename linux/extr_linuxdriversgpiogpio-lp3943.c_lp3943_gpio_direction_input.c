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
struct lp3943_gpio {int /*<<< orphan*/  input_mask; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int /*<<< orphan*/  LP3943_GPIO_IN ; 
 struct lp3943_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int lp3943_gpio_set_mode (struct lp3943_gpio*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lp3943_gpio_direction_input(struct gpio_chip *chip, unsigned offset)
{
	struct lp3943_gpio *lp3943_gpio = gpiochip_get_data(chip);

	lp3943_gpio->input_mask |= BIT(offset);

	return lp3943_gpio_set_mode(lp3943_gpio, offset, LP3943_GPIO_IN);
}