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
struct tegra_pcie {int /*<<< orphan*/  supplies; int /*<<< orphan*/  num_supplies; int /*<<< orphan*/  afi_clk; int /*<<< orphan*/  cml_clk; int /*<<< orphan*/  afi_rst; int /*<<< orphan*/  pll_e; int /*<<< orphan*/  pex_rst; int /*<<< orphan*/  pcie_xrst; struct tegra_pcie_soc* soc; struct device* dev; } ;
struct device {int /*<<< orphan*/  pm_domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEGRA_POWERGATE_PCIE ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_powergate_power_off (int /*<<< orphan*/ ) ; 
 int tegra_powergate_power_on (int /*<<< orphan*/ ) ; 
 int tegra_powergate_remove_clamping (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_pcie_power_on(struct tegra_pcie *pcie)
{
	struct device *dev = pcie->dev;
	const struct tegra_pcie_soc *soc = pcie->soc;
	int err;

	reset_control_assert(pcie->pcie_xrst);
	reset_control_assert(pcie->afi_rst);
	reset_control_assert(pcie->pex_rst);

	if (!dev->pm_domain)
		tegra_powergate_power_off(TEGRA_POWERGATE_PCIE);

	/* enable regulators */
	err = regulator_bulk_enable(pcie->num_supplies, pcie->supplies);
	if (err < 0)
		dev_err(dev, "failed to enable regulators: %d\n", err);

	if (!dev->pm_domain) {
		err = tegra_powergate_power_on(TEGRA_POWERGATE_PCIE);
		if (err) {
			dev_err(dev, "failed to power ungate: %d\n", err);
			goto regulator_disable;
		}
		err = tegra_powergate_remove_clamping(TEGRA_POWERGATE_PCIE);
		if (err) {
			dev_err(dev, "failed to remove clamp: %d\n", err);
			goto powergate;
		}
	}

	err = clk_prepare_enable(pcie->afi_clk);
	if (err < 0) {
		dev_err(dev, "failed to enable AFI clock: %d\n", err);
		goto powergate;
	}

	if (soc->has_cml_clk) {
		err = clk_prepare_enable(pcie->cml_clk);
		if (err < 0) {
			dev_err(dev, "failed to enable CML clock: %d\n", err);
			goto disable_afi_clk;
		}
	}

	err = clk_prepare_enable(pcie->pll_e);
	if (err < 0) {
		dev_err(dev, "failed to enable PLLE clock: %d\n", err);
		goto disable_cml_clk;
	}

	reset_control_deassert(pcie->afi_rst);

	return 0;

disable_cml_clk:
	if (soc->has_cml_clk)
		clk_disable_unprepare(pcie->cml_clk);
disable_afi_clk:
	clk_disable_unprepare(pcie->afi_clk);
powergate:
	if (!dev->pm_domain)
		tegra_powergate_power_off(TEGRA_POWERGATE_PCIE);
regulator_disable:
	regulator_bulk_disable(pcie->num_supplies, pcie->supplies);

	return err;
}