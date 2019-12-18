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
struct tegra_pcie_soc {int num_ports; int /*<<< orphan*/  pads_refclk_cfg1; int /*<<< orphan*/  pads_refclk_cfg0; } ;
struct tegra_pcie {struct tegra_pcie_soc* soc; } ;

/* Variables and functions */
 int /*<<< orphan*/  PADS_REFCLK_CFG0 ; 
 int /*<<< orphan*/  PADS_REFCLK_CFG1 ; 
 int /*<<< orphan*/  pads_writel (struct tegra_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_pcie_apply_pad_settings(struct tegra_pcie *pcie)
{
	const struct tegra_pcie_soc *soc = pcie->soc;

	/* Configure the reference clock driver */
	pads_writel(pcie, soc->pads_refclk_cfg0, PADS_REFCLK_CFG0);

	if (soc->num_ports > 2)
		pads_writel(pcie, soc->pads_refclk_cfg1, PADS_REFCLK_CFG1);
}