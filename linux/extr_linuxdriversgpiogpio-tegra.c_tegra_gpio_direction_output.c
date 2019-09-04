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
struct tegra_gpio_info {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_MSK_OE (struct tegra_gpio_info*,unsigned int) ; 
 struct tegra_gpio_info* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  tegra_gpio_enable (struct tegra_gpio_info*,unsigned int) ; 
 int /*<<< orphan*/  tegra_gpio_mask_write (struct tegra_gpio_info*,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  tegra_gpio_set (struct gpio_chip*,unsigned int,int) ; 

__attribute__((used)) static int tegra_gpio_direction_output(struct gpio_chip *chip,
				       unsigned int offset,
				       int value)
{
	struct tegra_gpio_info *tgi = gpiochip_get_data(chip);

	tegra_gpio_set(chip, offset, value);
	tegra_gpio_mask_write(tgi, GPIO_MSK_OE(tgi, offset), offset, 1);
	tegra_gpio_enable(tgi, offset);
	return 0;
}