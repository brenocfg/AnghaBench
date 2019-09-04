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
typedef  scalar_t__ u16 ;
struct e1000_hw {scalar_t__ forced_speed_duplex; scalar_t__ phy_type; scalar_t__ mac_type; int /*<<< orphan*/  autoneg; scalar_t__ wait_autoneg_complete; int /*<<< orphan*/  fc; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int DEVICE_SPEED_MASK ; 
 int E1000_CTRL_ASDE ; 
 int E1000_CTRL_FD ; 
 int E1000_CTRL_FRCDPX ; 
 int E1000_CTRL_FRCSPD ; 
 int E1000_CTRL_SPD_100 ; 
 int E1000_CTRL_SPD_1000 ; 
 int /*<<< orphan*/  E1000_FC_NONE ; 
 scalar_t__ E1000_SUCCESS ; 
 int /*<<< orphan*/  IGP01E1000_PHY_PORT_CTRL ; 
 scalar_t__ IGP01E1000_PSCR_AUTO_MDIX ; 
 scalar_t__ IGP01E1000_PSCR_FORCE_MDI_MDIX ; 
 scalar_t__ M88E1000_EPSCR_TX_CLK_25 ; 
 int /*<<< orphan*/  M88E1000_EXT_PHY_SPEC_CTRL ; 
 int /*<<< orphan*/  M88E1000_PHY_SPEC_CTRL ; 
 scalar_t__ M88E1000_PSCR_ASSERT_CRS_ON_TX ; 
 scalar_t__ M88E1000_PSCR_AUTO_X_MODE ; 
 scalar_t__ MII_CR_AUTO_NEG_EN ; 
 scalar_t__ MII_CR_FULL_DUPLEX ; 
 scalar_t__ MII_CR_RESET ; 
 scalar_t__ MII_CR_SPEED_10 ; 
 scalar_t__ MII_CR_SPEED_100 ; 
 scalar_t__ MII_CR_SPEED_1000 ; 
 scalar_t__ MII_SR_LINK_STATUS ; 
 int /*<<< orphan*/  PHY_CTRL ; 
 scalar_t__ PHY_FORCE_TIME ; 
 int /*<<< orphan*/  PHY_STATUS ; 
 scalar_t__ e1000_100_full ; 
 scalar_t__ e1000_100_half ; 
 scalar_t__ e1000_10_full ; 
 scalar_t__ e1000_10_half ; 
 scalar_t__ e1000_82543 ; 
 scalar_t__ e1000_82544 ; 
 int /*<<< orphan*/  e1000_config_collision_dist (struct e1000_hw*) ; 
 scalar_t__ e1000_phy_m88 ; 
 scalar_t__ e1000_phy_reset_dsp (struct e1000_hw*) ; 
 scalar_t__ e1000_polarity_reversal_workaround (struct e1000_hw*) ; 
 scalar_t__ e1000_read_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ e1000_write_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  e_dbg (char*,...) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static s32 e1000_phy_force_speed_duplex(struct e1000_hw *hw)
{
	u32 ctrl;
	s32 ret_val;
	u16 mii_ctrl_reg;
	u16 mii_status_reg;
	u16 phy_data;
	u16 i;

	/* Turn off Flow control if we are forcing speed and duplex. */
	hw->fc = E1000_FC_NONE;

	e_dbg("hw->fc = %d\n", hw->fc);

	/* Read the Device Control Register. */
	ctrl = er32(CTRL);

	/* Set the bits to Force Speed and Duplex in the Device Ctrl Reg. */
	ctrl |= (E1000_CTRL_FRCSPD | E1000_CTRL_FRCDPX);
	ctrl &= ~(DEVICE_SPEED_MASK);

	/* Clear the Auto Speed Detect Enable bit. */
	ctrl &= ~E1000_CTRL_ASDE;

	/* Read the MII Control Register. */
	ret_val = e1000_read_phy_reg(hw, PHY_CTRL, &mii_ctrl_reg);
	if (ret_val)
		return ret_val;

	/* We need to disable autoneg in order to force link and duplex. */

	mii_ctrl_reg &= ~MII_CR_AUTO_NEG_EN;

	/* Are we forcing Full or Half Duplex? */
	if (hw->forced_speed_duplex == e1000_100_full ||
	    hw->forced_speed_duplex == e1000_10_full) {
		/* We want to force full duplex so we SET the full duplex bits
		 * in the Device and MII Control Registers.
		 */
		ctrl |= E1000_CTRL_FD;
		mii_ctrl_reg |= MII_CR_FULL_DUPLEX;
		e_dbg("Full Duplex\n");
	} else {
		/* We want to force half duplex so we CLEAR the full duplex bits
		 * in the Device and MII Control Registers.
		 */
		ctrl &= ~E1000_CTRL_FD;
		mii_ctrl_reg &= ~MII_CR_FULL_DUPLEX;
		e_dbg("Half Duplex\n");
	}

	/* Are we forcing 100Mbps??? */
	if (hw->forced_speed_duplex == e1000_100_full ||
	    hw->forced_speed_duplex == e1000_100_half) {
		/* Set the 100Mb bit and turn off the 1000Mb and 10Mb bits. */
		ctrl |= E1000_CTRL_SPD_100;
		mii_ctrl_reg |= MII_CR_SPEED_100;
		mii_ctrl_reg &= ~(MII_CR_SPEED_1000 | MII_CR_SPEED_10);
		e_dbg("Forcing 100mb ");
	} else {
		/* Set the 10Mb bit and turn off the 1000Mb and 100Mb bits. */
		ctrl &= ~(E1000_CTRL_SPD_1000 | E1000_CTRL_SPD_100);
		mii_ctrl_reg |= MII_CR_SPEED_10;
		mii_ctrl_reg &= ~(MII_CR_SPEED_1000 | MII_CR_SPEED_100);
		e_dbg("Forcing 10mb ");
	}

	e1000_config_collision_dist(hw);

	/* Write the configured values back to the Device Control Reg. */
	ew32(CTRL, ctrl);

	if (hw->phy_type == e1000_phy_m88) {
		ret_val =
		    e1000_read_phy_reg(hw, M88E1000_PHY_SPEC_CTRL, &phy_data);
		if (ret_val)
			return ret_val;

		/* Clear Auto-Crossover to force MDI manually. M88E1000 requires
		 * MDI forced whenever speed are duplex are forced.
		 */
		phy_data &= ~M88E1000_PSCR_AUTO_X_MODE;
		ret_val =
		    e1000_write_phy_reg(hw, M88E1000_PHY_SPEC_CTRL, phy_data);
		if (ret_val)
			return ret_val;

		e_dbg("M88E1000 PSCR: %x\n", phy_data);

		/* Need to reset the PHY or these changes will be ignored */
		mii_ctrl_reg |= MII_CR_RESET;

		/* Disable MDI-X support for 10/100 */
	} else {
		/* Clear Auto-Crossover to force MDI manually.  IGP requires MDI
		 * forced whenever speed or duplex are forced.
		 */
		ret_val =
		    e1000_read_phy_reg(hw, IGP01E1000_PHY_PORT_CTRL, &phy_data);
		if (ret_val)
			return ret_val;

		phy_data &= ~IGP01E1000_PSCR_AUTO_MDIX;
		phy_data &= ~IGP01E1000_PSCR_FORCE_MDI_MDIX;

		ret_val =
		    e1000_write_phy_reg(hw, IGP01E1000_PHY_PORT_CTRL, phy_data);
		if (ret_val)
			return ret_val;
	}

	/* Write back the modified PHY MII control register. */
	ret_val = e1000_write_phy_reg(hw, PHY_CTRL, mii_ctrl_reg);
	if (ret_val)
		return ret_val;

	udelay(1);

	/* The wait_autoneg_complete flag may be a little misleading here.
	 * Since we are forcing speed and duplex, Auto-Neg is not enabled.
	 * But we do want to delay for a period while forcing only so we
	 * don't generate false No Link messages.  So we will wait here
	 * only if the user has set wait_autoneg_complete to 1, which is
	 * the default.
	 */
	if (hw->wait_autoneg_complete) {
		/* We will wait for autoneg to complete. */
		e_dbg("Waiting for forced speed/duplex link.\n");
		mii_status_reg = 0;

		/* Wait for autoneg to complete or 4.5 seconds to expire */
		for (i = PHY_FORCE_TIME; i > 0; i--) {
			/* Read the MII Status Register and wait for Auto-Neg
			 * Complete bit to be set.
			 */
			ret_val =
			    e1000_read_phy_reg(hw, PHY_STATUS, &mii_status_reg);
			if (ret_val)
				return ret_val;

			ret_val =
			    e1000_read_phy_reg(hw, PHY_STATUS, &mii_status_reg);
			if (ret_val)
				return ret_val;

			if (mii_status_reg & MII_SR_LINK_STATUS)
				break;
			msleep(100);
		}
		if ((i == 0) && (hw->phy_type == e1000_phy_m88)) {
			/* We didn't get link.  Reset the DSP and wait again
			 * for link.
			 */
			ret_val = e1000_phy_reset_dsp(hw);
			if (ret_val) {
				e_dbg("Error Resetting PHY DSP\n");
				return ret_val;
			}
		}
		/* This loop will early-out if the link condition has been
		 * met
		 */
		for (i = PHY_FORCE_TIME; i > 0; i--) {
			if (mii_status_reg & MII_SR_LINK_STATUS)
				break;
			msleep(100);
			/* Read the MII Status Register and wait for Auto-Neg
			 * Complete bit to be set.
			 */
			ret_val =
			    e1000_read_phy_reg(hw, PHY_STATUS, &mii_status_reg);
			if (ret_val)
				return ret_val;

			ret_val =
			    e1000_read_phy_reg(hw, PHY_STATUS, &mii_status_reg);
			if (ret_val)
				return ret_val;
		}
	}

	if (hw->phy_type == e1000_phy_m88) {
		/* Because we reset the PHY above, we need to re-force TX_CLK in
		 * the Extended PHY Specific Control Register to 25MHz clock.
		 * This value defaults back to a 2.5MHz clock when the PHY is
		 * reset.
		 */
		ret_val =
		    e1000_read_phy_reg(hw, M88E1000_EXT_PHY_SPEC_CTRL,
				       &phy_data);
		if (ret_val)
			return ret_val;

		phy_data |= M88E1000_EPSCR_TX_CLK_25;
		ret_val =
		    e1000_write_phy_reg(hw, M88E1000_EXT_PHY_SPEC_CTRL,
					phy_data);
		if (ret_val)
			return ret_val;

		/* In addition, because of the s/w reset above, we need to
		 * enable CRS on Tx.  This must be set for both full and half
		 * duplex operation.
		 */
		ret_val =
		    e1000_read_phy_reg(hw, M88E1000_PHY_SPEC_CTRL, &phy_data);
		if (ret_val)
			return ret_val;

		phy_data |= M88E1000_PSCR_ASSERT_CRS_ON_TX;
		ret_val =
		    e1000_write_phy_reg(hw, M88E1000_PHY_SPEC_CTRL, phy_data);
		if (ret_val)
			return ret_val;

		if ((hw->mac_type == e1000_82544 ||
		     hw->mac_type == e1000_82543) &&
		    (!hw->autoneg) &&
		    (hw->forced_speed_duplex == e1000_10_full ||
		     hw->forced_speed_duplex == e1000_10_half)) {
			ret_val = e1000_polarity_reversal_workaround(hw);
			if (ret_val)
				return ret_val;
		}
	}
	return E1000_SUCCESS;
}