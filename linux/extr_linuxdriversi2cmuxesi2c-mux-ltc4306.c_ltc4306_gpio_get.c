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
 unsigned int BIT (int) ; 
 int /*<<< orphan*/  LTC_REG_CONFIG ; 
 struct ltc4306* gpiochip_get_data (struct gpio_chip*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int ltc4306_gpio_get(struct gpio_chip *chip, unsigned int offset)
{
	struct ltc4306 *data = gpiochip_get_data(chip);
	unsigned int val;
	int ret;

	ret = regmap_read(data->regmap, LTC_REG_CONFIG, &val);
	if (ret < 0)
		return ret;

	return !!(val & BIT(1 - offset));
}