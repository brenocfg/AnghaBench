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
struct tegra_pcie_dw {int /*<<< orphan*/  bpmp; int /*<<< orphan*/  dev; int /*<<< orphan*/  debugfs; int /*<<< orphan*/  link_state; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 struct tegra_pcie_dw* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_bpmp_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_pcie_deinit_controller (struct tegra_pcie_dw*) ; 

__attribute__((used)) static int tegra_pcie_dw_remove(struct platform_device *pdev)
{
	struct tegra_pcie_dw *pcie = platform_get_drvdata(pdev);

	if (!pcie->link_state)
		return 0;

	debugfs_remove_recursive(pcie->debugfs);
	tegra_pcie_deinit_controller(pcie);
	pm_runtime_put_sync(pcie->dev);
	pm_runtime_disable(pcie->dev);
	tegra_bpmp_put(pcie->bpmp);

	return 0;
}