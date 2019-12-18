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
typedef  int u32 ;
struct tegra_pmc {scalar_t__ wake; } ;
struct irq_data {int hwirq; } ;

/* Variables and functions */
 int ULONG_MAX ; 
 scalar_t__ WAKE_AOWAKE_MASK_W (int) ; 
 scalar_t__ WAKE_AOWAKE_STATUS_W (int) ; 
 scalar_t__ WAKE_AOWAKE_TIER2_ROUTING (unsigned int) ; 
 scalar_t__ WARN_ON (int) ; 
 struct tegra_pmc* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int tegra_pmc_irq_set_wake(struct irq_data *data, unsigned int on)
{
	struct tegra_pmc *pmc = irq_data_get_irq_chip_data(data);
	unsigned int offset, bit;
	u32 value;

	/* nothing to do if there's no associated wake event */
	if (WARN_ON(data->hwirq == ULONG_MAX))
		return 0;

	offset = data->hwirq / 32;
	bit = data->hwirq % 32;

	/* clear wake status */
	writel(0x1, pmc->wake + WAKE_AOWAKE_STATUS_W(data->hwirq));

	/* route wake to tier 2 */
	value = readl(pmc->wake + WAKE_AOWAKE_TIER2_ROUTING(offset));

	if (!on)
		value &= ~(1 << bit);
	else
		value |= 1 << bit;

	writel(value, pmc->wake + WAKE_AOWAKE_TIER2_ROUTING(offset));

	/* enable wakeup event */
	writel(!!on, pmc->wake + WAKE_AOWAKE_MASK_W(data->hwirq));

	return 0;
}