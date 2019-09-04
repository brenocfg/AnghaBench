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
struct tegra_gpio_info {int /*<<< orphan*/  irq_domain; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 struct tegra_gpio_info* gpiochip_get_data (struct gpio_chip*) ; 
 int irq_find_mapping (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int tegra_gpio_to_irq(struct gpio_chip *chip, unsigned int offset)
{
	struct tegra_gpio_info *tgi = gpiochip_get_data(chip);

	return irq_find_mapping(tgi->irq_domain, offset);
}