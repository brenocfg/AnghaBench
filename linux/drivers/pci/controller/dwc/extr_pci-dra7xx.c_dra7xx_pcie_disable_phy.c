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
 int /*<<< orphan*/  phy_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dra7xx_pcie_disable_phy(struct dra7xx_pcie *dra7xx)
{
	int phy_count = dra7xx->phy_count;

	while (phy_count--) {
		phy_power_off(dra7xx->phy[phy_count]);
		phy_exit(dra7xx->phy[phy_count]);
	}
}