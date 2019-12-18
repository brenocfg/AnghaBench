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
struct nmk_gpio_chip {int /*<<< orphan*/  clk; scalar_t__ addr; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 scalar_t__ NMK_GPIO_DIR ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 struct nmk_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int nmk_gpio_get_dir(struct gpio_chip *chip, unsigned offset)
{
	struct nmk_gpio_chip *nmk_chip = gpiochip_get_data(chip);
	int dir;

	clk_enable(nmk_chip->clk);

	dir = !(readl(nmk_chip->addr + NMK_GPIO_DIR) & BIT(offset));

	clk_disable(nmk_chip->clk);

	return dir;
}