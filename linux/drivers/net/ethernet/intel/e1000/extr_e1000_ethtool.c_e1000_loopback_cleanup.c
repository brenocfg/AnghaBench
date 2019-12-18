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
typedef  int u32 ;
typedef  int u16 ;
struct e1000_hw {int mac_type; int autoneg; } ;
struct e1000_adapter {struct e1000_hw hw; } ;

/* Variables and functions */
 int E1000_RCTL_LBM_MAC ; 
 int E1000_RCTL_LBM_TCVR ; 
 int MII_CR_LOOPBACK ; 
 int /*<<< orphan*/  PHY_CTRL ; 
 int /*<<< orphan*/  RCTL ; 
#define  e1000_82545 131 
#define  e1000_82545_rev_3 130 
#define  e1000_82546 129 
#define  e1000_82546_rev_3 128 
 int /*<<< orphan*/  e1000_phy_reset (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_read_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  e1000_write_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void e1000_loopback_cleanup(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	u32 rctl;
	u16 phy_reg;

	rctl = er32(RCTL);
	rctl &= ~(E1000_RCTL_LBM_TCVR | E1000_RCTL_LBM_MAC);
	ew32(RCTL, rctl);

	switch (hw->mac_type) {
	case e1000_82545:
	case e1000_82546:
	case e1000_82545_rev_3:
	case e1000_82546_rev_3:
	default:
		hw->autoneg = true;
		e1000_read_phy_reg(hw, PHY_CTRL, &phy_reg);
		if (phy_reg & MII_CR_LOOPBACK) {
			phy_reg &= ~MII_CR_LOOPBACK;
			e1000_write_phy_reg(hw, PHY_CTRL, phy_reg);
			e1000_phy_reset(hw);
		}
		break;
	}
}