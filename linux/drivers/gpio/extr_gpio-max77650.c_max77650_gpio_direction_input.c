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
 int /*<<< orphan*/  MAX77650_GPIO_DIR_IN ; 
 int /*<<< orphan*/  MAX77650_GPIO_DIR_MASK ; 
 int /*<<< orphan*/  MAX77650_REG_CNFG_GPIO ; 
 struct max77650_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max77650_gpio_direction_input(struct gpio_chip *gc,
					 unsigned int offset)
{
	struct max77650_gpio_chip *chip = gpiochip_get_data(gc);

	return regmap_update_bits(chip->map,
				  MAX77650_REG_CNFG_GPIO,
				  MAX77650_GPIO_DIR_MASK,
				  MAX77650_GPIO_DIR_IN);
}