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
struct tegra_pcie_dw {int /*<<< orphan*/  cid; int /*<<< orphan*/  dev; int /*<<< orphan*/  pex_ctl_supply; int /*<<< orphan*/  core_clk; int /*<<< orphan*/  core_apb_rst; int /*<<< orphan*/  core_rst; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 
 int reset_control_assert (int /*<<< orphan*/ ) ; 
 int tegra_pcie_bpmp_set_ctrl_state (struct tegra_pcie_dw*,int) ; 
 int /*<<< orphan*/  tegra_pcie_disable_phy (struct tegra_pcie_dw*) ; 
 int /*<<< orphan*/  tegra_pcie_disable_slot_regulators (struct tegra_pcie_dw*) ; 

__attribute__((used)) static int __deinit_controller(struct tegra_pcie_dw *pcie)
{
	int ret;

	ret = reset_control_assert(pcie->core_rst);
	if (ret) {
		dev_err(pcie->dev, "Failed to assert \"core\" reset: %d\n",
			ret);
		return ret;
	}

	tegra_pcie_disable_phy(pcie);

	ret = reset_control_assert(pcie->core_apb_rst);
	if (ret) {
		dev_err(pcie->dev, "Failed to assert APB reset: %d\n", ret);
		return ret;
	}

	clk_disable_unprepare(pcie->core_clk);

	ret = regulator_disable(pcie->pex_ctl_supply);
	if (ret) {
		dev_err(pcie->dev, "Failed to disable regulator: %d\n", ret);
		return ret;
	}

	tegra_pcie_disable_slot_regulators(pcie);

	ret = tegra_pcie_bpmp_set_ctrl_state(pcie, false);
	if (ret) {
		dev_err(pcie->dev, "Failed to disable controller %d: %d\n",
			pcie->cid, ret);
		return ret;
	}

	return ret;
}