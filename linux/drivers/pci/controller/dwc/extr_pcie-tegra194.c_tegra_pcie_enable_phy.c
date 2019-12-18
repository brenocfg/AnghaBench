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
 int phy_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 
 int phy_power_on (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_pcie_enable_phy(struct tegra_pcie_dw *pcie)
{
	unsigned int i;
	int ret;

	for (i = 0; i < pcie->phy_count; i++) {
		ret = phy_init(pcie->phys[i]);
		if (ret < 0)
			goto phy_power_off;

		ret = phy_power_on(pcie->phys[i]);
		if (ret < 0)
			goto phy_exit;
	}

	return 0;

phy_power_off:
	while (i--) {
		phy_power_off(pcie->phys[i]);
phy_exit:
		phy_exit(pcie->phys[i]);
	}

	return ret;
}