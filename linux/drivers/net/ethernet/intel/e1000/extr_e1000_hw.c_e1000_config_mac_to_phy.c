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
struct e1000_hw {scalar_t__ mac_type; int phy_type; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int E1000_CTRL_FD ; 
 int E1000_CTRL_FRCDPX ; 
 int E1000_CTRL_FRCSPD ; 
 int E1000_CTRL_ILOS ; 
 int E1000_CTRL_SPD_10 ; 
 int E1000_CTRL_SPD_100 ; 
 int E1000_CTRL_SPD_1000 ; 
 int E1000_CTRL_SPD_SEL ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  M88E1000_PHY_SPEC_STATUS ; 
 int M88E1000_PSSR_1000MBS ; 
 int M88E1000_PSSR_100MBS ; 
 int M88E1000_PSSR_DPLX ; 
 int M88E1000_PSSR_SPEED ; 
 int /*<<< orphan*/  PHY_CTRL ; 
 int RTL_PHY_CTRL_FD ; 
 int RTL_PHY_CTRL_SPD_100 ; 
 scalar_t__ e1000_82544 ; 
 scalar_t__ e1000_ce4100 ; 
 int /*<<< orphan*/  e1000_config_collision_dist (struct e1000_hw*) ; 
#define  e1000_phy_8201 128 
 int /*<<< orphan*/  e1000_read_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 e1000_config_mac_to_phy(struct e1000_hw *hw)
{
	u32 ctrl;
	s32 ret_val;
	u16 phy_data;

	/* 82544 or newer MAC, Auto Speed Detection takes care of
	 * MAC speed/duplex configuration.
	 */
	if ((hw->mac_type >= e1000_82544) && (hw->mac_type != e1000_ce4100))
		return E1000_SUCCESS;

	/* Read the Device Control Register and set the bits to Force Speed
	 * and Duplex.
	 */
	ctrl = er32(CTRL);
	ctrl |= (E1000_CTRL_FRCSPD | E1000_CTRL_FRCDPX);
	ctrl &= ~(E1000_CTRL_SPD_SEL | E1000_CTRL_ILOS);

	switch (hw->phy_type) {
	case e1000_phy_8201:
		ret_val = e1000_read_phy_reg(hw, PHY_CTRL, &phy_data);
		if (ret_val)
			return ret_val;

		if (phy_data & RTL_PHY_CTRL_FD)
			ctrl |= E1000_CTRL_FD;
		else
			ctrl &= ~E1000_CTRL_FD;

		if (phy_data & RTL_PHY_CTRL_SPD_100)
			ctrl |= E1000_CTRL_SPD_100;
		else
			ctrl |= E1000_CTRL_SPD_10;

		e1000_config_collision_dist(hw);
		break;
	default:
		/* Set up duplex in the Device Control and Transmit Control
		 * registers depending on negotiated values.
		 */
		ret_val = e1000_read_phy_reg(hw, M88E1000_PHY_SPEC_STATUS,
					     &phy_data);
		if (ret_val)
			return ret_val;

		if (phy_data & M88E1000_PSSR_DPLX)
			ctrl |= E1000_CTRL_FD;
		else
			ctrl &= ~E1000_CTRL_FD;

		e1000_config_collision_dist(hw);

		/* Set up speed in the Device Control register depending on
		 * negotiated values.
		 */
		if ((phy_data & M88E1000_PSSR_SPEED) == M88E1000_PSSR_1000MBS)
			ctrl |= E1000_CTRL_SPD_1000;
		else if ((phy_data & M88E1000_PSSR_SPEED) ==
			 M88E1000_PSSR_100MBS)
			ctrl |= E1000_CTRL_SPD_100;
	}

	/* Write the configured values back to the Device Control Reg. */
	ew32(CTRL, ctrl);
	return E1000_SUCCESS;
}