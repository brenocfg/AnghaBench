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
struct e1000_hw {scalar_t__ phy_type; int autoneg_advertised; int fc; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int ADVERTISE_1000_FULL ; 
 int ADVERTISE_1000_HALF ; 
 int ADVERTISE_100_FULL ; 
 int ADVERTISE_100_HALF ; 
 int ADVERTISE_10_FULL ; 
 int ADVERTISE_10_HALF ; 
 int CR_1000T_FD_CAPS ; 
 scalar_t__ E1000_ERR_CONFIG ; 
#define  E1000_FC_FULL 131 
#define  E1000_FC_NONE 130 
#define  E1000_FC_RX_PAUSE 129 
#define  E1000_FC_TX_PAUSE 128 
 scalar_t__ E1000_SUCCESS ; 
 int NWAY_AR_100TX_FD_CAPS ; 
 int NWAY_AR_100TX_HD_CAPS ; 
 int NWAY_AR_10T_FD_CAPS ; 
 int NWAY_AR_10T_HD_CAPS ; 
 int NWAY_AR_ASM_DIR ; 
 int NWAY_AR_PAUSE ; 
 int /*<<< orphan*/  PHY_1000T_CTRL ; 
 int /*<<< orphan*/  PHY_AUTONEG_ADV ; 
 int REG4_SPEED_MASK ; 
 int REG9_SPEED_MASK ; 
 scalar_t__ e1000_phy_8201 ; 
 scalar_t__ e1000_read_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ e1000_write_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  e_dbg (char*,...) ; 

s32 e1000_phy_setup_autoneg(struct e1000_hw *hw)
{
	s32 ret_val;
	u16 mii_autoneg_adv_reg;
	u16 mii_1000t_ctrl_reg;

	/* Read the MII Auto-Neg Advertisement Register (Address 4). */
	ret_val = e1000_read_phy_reg(hw, PHY_AUTONEG_ADV, &mii_autoneg_adv_reg);
	if (ret_val)
		return ret_val;

	/* Read the MII 1000Base-T Control Register (Address 9). */
	ret_val = e1000_read_phy_reg(hw, PHY_1000T_CTRL, &mii_1000t_ctrl_reg);
	if (ret_val)
		return ret_val;
	else if (hw->phy_type == e1000_phy_8201)
		mii_1000t_ctrl_reg &= ~REG9_SPEED_MASK;

	/* Need to parse both autoneg_advertised and fc and set up
	 * the appropriate PHY registers.  First we will parse for
	 * autoneg_advertised software override.  Since we can advertise
	 * a plethora of combinations, we need to check each bit
	 * individually.
	 */

	/* First we clear all the 10/100 mb speed bits in the Auto-Neg
	 * Advertisement Register (Address 4) and the 1000 mb speed bits in
	 * the  1000Base-T Control Register (Address 9).
	 */
	mii_autoneg_adv_reg &= ~REG4_SPEED_MASK;
	mii_1000t_ctrl_reg &= ~REG9_SPEED_MASK;

	e_dbg("autoneg_advertised %x\n", hw->autoneg_advertised);

	/* Do we want to advertise 10 Mb Half Duplex? */
	if (hw->autoneg_advertised & ADVERTISE_10_HALF) {
		e_dbg("Advertise 10mb Half duplex\n");
		mii_autoneg_adv_reg |= NWAY_AR_10T_HD_CAPS;
	}

	/* Do we want to advertise 10 Mb Full Duplex? */
	if (hw->autoneg_advertised & ADVERTISE_10_FULL) {
		e_dbg("Advertise 10mb Full duplex\n");
		mii_autoneg_adv_reg |= NWAY_AR_10T_FD_CAPS;
	}

	/* Do we want to advertise 100 Mb Half Duplex? */
	if (hw->autoneg_advertised & ADVERTISE_100_HALF) {
		e_dbg("Advertise 100mb Half duplex\n");
		mii_autoneg_adv_reg |= NWAY_AR_100TX_HD_CAPS;
	}

	/* Do we want to advertise 100 Mb Full Duplex? */
	if (hw->autoneg_advertised & ADVERTISE_100_FULL) {
		e_dbg("Advertise 100mb Full duplex\n");
		mii_autoneg_adv_reg |= NWAY_AR_100TX_FD_CAPS;
	}

	/* We do not allow the Phy to advertise 1000 Mb Half Duplex */
	if (hw->autoneg_advertised & ADVERTISE_1000_HALF) {
		e_dbg
		    ("Advertise 1000mb Half duplex requested, request denied!\n");
	}

	/* Do we want to advertise 1000 Mb Full Duplex? */
	if (hw->autoneg_advertised & ADVERTISE_1000_FULL) {
		e_dbg("Advertise 1000mb Full duplex\n");
		mii_1000t_ctrl_reg |= CR_1000T_FD_CAPS;
	}

	/* Check for a software override of the flow control settings, and
	 * setup the PHY advertisement registers accordingly.  If
	 * auto-negotiation is enabled, then software will have to set the
	 * "PAUSE" bits to the correct value in the Auto-Negotiation
	 * Advertisement Register (PHY_AUTONEG_ADV) and re-start
	 * auto-negotiation.
	 *
	 * The possible values of the "fc" parameter are:
	 *      0:  Flow control is completely disabled
	 *      1:  Rx flow control is enabled (we can receive pause frames
	 *          but not send pause frames).
	 *      2:  Tx flow control is enabled (we can send pause frames
	 *          but we do not support receiving pause frames).
	 *      3:  Both Rx and TX flow control (symmetric) are enabled.
	 *  other:  No software override.  The flow control configuration
	 *          in the EEPROM is used.
	 */
	switch (hw->fc) {
	case E1000_FC_NONE:	/* 0 */
		/* Flow control (RX & TX) is completely disabled by a
		 * software over-ride.
		 */
		mii_autoneg_adv_reg &= ~(NWAY_AR_ASM_DIR | NWAY_AR_PAUSE);
		break;
	case E1000_FC_RX_PAUSE:	/* 1 */
		/* RX Flow control is enabled, and TX Flow control is
		 * disabled, by a software over-ride.
		 */
		/* Since there really isn't a way to advertise that we are
		 * capable of RX Pause ONLY, we will advertise that we
		 * support both symmetric and asymmetric RX PAUSE.  Later
		 * (in e1000_config_fc_after_link_up) we will disable the
		 * hw's ability to send PAUSE frames.
		 */
		mii_autoneg_adv_reg |= (NWAY_AR_ASM_DIR | NWAY_AR_PAUSE);
		break;
	case E1000_FC_TX_PAUSE:	/* 2 */
		/* TX Flow control is enabled, and RX Flow control is
		 * disabled, by a software over-ride.
		 */
		mii_autoneg_adv_reg |= NWAY_AR_ASM_DIR;
		mii_autoneg_adv_reg &= ~NWAY_AR_PAUSE;
		break;
	case E1000_FC_FULL:	/* 3 */
		/* Flow control (both RX and TX) is enabled by a software
		 * over-ride.
		 */
		mii_autoneg_adv_reg |= (NWAY_AR_ASM_DIR | NWAY_AR_PAUSE);
		break;
	default:
		e_dbg("Flow control param set incorrectly\n");
		return -E1000_ERR_CONFIG;
	}

	ret_val = e1000_write_phy_reg(hw, PHY_AUTONEG_ADV, mii_autoneg_adv_reg);
	if (ret_val)
		return ret_val;

	e_dbg("Auto-Neg Advertising %x\n", mii_autoneg_adv_reg);

	if (hw->phy_type == e1000_phy_8201) {
		mii_1000t_ctrl_reg = 0;
	} else {
		ret_val = e1000_write_phy_reg(hw, PHY_1000T_CTRL,
					      mii_1000t_ctrl_reg);
		if (ret_val)
			return ret_val;
	}

	return E1000_SUCCESS;
}