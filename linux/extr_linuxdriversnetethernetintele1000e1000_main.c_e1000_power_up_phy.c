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
struct e1000_hw {scalar_t__ media_type; } ;
struct e1000_adapter {struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_CR_POWER_DOWN ; 
 int /*<<< orphan*/  PHY_CTRL ; 
 scalar_t__ e1000_media_type_copper ; 
 int /*<<< orphan*/  e1000_read_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e1000_write_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void e1000_power_up_phy(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	u16 mii_reg = 0;

	/* Just clear the power down bit to wake the phy back up */
	if (hw->media_type == e1000_media_type_copper) {
		/* according to the manual, the phy will retain its
		 * settings across a power-down/up cycle
		 */
		e1000_read_phy_reg(hw, PHY_CTRL, &mii_reg);
		mii_reg &= ~MII_CR_POWER_DOWN;
		e1000_write_phy_reg(hw, PHY_CTRL, mii_reg);
	}
}