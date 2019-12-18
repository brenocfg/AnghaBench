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
struct tegra_pcie_soc {scalar_t__ has_cml_clk; } ;
struct tegra_pcie {int /*<<< orphan*/  supplies; int /*<<< orphan*/  num_supplies; int /*<<< orphan*/  afi_clk; int /*<<< orphan*/  cml_clk; int /*<<< orphan*/  pll_e; int /*<<< orphan*/  afi_rst; struct tegra_pcie_soc* soc; struct device* dev; } ;
struct device {int /*<<< orphan*/  pm_domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEGRA_POWERGATE_PCIE ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 int regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_powergate_power_off (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_pcie_power_off(struct tegra_pcie *pcie)
{
	struct device *dev = pcie->dev;
	const struct tegra_pcie_soc *soc = pcie->soc;
	int err;

	reset_control_assert(pcie->afi_rst);

	clk_disable_unprepare(pcie->pll_e);
	if (soc->has_cml_clk)
		clk_disable_unprepare(pcie->cml_clk);
	clk_disable_unprepare(pcie->afi_clk);

	if (!dev->pm_domain)
		tegra_powergate_power_off(TEGRA_POWERGATE_PCIE);

	err = regulator_bulk_disable(pcie->num_supplies, pcie->supplies);
	if (err < 0)
		dev_warn(dev, "failed to disable regulators: %d\n", err);
}