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
struct tegra_pmc {scalar_t__ sysclkreq_high; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMC_CNTRL ; 
 int /*<<< orphan*/  PMC_CNTRL_CPU_PWRREQ_OE ; 
 int /*<<< orphan*/  PMC_CNTRL_SYSCLK_OE ; 
 int /*<<< orphan*/  PMC_CNTRL_SYSCLK_POLARITY ; 
 int /*<<< orphan*/  tegra_pmc_readl (struct tegra_pmc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_pmc_writel (struct tegra_pmc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra20_pmc_init(struct tegra_pmc *pmc)
{
	u32 value;

	/* Always enable CPU power request */
	value = tegra_pmc_readl(pmc, PMC_CNTRL);
	value |= PMC_CNTRL_CPU_PWRREQ_OE;
	tegra_pmc_writel(pmc, value, PMC_CNTRL);

	value = tegra_pmc_readl(pmc, PMC_CNTRL);

	if (pmc->sysclkreq_high)
		value &= ~PMC_CNTRL_SYSCLK_POLARITY;
	else
		value |= PMC_CNTRL_SYSCLK_POLARITY;

	/* configure the output polarity while the request is tristated */
	tegra_pmc_writel(pmc, value, PMC_CNTRL);

	/* now enable the request */
	value = tegra_pmc_readl(pmc, PMC_CNTRL);
	value |= PMC_CNTRL_SYSCLK_OE;
	tegra_pmc_writel(pmc, value, PMC_CNTRL);
}