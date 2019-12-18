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
struct gpio_chip {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX77650_GPIO_OUTVAL_MASK ; 
 int MAX77650_GPIO_OUT_HIGH ; 
 int MAX77650_GPIO_OUT_LOW ; 
 int /*<<< orphan*/  MAX77650_REG_CNFG_GPIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct max77650_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void max77650_gpio_set_value(struct gpio_chip *gc,
				    unsigned int offset, int value)
{
	struct max77650_gpio_chip *chip = gpiochip_get_data(gc);
	int rv, regval;

	regval = value ? MAX77650_GPIO_OUT_HIGH : MAX77650_GPIO_OUT_LOW;

	rv = regmap_update_bits(chip->map, MAX77650_REG_CNFG_GPIO,
				MAX77650_GPIO_OUTVAL_MASK, regval);
	if (rv)
		dev_err(gc->parent, "cannot set GPIO value: %d\n", rv);
}