#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  msi_irq; int /*<<< orphan*/  irq; } ;
struct TYPE_4__ {TYPE_1__ pp; } ;
struct tegra_pcie_dw {TYPE_2__ pci; int /*<<< orphan*/  debugfs; int /*<<< orphan*/  link_state; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PCI_MSI ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __deinit_controller (struct tegra_pcie_dw*) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 struct tegra_pcie_dw* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  tegra_pcie_downstream_dev_to_D0 (struct tegra_pcie_dw*) ; 
 int /*<<< orphan*/  tegra_pcie_dw_pme_turnoff (struct tegra_pcie_dw*) ; 

__attribute__((used)) static void tegra_pcie_dw_shutdown(struct platform_device *pdev)
{
	struct tegra_pcie_dw *pcie = platform_get_drvdata(pdev);

	if (!pcie->link_state)
		return;

	debugfs_remove_recursive(pcie->debugfs);
	tegra_pcie_downstream_dev_to_D0(pcie);

	disable_irq(pcie->pci.pp.irq);
	if (IS_ENABLED(CONFIG_PCI_MSI))
		disable_irq(pcie->pci.pp.msi_irq);

	tegra_pcie_dw_pme_turnoff(pcie);
	__deinit_controller(pcie);
}