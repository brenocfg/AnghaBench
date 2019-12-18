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
struct lp87565_gpio {int /*<<< orphan*/  map; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 int /*<<< orphan*/  LP87565_REG_GPIO_OUT ; 
 struct lp87565_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lp87565_gpio_set(struct gpio_chip *chip, unsigned int offset,
			     int value)
{
	struct lp87565_gpio *gpio = gpiochip_get_data(chip);

	regmap_update_bits(gpio->map, LP87565_REG_GPIO_OUT,
			   BIT(offset), value ? BIT(offset) : 0);
}