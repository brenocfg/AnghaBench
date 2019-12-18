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
struct tegra_pcie_dw {unsigned int phy_count; int /*<<< orphan*/ * phys; } ;

/* Variables and functions */
 int /*<<< orphan*/  phy_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_pcie_disable_phy(struct tegra_pcie_dw *pcie)
{
	unsigned int phy_count = pcie->phy_count;

	while (phy_count--) {
		phy_power_off(pcie->phys[phy_count]);
		phy_exit(pcie->phys[phy_count]);
	}
}