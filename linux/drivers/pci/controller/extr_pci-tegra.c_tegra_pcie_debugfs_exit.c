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
struct tegra_pcie {int /*<<< orphan*/ * debugfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tegra_pcie_debugfs_exit(struct tegra_pcie *pcie)
{
	debugfs_remove_recursive(pcie->debugfs);
	pcie->debugfs = NULL;
}