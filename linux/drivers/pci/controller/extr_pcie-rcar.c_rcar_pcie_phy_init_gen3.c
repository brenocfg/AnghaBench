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
struct rcar_pcie {int /*<<< orphan*/  phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  phy_exit (int /*<<< orphan*/ ) ; 
 int phy_init (int /*<<< orphan*/ ) ; 
 int phy_power_on (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rcar_pcie_phy_init_gen3(struct rcar_pcie *pcie)
{
	int err;

	err = phy_init(pcie->phy);
	if (err)
		return err;

	err = phy_power_on(pcie->phy);
	if (err)
		phy_exit(pcie->phy);

	return err;
}