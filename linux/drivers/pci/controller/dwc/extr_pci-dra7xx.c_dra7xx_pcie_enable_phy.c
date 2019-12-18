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
struct dra7xx_pcie {int phy_count; int /*<<< orphan*/ * phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_MODE_PCIE ; 
 int /*<<< orphan*/  phy_exit (int /*<<< orphan*/ ) ; 
 int phy_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 
 int phy_power_on (int /*<<< orphan*/ ) ; 
 int phy_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dra7xx_pcie_enable_phy(struct dra7xx_pcie *dra7xx)
{
	int phy_count = dra7xx->phy_count;
	int ret;
	int i;

	for (i = 0; i < phy_count; i++) {
		ret = phy_set_mode(dra7xx->phy[i], PHY_MODE_PCIE);
		if (ret < 0)
			goto err_phy;

		ret = phy_init(dra7xx->phy[i]);
		if (ret < 0)
			goto err_phy;

		ret = phy_power_on(dra7xx->phy[i]);
		if (ret < 0) {
			phy_exit(dra7xx->phy[i]);
			goto err_phy;
		}
	}

	return 0;

err_phy:
	while (--i >= 0) {
		phy_power_off(dra7xx->phy[i]);
		phy_exit(dra7xx->phy[i]);
	}

	return ret;
}