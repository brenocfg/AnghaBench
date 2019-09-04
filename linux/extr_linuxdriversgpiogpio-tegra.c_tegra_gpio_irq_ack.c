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
struct tegra_gpio_bank {struct tegra_gpio_info* tgi; } ;
struct irq_data {unsigned int hwirq; } ;

/* Variables and functions */
 int GPIO_BIT (unsigned int) ; 
 int /*<<< orphan*/  GPIO_INT_CLR (struct tegra_gpio_info*,unsigned int) ; 
 struct tegra_gpio_bank* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  tegra_gpio_writel (struct tegra_gpio_info*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_gpio_irq_ack(struct irq_data *d)
{
	struct tegra_gpio_bank *bank = irq_data_get_irq_chip_data(d);
	struct tegra_gpio_info *tgi = bank->tgi;
	unsigned int gpio = d->hwirq;

	tegra_gpio_writel(tgi, 1 << GPIO_BIT(gpio), GPIO_INT_CLR(tgi, gpio));
}