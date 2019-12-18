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
typedef  int /*<<< orphan*/  u8 ;
struct max77620_gpio {int /*<<< orphan*/  dev; int /*<<< orphan*/  rmap; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_REG_ADDR (unsigned int) ; 
 int /*<<< orphan*/  MAX77620_CNFG_GPIO_OUTPUT_VAL_HIGH ; 
 int /*<<< orphan*/  MAX77620_CNFG_GPIO_OUTPUT_VAL_LOW ; 
 int /*<<< orphan*/  MAX77620_CNFG_GPIO_OUTPUT_VAL_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct max77620_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void max77620_gpio_set(struct gpio_chip *gc, unsigned int offset,
			      int value)
{
	struct max77620_gpio *mgpio = gpiochip_get_data(gc);
	u8 val;
	int ret;

	val = (value) ? MAX77620_CNFG_GPIO_OUTPUT_VAL_HIGH :
				MAX77620_CNFG_GPIO_OUTPUT_VAL_LOW;

	ret = regmap_update_bits(mgpio->rmap, GPIO_REG_ADDR(offset),
				 MAX77620_CNFG_GPIO_OUTPUT_VAL_MASK, val);
	if (ret < 0)
		dev_err(mgpio->dev, "CNFG_GPIO_OUT update failed: %d\n", ret);
}