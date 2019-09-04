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
typedef  int /*<<< orphan*/  u16 ;
struct pch_gbe_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_CR_POWER_DOWN ; 
 int /*<<< orphan*/  PHY_CONTROL ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  pch_gbe_phy_read_reg_miic (struct pch_gbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pch_gbe_phy_write_reg_miic (struct pch_gbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pch_gbe_phy_power_down(struct pch_gbe_hw *hw)
{
	u16 mii_reg;

	mii_reg = 0;
	/* Power down the PHY so no link is implied when interface is down *
	 * The PHY cannot be powered down if any of the following is TRUE *
	 * (a) WoL is enabled
	 * (b) AMT is active
	 */
	pch_gbe_phy_read_reg_miic(hw, PHY_CONTROL, &mii_reg);
	mii_reg |= MII_CR_POWER_DOWN;
	pch_gbe_phy_write_reg_miic(hw, PHY_CONTROL, mii_reg);
	mdelay(1);
}