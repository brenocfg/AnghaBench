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
struct max77620_gpio {int /*<<< orphan*/  dev; int /*<<< orphan*/  rmap; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_REG_ADDR (unsigned int) ; 
 unsigned int MAX77620_CNFG_GPIO_DIR_MASK ; 
 unsigned int MAX77620_CNFG_GPIO_INPUT_VAL_MASK ; 
 unsigned int MAX77620_CNFG_GPIO_OUTPUT_VAL_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct max77620_gpio* gpiochip_get_data (struct gpio_chip*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int max77620_gpio_get(struct gpio_chip *gc, unsigned int offset)
{
	struct max77620_gpio *mgpio = gpiochip_get_data(gc);
	unsigned int val;
	int ret;

	ret = regmap_read(mgpio->rmap, GPIO_REG_ADDR(offset), &val);
	if (ret < 0) {
		dev_err(mgpio->dev, "CNFG_GPIOx read failed: %d\n", ret);
		return ret;
	}

	if  (val & MAX77620_CNFG_GPIO_DIR_MASK)
		return !!(val & MAX77620_CNFG_GPIO_INPUT_VAL_MASK);
	else
		return !!(val & MAX77620_CNFG_GPIO_OUTPUT_VAL_MASK);
}