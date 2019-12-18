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
struct gpio_chip {scalar_t__ base; } ;

/* Variables and functions */
 struct tegra_gpio_info* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  pinctrl_gpio_free (scalar_t__) ; 
 int /*<<< orphan*/  tegra_gpio_disable (struct tegra_gpio_info*,unsigned int) ; 

__attribute__((used)) static void tegra_gpio_free(struct gpio_chip *chip, unsigned int offset)
{
	struct tegra_gpio_info *tgi = gpiochip_get_data(chip);

	pinctrl_gpio_free(chip->base + offset);
	tegra_gpio_disable(tgi, offset);
}