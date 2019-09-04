#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {scalar_t__ (* write_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ (* read_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct e1000_phy_info {scalar_t__ autoneg_wait_to_complete; TYPE_1__ ops; } ;
struct e1000_hw {struct e1000_phy_info phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IGP01E1000_PHY_PORT_CTRL ; 
 int /*<<< orphan*/  IGP01E1000_PSCR_AUTO_MDIX ; 
 int /*<<< orphan*/  IGP01E1000_PSCR_FORCE_MDI_MDIX ; 
 int /*<<< orphan*/  PHY_CONTROL ; 
 int /*<<< orphan*/  PHY_FORCE_LIMIT ; 
 int /*<<< orphan*/  hw_dbg (char*,...) ; 
 int /*<<< orphan*/  igb_phy_force_speed_duplex_setup (struct e1000_hw*,int /*<<< orphan*/ *) ; 
 scalar_t__ igb_phy_has_link (struct e1000_hw*,int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ stub1 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub4 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

s32 igb_phy_force_speed_duplex_igp(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data;
	bool link;

	ret_val = phy->ops.read_reg(hw, PHY_CONTROL, &phy_data);
	if (ret_val)
		goto out;

	igb_phy_force_speed_duplex_setup(hw, &phy_data);

	ret_val = phy->ops.write_reg(hw, PHY_CONTROL, phy_data);
	if (ret_val)
		goto out;

	/* Clear Auto-Crossover to force MDI manually.  IGP requires MDI
	 * forced whenever speed and duplex are forced.
	 */
	ret_val = phy->ops.read_reg(hw, IGP01E1000_PHY_PORT_CTRL, &phy_data);
	if (ret_val)
		goto out;

	phy_data &= ~IGP01E1000_PSCR_AUTO_MDIX;
	phy_data &= ~IGP01E1000_PSCR_FORCE_MDI_MDIX;

	ret_val = phy->ops.write_reg(hw, IGP01E1000_PHY_PORT_CTRL, phy_data);
	if (ret_val)
		goto out;

	hw_dbg("IGP PSCR: %X\n", phy_data);

	udelay(1);

	if (phy->autoneg_wait_to_complete) {
		hw_dbg("Waiting for forced speed/duplex link on IGP phy.\n");

		ret_val = igb_phy_has_link(hw, PHY_FORCE_LIMIT, 10000, &link);
		if (ret_val)
			goto out;

		if (!link)
			hw_dbg("Link taking longer than expected.\n");

		/* Try once more */
		ret_val = igb_phy_has_link(hw, PHY_FORCE_LIMIT, 10000, &link);
		if (ret_val)
			goto out;
	}

out:
	return ret_val;
}