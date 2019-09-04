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
struct ltc4306 {int /*<<< orphan*/  regmap; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  LTC_REG_MODE ; 
 struct ltc4306* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  ltc4306_gpio_set (struct gpio_chip*,unsigned int,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ltc4306_gpio_direction_output(struct gpio_chip *chip,
					 unsigned int offset, int value)
{
	struct ltc4306 *data = gpiochip_get_data(chip);

	ltc4306_gpio_set(chip, offset, value);
	return regmap_update_bits(data->regmap, LTC_REG_MODE,
				  BIT(7 - offset), 0);
}