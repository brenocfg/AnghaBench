#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  pp; } ;
struct tegra_pcie_dw {TYPE_1__ pci; } ;

/* Variables and functions */
 int __deinit_controller (struct tegra_pcie_dw*) ; 
 int /*<<< orphan*/  dw_pcie_host_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_pcie_downstream_dev_to_D0 (struct tegra_pcie_dw*) ; 
 int /*<<< orphan*/  tegra_pcie_dw_pme_turnoff (struct tegra_pcie_dw*) ; 

__attribute__((used)) static int tegra_pcie_deinit_controller(struct tegra_pcie_dw *pcie)
{
	tegra_pcie_downstream_dev_to_D0(pcie);
	dw_pcie_host_deinit(&pcie->pci.pp);
	tegra_pcie_dw_pme_turnoff(pcie);

	return __deinit_controller(pcie);
}