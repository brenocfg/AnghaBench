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
struct tegra_pcie_dw {int /*<<< orphan*/  pci; int /*<<< orphan*/  msi_ctrl_int; int /*<<< orphan*/  link_state; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_LOGIC_MSI_CTRL_INT_0_EN ; 
 int __deinit_controller (struct tegra_pcie_dw*) ; 
 struct tegra_pcie_dw* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dw_pcie_readl_dbi (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_pcie_downstream_dev_to_D0 (struct tegra_pcie_dw*) ; 
 int /*<<< orphan*/  tegra_pcie_dw_pme_turnoff (struct tegra_pcie_dw*) ; 

__attribute__((used)) static int tegra_pcie_dw_suspend_noirq(struct device *dev)
{
	struct tegra_pcie_dw *pcie = dev_get_drvdata(dev);

	if (!pcie->link_state)
		return 0;

	/* Save MSI interrupt vector */
	pcie->msi_ctrl_int = dw_pcie_readl_dbi(&pcie->pci,
					       PORT_LOGIC_MSI_CTRL_INT_0_EN);
	tegra_pcie_downstream_dev_to_D0(pcie);
	tegra_pcie_dw_pme_turnoff(pcie);

	return __deinit_controller(pcie);
}