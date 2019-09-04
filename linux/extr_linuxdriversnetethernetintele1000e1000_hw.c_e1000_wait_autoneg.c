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
typedef  scalar_t__ u16 ;
struct e1000_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ E1000_SUCCESS ; 
 scalar_t__ MII_SR_AUTONEG_COMPLETE ; 
 scalar_t__ PHY_AUTO_NEG_TIME ; 
 int /*<<< orphan*/  PHY_STATUS ; 
 scalar_t__ e1000_read_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static s32 e1000_wait_autoneg(struct e1000_hw *hw)
{
	s32 ret_val;
	u16 i;
	u16 phy_data;

	e_dbg("Waiting for Auto-Neg to complete.\n");

	/* We will wait for autoneg to complete or 4.5 seconds to expire. */
	for (i = PHY_AUTO_NEG_TIME; i > 0; i--) {
		/* Read the MII Status Register and wait for Auto-Neg
		 * Complete bit to be set.
		 */
		ret_val = e1000_read_phy_reg(hw, PHY_STATUS, &phy_data);
		if (ret_val)
			return ret_val;
		ret_val = e1000_read_phy_reg(hw, PHY_STATUS, &phy_data);
		if (ret_val)
			return ret_val;
		if (phy_data & MII_SR_AUTONEG_COMPLETE)
			return E1000_SUCCESS;

		msleep(100);
	}
	return E1000_SUCCESS;
}