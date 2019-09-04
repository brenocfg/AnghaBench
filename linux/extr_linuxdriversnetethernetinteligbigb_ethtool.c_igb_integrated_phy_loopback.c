#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ type; scalar_t__ id; } ;
struct TYPE_3__ {int autoneg; } ;
struct e1000_hw {TYPE_2__ phy; TYPE_1__ mac; } ;
struct igb_adapter {struct e1000_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_CTRL ; 
 int E1000_CTRL_FD ; 
 int E1000_CTRL_FRCDPX ; 
 int E1000_CTRL_FRCSPD ; 
 int E1000_CTRL_ILOS ; 
 int E1000_CTRL_SLU ; 
 int E1000_CTRL_SPD_1000 ; 
 int E1000_CTRL_SPD_SEL ; 
 scalar_t__ I210_I_PHY_ID ; 
 int /*<<< orphan*/  I347AT4_PAGE_SELECT ; 
 int /*<<< orphan*/  I82580_PHY_LBK_CTRL ; 
 int /*<<< orphan*/  M88E1000_PHY_SPEC_CTRL ; 
 int /*<<< orphan*/  PHY_CONTROL ; 
 scalar_t__ e1000_phy_82580 ; 
 scalar_t__ e1000_phy_m88 ; 
 int /*<<< orphan*/  igb_phy_disable_receiver (struct igb_adapter*) ; 
 int /*<<< orphan*/  igb_write_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int igb_integrated_phy_loopback(struct igb_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 ctrl_reg = 0;

	hw->mac.autoneg = false;

	if (hw->phy.type == e1000_phy_m88) {
		if (hw->phy.id != I210_I_PHY_ID) {
			/* Auto-MDI/MDIX Off */
			igb_write_phy_reg(hw, M88E1000_PHY_SPEC_CTRL, 0x0808);
			/* reset to update Auto-MDI/MDIX */
			igb_write_phy_reg(hw, PHY_CONTROL, 0x9140);
			/* autoneg off */
			igb_write_phy_reg(hw, PHY_CONTROL, 0x8140);
		} else {
			/* force 1000, set loopback  */
			igb_write_phy_reg(hw, I347AT4_PAGE_SELECT, 0);
			igb_write_phy_reg(hw, PHY_CONTROL, 0x4140);
		}
	} else if (hw->phy.type == e1000_phy_82580) {
		/* enable MII loopback */
		igb_write_phy_reg(hw, I82580_PHY_LBK_CTRL, 0x8041);
	}

	/* add small delay to avoid loopback test failure */
	msleep(50);

	/* force 1000, set loopback */
	igb_write_phy_reg(hw, PHY_CONTROL, 0x4140);

	/* Now set up the MAC to the same speed/duplex as the PHY. */
	ctrl_reg = rd32(E1000_CTRL);
	ctrl_reg &= ~E1000_CTRL_SPD_SEL; /* Clear the speed sel bits */
	ctrl_reg |= (E1000_CTRL_FRCSPD | /* Set the Force Speed Bit */
		     E1000_CTRL_FRCDPX | /* Set the Force Duplex Bit */
		     E1000_CTRL_SPD_1000 |/* Force Speed to 1000 */
		     E1000_CTRL_FD |	 /* Force Duplex to FULL */
		     E1000_CTRL_SLU);	 /* Set link up enable bit */

	if (hw->phy.type == e1000_phy_m88)
		ctrl_reg |= E1000_CTRL_ILOS; /* Invert Loss of Signal */

	wr32(E1000_CTRL, ctrl_reg);

	/* Disable the receiver on the PHY so when a cable is plugged in, the
	 * PHY does not begin to autoneg when a cable is reconnected to the NIC.
	 */
	if (hw->phy.type == e1000_phy_m88)
		igb_phy_disable_receiver(adapter);

	msleep(500);
	return 0;
}