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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_pmc {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMC_CNTRL ; 
 int /*<<< orphan*/  PMC_CNTRL_INTR_POLARITY ; 
 int /*<<< orphan*/  tegra_pmc_readl (struct tegra_pmc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_pmc_writel (struct tegra_pmc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra20_pmc_setup_irq_polarity(struct tegra_pmc *pmc,
					   struct device_node *np,
					   bool invert)
{
	u32 value;

	value = tegra_pmc_readl(pmc, PMC_CNTRL);

	if (invert)
		value |= PMC_CNTRL_INTR_POLARITY;
	else
		value &= ~PMC_CNTRL_INTR_POLARITY;

	tegra_pmc_writel(pmc, value, PMC_CNTRL);
}