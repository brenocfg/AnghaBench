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
 unsigned int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPIO_BIT (unsigned int) ; 
 int /*<<< orphan*/  GPIO_IN (struct tegra_gpio_info*,unsigned int) ; 
 int /*<<< orphan*/  GPIO_OE (struct tegra_gpio_info*,unsigned int) ; 
 int /*<<< orphan*/  GPIO_OUT (struct tegra_gpio_info*,unsigned int) ; 
 struct tegra_gpio_info* gpiochip_get_data (struct gpio_chip*) ; 
 unsigned int tegra_gpio_readl (struct tegra_gpio_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_gpio_get(struct gpio_chip *chip, unsigned int offset)
{
	struct tegra_gpio_info *tgi = gpiochip_get_data(chip);
	unsigned int bval = BIT(GPIO_BIT(offset));

	/* If gpio is in output mode then read from the out value */
	if (tegra_gpio_readl(tgi, GPIO_OE(tgi, offset)) & bval)
		return !!(tegra_gpio_readl(tgi, GPIO_OUT(tgi, offset)) & bval);

	return !!(tegra_gpio_readl(tgi, GPIO_IN(tgi, offset)) & bval);
}