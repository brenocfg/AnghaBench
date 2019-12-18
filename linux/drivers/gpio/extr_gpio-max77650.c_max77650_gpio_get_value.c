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
struct max77650_gpio_chip {int /*<<< orphan*/  map; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int MAX77650_GPIO_INVAL_BITS (unsigned int) ; 
 int /*<<< orphan*/  MAX77650_REG_CNFG_GPIO ; 
 struct max77650_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int max77650_gpio_get_value(struct gpio_chip *gc,
				   unsigned int offset)
{
	struct max77650_gpio_chip *chip = gpiochip_get_data(gc);
	unsigned int val;
	int rv;

	rv = regmap_read(chip->map, MAX77650_REG_CNFG_GPIO, &val);
	if (rv)
		return rv;

	return MAX77650_GPIO_INVAL_BITS(val);
}