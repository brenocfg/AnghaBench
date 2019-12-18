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
typedef  int u16 ;
struct e1000_hw {scalar_t__ phy_type; int get_link_status; scalar_t__ wait_autoneg_complete; int /*<<< orphan*/  autoneg_advertised; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_ADVERTISE_10_100_ALL ; 
 int /*<<< orphan*/  AUTONEG_ADVERTISE_SPEED_DEFAULT ; 
 scalar_t__ E1000_SUCCESS ; 
 int MII_CR_AUTO_NEG_EN ; 
 int MII_CR_RESTART_AUTO_NEG ; 
 int /*<<< orphan*/  PHY_CTRL ; 
 scalar_t__ e1000_phy_8201 ; 
 scalar_t__ e1000_phy_setup_autoneg (struct e1000_hw*) ; 
 scalar_t__ e1000_read_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ e1000_wait_autoneg (struct e1000_hw*) ; 
 scalar_t__ e1000_write_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 

__attribute__((used)) static s32 e1000_copper_link_autoneg(struct e1000_hw *hw)
{
	s32 ret_val;
	u16 phy_data;

	/* Perform some bounds checking on the hw->autoneg_advertised
	 * parameter.  If this variable is zero, then set it to the default.
	 */
	hw->autoneg_advertised &= AUTONEG_ADVERTISE_SPEED_DEFAULT;

	/* If autoneg_advertised is zero, we assume it was not defaulted
	 * by the calling code so we set to advertise full capability.
	 */
	if (hw->autoneg_advertised == 0)
		hw->autoneg_advertised = AUTONEG_ADVERTISE_SPEED_DEFAULT;

	/* IFE/RTL8201N PHY only supports 10/100 */
	if (hw->phy_type == e1000_phy_8201)
		hw->autoneg_advertised &= AUTONEG_ADVERTISE_10_100_ALL;

	e_dbg("Reconfiguring auto-neg advertisement params\n");
	ret_val = e1000_phy_setup_autoneg(hw);
	if (ret_val) {
		e_dbg("Error Setting up Auto-Negotiation\n");
		return ret_val;
	}
	e_dbg("Restarting Auto-Neg\n");

	/* Restart auto-negotiation by setting the Auto Neg Enable bit and
	 * the Auto Neg Restart bit in the PHY control register.
	 */
	ret_val = e1000_read_phy_reg(hw, PHY_CTRL, &phy_data);
	if (ret_val)
		return ret_val;

	phy_data |= (MII_CR_AUTO_NEG_EN | MII_CR_RESTART_AUTO_NEG);
	ret_val = e1000_write_phy_reg(hw, PHY_CTRL, phy_data);
	if (ret_val)
		return ret_val;

	/* Does the user want to wait for Auto-Neg to complete here, or
	 * check at a later time (for example, callback routine).
	 */
	if (hw->wait_autoneg_complete) {
		ret_val = e1000_wait_autoneg(hw);
		if (ret_val) {
			e_dbg
			    ("Error while waiting for autoneg to complete\n");
			return ret_val;
		}
	}

	hw->get_link_status = true;

	return E1000_SUCCESS;
}