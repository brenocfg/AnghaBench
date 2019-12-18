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
struct armada8k_pcie {int /*<<< orphan*/ * phy; int /*<<< orphan*/  phy_count; } ;

/* Variables and functions */
 int ARMADA8K_PCIE_MAX_LANES ; 
 int /*<<< orphan*/  PHY_MODE_PCIE ; 
 int /*<<< orphan*/  phy_exit (int /*<<< orphan*/ ) ; 
 int phy_init (int /*<<< orphan*/ ) ; 
 int phy_power_on (int /*<<< orphan*/ ) ; 
 int phy_set_mode_ext (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int armada8k_pcie_enable_phys(struct armada8k_pcie *pcie)
{
	int ret;
	int i;

	for (i = 0; i < ARMADA8K_PCIE_MAX_LANES; i++) {
		ret = phy_init(pcie->phy[i]);
		if (ret)
			return ret;

		ret = phy_set_mode_ext(pcie->phy[i], PHY_MODE_PCIE,
				       pcie->phy_count);
		if (ret) {
			phy_exit(pcie->phy[i]);
			return ret;
		}

		ret = phy_power_on(pcie->phy[i]);
		if (ret) {
			phy_exit(pcie->phy[i]);
			return ret;
		}
	}

	return 0;
}