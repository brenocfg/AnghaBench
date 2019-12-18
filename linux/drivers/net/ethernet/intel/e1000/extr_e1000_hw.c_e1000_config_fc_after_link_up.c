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
struct e1000_hw {scalar_t__ media_type; scalar_t__ original_fc; void* fc; scalar_t__ fc_strict_ieee; scalar_t__ autoneg; scalar_t__ autoneg_failed; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ E1000_FC_FULL ; 
 scalar_t__ E1000_FC_NONE ; 
 void* E1000_FC_RX_PAUSE ; 
 scalar_t__ E1000_FC_TX_PAUSE ; 
 scalar_t__ E1000_SUCCESS ; 
 int HALF_DUPLEX ; 
 int MII_SR_AUTONEG_COMPLETE ; 
 int NWAY_AR_ASM_DIR ; 
 int NWAY_AR_PAUSE ; 
 int NWAY_LPAR_ASM_DIR ; 
 int NWAY_LPAR_PAUSE ; 
 int /*<<< orphan*/  PHY_AUTONEG_ADV ; 
 int /*<<< orphan*/  PHY_LP_ABILITY ; 
 int /*<<< orphan*/  PHY_STATUS ; 
 scalar_t__ e1000_force_mac_fc (struct e1000_hw*) ; 
 scalar_t__ e1000_get_speed_and_duplex (struct e1000_hw*,int*,int*) ; 
 scalar_t__ e1000_media_type_copper ; 
 scalar_t__ e1000_media_type_fiber ; 
 scalar_t__ e1000_media_type_internal_serdes ; 
 scalar_t__ e1000_read_phy_reg (struct e1000_hw*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  e_dbg (char*) ; 

__attribute__((used)) static s32 e1000_config_fc_after_link_up(struct e1000_hw *hw)
{
	s32 ret_val;
	u16 mii_status_reg;
	u16 mii_nway_adv_reg;
	u16 mii_nway_lp_ability_reg;
	u16 speed;
	u16 duplex;

	/* Check for the case where we have fiber media and auto-neg failed
	 * so we had to force link.  In this case, we need to force the
	 * configuration of the MAC to match the "fc" parameter.
	 */
	if (((hw->media_type == e1000_media_type_fiber) &&
	     (hw->autoneg_failed)) ||
	    ((hw->media_type == e1000_media_type_internal_serdes) &&
	     (hw->autoneg_failed)) ||
	    ((hw->media_type == e1000_media_type_copper) &&
	     (!hw->autoneg))) {
		ret_val = e1000_force_mac_fc(hw);
		if (ret_val) {
			e_dbg("Error forcing flow control settings\n");
			return ret_val;
		}
	}

	/* Check for the case where we have copper media and auto-neg is
	 * enabled.  In this case, we need to check and see if Auto-Neg
	 * has completed, and if so, how the PHY and link partner has
	 * flow control configured.
	 */
	if ((hw->media_type == e1000_media_type_copper) && hw->autoneg) {
		/* Read the MII Status Register and check to see if AutoNeg
		 * has completed.  We read this twice because this reg has
		 * some "sticky" (latched) bits.
		 */
		ret_val = e1000_read_phy_reg(hw, PHY_STATUS, &mii_status_reg);
		if (ret_val)
			return ret_val;
		ret_val = e1000_read_phy_reg(hw, PHY_STATUS, &mii_status_reg);
		if (ret_val)
			return ret_val;

		if (mii_status_reg & MII_SR_AUTONEG_COMPLETE) {
			/* The AutoNeg process has completed, so we now need to
			 * read both the Auto Negotiation Advertisement Register
			 * (Address 4) and the Auto_Negotiation Base Page
			 * Ability Register (Address 5) to determine how flow
			 * control was negotiated.
			 */
			ret_val = e1000_read_phy_reg(hw, PHY_AUTONEG_ADV,
						     &mii_nway_adv_reg);
			if (ret_val)
				return ret_val;
			ret_val = e1000_read_phy_reg(hw, PHY_LP_ABILITY,
						     &mii_nway_lp_ability_reg);
			if (ret_val)
				return ret_val;

			/* Two bits in the Auto Negotiation Advertisement
			 * Register (Address 4) and two bits in the Auto
			 * Negotiation Base Page Ability Register (Address 5)
			 * determine flow control for both the PHY and the link
			 * partner.  The following table, taken out of the IEEE
			 * 802.3ab/D6.0 dated March 25, 1999, describes these
			 * PAUSE resolution bits and how flow control is
			 * determined based upon these settings.
			 * NOTE:  DC = Don't Care
			 *
			 *   LOCAL DEVICE  |   LINK PARTNER
			 * PAUSE | ASM_DIR | PAUSE | ASM_DIR | NIC Resolution
			 *-------|---------|-------|---------|------------------
			 *   0   |    0    |  DC   |   DC    | E1000_FC_NONE
			 *   0   |    1    |   0   |   DC    | E1000_FC_NONE
			 *   0   |    1    |   1   |    0    | E1000_FC_NONE
			 *   0   |    1    |   1   |    1    | E1000_FC_TX_PAUSE
			 *   1   |    0    |   0   |   DC    | E1000_FC_NONE
			 *   1   |   DC    |   1   |   DC    | E1000_FC_FULL
			 *   1   |    1    |   0   |    0    | E1000_FC_NONE
			 *   1   |    1    |   0   |    1    | E1000_FC_RX_PAUSE
			 *
			 */
			/* Are both PAUSE bits set to 1?  If so, this implies
			 * Symmetric Flow Control is enabled at both ends.  The
			 * ASM_DIR bits are irrelevant per the spec.
			 *
			 * For Symmetric Flow Control:
			 *
			 *   LOCAL DEVICE  |   LINK PARTNER
			 * PAUSE | ASM_DIR | PAUSE | ASM_DIR | Result
			 *-------|---------|-------|---------|------------------
			 *   1   |   DC    |   1   |   DC    | E1000_FC_FULL
			 *
			 */
			if ((mii_nway_adv_reg & NWAY_AR_PAUSE) &&
			    (mii_nway_lp_ability_reg & NWAY_LPAR_PAUSE)) {
				/* Now we need to check if the user selected Rx
				 * ONLY of pause frames.  In this case, we had
				 * to advertise FULL flow control because we
				 * could not advertise Rx ONLY. Hence, we must
				 * now check to see if we need to turn OFF the
				 * TRANSMISSION of PAUSE frames.
				 */
				if (hw->original_fc == E1000_FC_FULL) {
					hw->fc = E1000_FC_FULL;
					e_dbg("Flow Control = FULL.\n");
				} else {
					hw->fc = E1000_FC_RX_PAUSE;
					e_dbg
					    ("Flow Control = RX PAUSE frames only.\n");
				}
			}
			/* For receiving PAUSE frames ONLY.
			 *
			 *   LOCAL DEVICE  |   LINK PARTNER
			 * PAUSE | ASM_DIR | PAUSE | ASM_DIR | Result
			 *-------|---------|-------|---------|------------------
			 *   0   |    1    |   1   |    1    | E1000_FC_TX_PAUSE
			 *
			 */
			else if (!(mii_nway_adv_reg & NWAY_AR_PAUSE) &&
				 (mii_nway_adv_reg & NWAY_AR_ASM_DIR) &&
				 (mii_nway_lp_ability_reg & NWAY_LPAR_PAUSE) &&
				 (mii_nway_lp_ability_reg & NWAY_LPAR_ASM_DIR)) {
				hw->fc = E1000_FC_TX_PAUSE;
				e_dbg
				    ("Flow Control = TX PAUSE frames only.\n");
			}
			/* For transmitting PAUSE frames ONLY.
			 *
			 *   LOCAL DEVICE  |   LINK PARTNER
			 * PAUSE | ASM_DIR | PAUSE | ASM_DIR | Result
			 *-------|---------|-------|---------|------------------
			 *   1   |    1    |   0   |    1    | E1000_FC_RX_PAUSE
			 *
			 */
			else if ((mii_nway_adv_reg & NWAY_AR_PAUSE) &&
				 (mii_nway_adv_reg & NWAY_AR_ASM_DIR) &&
				 !(mii_nway_lp_ability_reg & NWAY_LPAR_PAUSE) &&
				 (mii_nway_lp_ability_reg & NWAY_LPAR_ASM_DIR)) {
				hw->fc = E1000_FC_RX_PAUSE;
				e_dbg
				    ("Flow Control = RX PAUSE frames only.\n");
			}
			/* Per the IEEE spec, at this point flow control should
			 * be disabled.  However, we want to consider that we
			 * could be connected to a legacy switch that doesn't
			 * advertise desired flow control, but can be forced on
			 * the link partner.  So if we advertised no flow
			 * control, that is what we will resolve to.  If we
			 * advertised some kind of receive capability (Rx Pause
			 * Only or Full Flow Control) and the link partner
			 * advertised none, we will configure ourselves to
			 * enable Rx Flow Control only.  We can do this safely
			 * for two reasons:  If the link partner really
			 * didn't want flow control enabled, and we enable Rx,
			 * no harm done since we won't be receiving any PAUSE
			 * frames anyway.  If the intent on the link partner was
			 * to have flow control enabled, then by us enabling Rx
			 * only, we can at least receive pause frames and
			 * process them. This is a good idea because in most
			 * cases, since we are predominantly a server NIC, more
			 * times than not we will be asked to delay transmission
			 * of packets than asking our link partner to pause
			 * transmission of frames.
			 */
			else if ((hw->original_fc == E1000_FC_NONE ||
				  hw->original_fc == E1000_FC_TX_PAUSE) ||
				 hw->fc_strict_ieee) {
				hw->fc = E1000_FC_NONE;
				e_dbg("Flow Control = NONE.\n");
			} else {
				hw->fc = E1000_FC_RX_PAUSE;
				e_dbg
				    ("Flow Control = RX PAUSE frames only.\n");
			}

			/* Now we need to do one last check...  If we auto-
			 * negotiated to HALF DUPLEX, flow control should not be
			 * enabled per IEEE 802.3 spec.
			 */
			ret_val =
			    e1000_get_speed_and_duplex(hw, &speed, &duplex);
			if (ret_val) {
				e_dbg
				    ("Error getting link speed and duplex\n");
				return ret_val;
			}

			if (duplex == HALF_DUPLEX)
				hw->fc = E1000_FC_NONE;

			/* Now we call a subroutine to actually force the MAC
			 * controller to use the correct flow control settings.
			 */
			ret_val = e1000_force_mac_fc(hw);
			if (ret_val) {
				e_dbg
				    ("Error forcing flow control settings\n");
				return ret_val;
			}
		} else {
			e_dbg
			    ("Copper PHY and Auto Neg has not completed.\n");
		}
	}
	return E1000_SUCCESS;
}