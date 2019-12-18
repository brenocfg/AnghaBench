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
struct cdns_pcie {int phy_count; int /*<<< orphan*/ * phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  phy_exit (int /*<<< orphan*/ ) ; 
 int phy_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 
 int phy_power_on (int /*<<< orphan*/ ) ; 

int cdns_pcie_enable_phy(struct cdns_pcie *pcie)
{
	int ret;
	int i;

	for (i = 0; i < pcie->phy_count; i++) {
		ret = phy_init(pcie->phy[i]);
		if (ret < 0)
			goto err_phy;

		ret = phy_power_on(pcie->phy[i]);
		if (ret < 0) {
			phy_exit(pcie->phy[i]);
			goto err_phy;
		}
	}

	return 0;

err_phy:
	while (--i >= 0) {
		phy_power_off(pcie->phy[i]);
		phy_exit(pcie->phy[i]);
	}

	return ret;
}