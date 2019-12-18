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
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ (* write_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int) ;scalar_t__ (* read_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int*) ;} ;
struct e1000_phy_info {scalar_t__ type; int id; TYPE_1__ ops; scalar_t__ autoneg_wait_to_complete; } ;
struct e1000_hw {struct e1000_phy_info phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
#define  I210_I_PHY_ID 132 
#define  I347AT4_E_PHY_ID 131 
 int M88E1000_EPSCR_TX_CLK_25 ; 
 int /*<<< orphan*/  M88E1000_EXT_PHY_SPEC_CTRL ; 
 int /*<<< orphan*/  M88E1000_PHY_PAGE_SELECT ; 
 int /*<<< orphan*/  M88E1000_PHY_SPEC_CTRL ; 
 int M88E1000_PSCR_ASSERT_CRS_ON_TX ; 
 int M88E1000_PSCR_AUTO_X_MODE ; 
#define  M88E1112_E_PHY_ID 130 
#define  M88E1512_E_PHY_ID 129 
#define  M88E1543_E_PHY_ID 128 
 int /*<<< orphan*/  PHY_CONTROL ; 
 int /*<<< orphan*/  PHY_FORCE_LIMIT ; 
 scalar_t__ e1000_phy_i210 ; 
 scalar_t__ e1000_phy_m88 ; 
 int /*<<< orphan*/  hw_dbg (char*,...) ; 
 int /*<<< orphan*/  igb_phy_force_speed_duplex_setup (struct e1000_hw*,int*) ; 
 scalar_t__ igb_phy_has_link (struct e1000_hw*,int /*<<< orphan*/ ,int,int*) ; 
 scalar_t__ igb_phy_reset_dsp (struct e1000_hw*) ; 
 scalar_t__ igb_phy_sw_reset (struct e1000_hw*) ; 
 scalar_t__ stub1 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub2 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub3 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub4 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub5 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub6 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub7 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub8 (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub9 (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 

s32 igb_phy_force_speed_duplex_m88(struct e1000_hw *hw)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val;
	u16 phy_data;
	bool link;

	/* I210 and I211 devices support Auto-Crossover in forced operation. */
	if (phy->type != e1000_phy_i210) {
		/* Clear Auto-Crossover to force MDI manually.  M88E1000
		 * requires MDI forced whenever speed and duplex are forced.
		 */
		ret_val = phy->ops.read_reg(hw, M88E1000_PHY_SPEC_CTRL,
					    &phy_data);
		if (ret_val)
			goto out;

		phy_data &= ~M88E1000_PSCR_AUTO_X_MODE;
		ret_val = phy->ops.write_reg(hw, M88E1000_PHY_SPEC_CTRL,
					     phy_data);
		if (ret_val)
			goto out;

		hw_dbg("M88E1000 PSCR: %X\n", phy_data);
	}

	ret_val = phy->ops.read_reg(hw, PHY_CONTROL, &phy_data);
	if (ret_val)
		goto out;

	igb_phy_force_speed_duplex_setup(hw, &phy_data);

	ret_val = phy->ops.write_reg(hw, PHY_CONTROL, phy_data);
	if (ret_val)
		goto out;

	/* Reset the phy to commit changes. */
	ret_val = igb_phy_sw_reset(hw);
	if (ret_val)
		goto out;

	if (phy->autoneg_wait_to_complete) {
		hw_dbg("Waiting for forced speed/duplex link on M88 phy.\n");

		ret_val = igb_phy_has_link(hw, PHY_FORCE_LIMIT, 100000, &link);
		if (ret_val)
			goto out;

		if (!link) {
			bool reset_dsp = true;

			switch (hw->phy.id) {
			case I347AT4_E_PHY_ID:
			case M88E1112_E_PHY_ID:
			case M88E1543_E_PHY_ID:
			case M88E1512_E_PHY_ID:
			case I210_I_PHY_ID:
				reset_dsp = false;
				break;
			default:
				if (hw->phy.type != e1000_phy_m88)
					reset_dsp = false;
				break;
			}
			if (!reset_dsp) {
				hw_dbg("Link taking longer than expected.\n");
			} else {
				/* We didn't get link.
				 * Reset the DSP and cross our fingers.
				 */
				ret_val = phy->ops.write_reg(hw,
						M88E1000_PHY_PAGE_SELECT,
						0x001d);
				if (ret_val)
					goto out;
				ret_val = igb_phy_reset_dsp(hw);
				if (ret_val)
					goto out;
			}
		}

		/* Try once more */
		ret_val = igb_phy_has_link(hw, PHY_FORCE_LIMIT,
					   100000, &link);
		if (ret_val)
			goto out;
	}

	if (hw->phy.type != e1000_phy_m88 ||
	    hw->phy.id == I347AT4_E_PHY_ID ||
	    hw->phy.id == M88E1112_E_PHY_ID ||
	    hw->phy.id == M88E1543_E_PHY_ID ||
	    hw->phy.id == M88E1512_E_PHY_ID ||
	    hw->phy.id == I210_I_PHY_ID)
		goto out;

	ret_val = phy->ops.read_reg(hw, M88E1000_EXT_PHY_SPEC_CTRL, &phy_data);
	if (ret_val)
		goto out;

	/* Resetting the phy means we need to re-force TX_CLK in the
	 * Extended PHY Specific Control Register to 25MHz clock from
	 * the reset value of 2.5MHz.
	 */
	phy_data |= M88E1000_EPSCR_TX_CLK_25;
	ret_val = phy->ops.write_reg(hw, M88E1000_EXT_PHY_SPEC_CTRL, phy_data);
	if (ret_val)
		goto out;

	/* In addition, we must re-enable CRS on Tx for both half and full
	 * duplex.
	 */
	ret_val = phy->ops.read_reg(hw, M88E1000_PHY_SPEC_CTRL, &phy_data);
	if (ret_val)
		goto out;

	phy_data |= M88E1000_PSCR_ASSERT_CRS_ON_TX;
	ret_val = phy->ops.write_reg(hw, M88E1000_PHY_SPEC_CTRL, phy_data);

out:
	return ret_val;
}