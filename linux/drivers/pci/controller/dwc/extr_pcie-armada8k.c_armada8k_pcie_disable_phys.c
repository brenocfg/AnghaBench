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
struct armada8k_pcie {int /*<<< orphan*/ * phy; } ;

/* Variables and functions */
 int ARMADA8K_PCIE_MAX_LANES ; 
 int /*<<< orphan*/  phy_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void armada8k_pcie_disable_phys(struct armada8k_pcie *pcie)
{
	int i;

	for (i = 0; i < ARMADA8K_PCIE_MAX_LANES; i++) {
		phy_power_off(pcie->phy[i]);
		phy_exit(pcie->phy[i]);
	}
}