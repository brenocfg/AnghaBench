#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_9__ {int /*<<< orphan*/  (* write_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* read_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_10__ {int media_type; TYPE_4__ ops; } ;
struct TYPE_7__ {scalar_t__ (* prot_autoc_write ) (struct ixgbe_hw*,int,int) ;scalar_t__ (* prot_autoc_read ) (struct ixgbe_hw*,int*,int*) ;} ;
struct TYPE_8__ {scalar_t__ type; TYPE_2__ ops; } ;
struct TYPE_6__ {int requested_mode; scalar_t__ strict_ieee; } ;
struct ixgbe_hw {TYPE_5__ phy; TYPE_3__ mac; TYPE_1__ fc; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int IXGBE_AUTOC_ASM_PAUSE ; 
 int IXGBE_AUTOC_SYM_PAUSE ; 
 scalar_t__ IXGBE_ERR_CONFIG ; 
 scalar_t__ IXGBE_ERR_INVALID_LINK_SETTINGS ; 
 int /*<<< orphan*/  IXGBE_PCS1GANA ; 
 int IXGBE_PCS1GANA_ASM_PAUSE ; 
 int IXGBE_PCS1GANA_SYM_PAUSE ; 
 int /*<<< orphan*/  IXGBE_PCS1GLCTL ; 
 int IXGBE_PCS1GLCTL_AN_1G_TIMEOUT_EN ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int IXGBE_TAF_ASM_PAUSE ; 
 int IXGBE_TAF_SYM_PAUSE ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MDIO_AN_ADVERTISE ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*,...) ; 
 scalar_t__ ixgbe_device_supports_autoneg_fc (struct ixgbe_hw*) ; 
 int ixgbe_fc_default ; 
#define  ixgbe_fc_full 134 
#define  ixgbe_fc_none 133 
#define  ixgbe_fc_rx_pause 132 
#define  ixgbe_fc_tx_pause 131 
 scalar_t__ ixgbe_mac_X540 ; 
#define  ixgbe_media_type_backplane 130 
#define  ixgbe_media_type_copper 129 
#define  ixgbe_media_type_fiber 128 
 scalar_t__ stub1 (struct ixgbe_hw*,int*,int*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub3 (struct ixgbe_hw*,int,int) ; 
 int /*<<< orphan*/  stub4 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

s32 ixgbe_setup_fc_generic(struct ixgbe_hw *hw)
{
	s32 ret_val = 0;
	u32 reg = 0, reg_bp = 0;
	u16 reg_cu = 0;
	bool locked = false;

	/*
	 * Validate the requested mode.  Strict IEEE mode does not allow
	 * ixgbe_fc_rx_pause because it will cause us to fail at UNH.
	 */
	if (hw->fc.strict_ieee && hw->fc.requested_mode == ixgbe_fc_rx_pause) {
		hw_dbg(hw, "ixgbe_fc_rx_pause not valid in strict IEEE mode\n");
		return IXGBE_ERR_INVALID_LINK_SETTINGS;
	}

	/*
	 * 10gig parts do not have a word in the EEPROM to determine the
	 * default flow control setting, so we explicitly set it to full.
	 */
	if (hw->fc.requested_mode == ixgbe_fc_default)
		hw->fc.requested_mode = ixgbe_fc_full;

	/*
	 * Set up the 1G and 10G flow control advertisement registers so the
	 * HW will be able to do fc autoneg once the cable is plugged in.  If
	 * we link at 10G, the 1G advertisement is harmless and vice versa.
	 */
	switch (hw->phy.media_type) {
	case ixgbe_media_type_backplane:
		/* some MAC's need RMW protection on AUTOC */
		ret_val = hw->mac.ops.prot_autoc_read(hw, &locked, &reg_bp);
		if (ret_val)
			return ret_val;

		/* fall through - only backplane uses autoc */
	case ixgbe_media_type_fiber:
		reg = IXGBE_READ_REG(hw, IXGBE_PCS1GANA);

		break;
	case ixgbe_media_type_copper:
		hw->phy.ops.read_reg(hw, MDIO_AN_ADVERTISE,
					MDIO_MMD_AN, &reg_cu);
		break;
	default:
		break;
	}

	/*
	 * The possible values of fc.requested_mode are:
	 * 0: Flow control is completely disabled
	 * 1: Rx flow control is enabled (we can receive pause frames,
	 *    but not send pause frames).
	 * 2: Tx flow control is enabled (we can send pause frames but
	 *    we do not support receiving pause frames).
	 * 3: Both Rx and Tx flow control (symmetric) are enabled.
	 * other: Invalid.
	 */
	switch (hw->fc.requested_mode) {
	case ixgbe_fc_none:
		/* Flow control completely disabled by software override. */
		reg &= ~(IXGBE_PCS1GANA_SYM_PAUSE | IXGBE_PCS1GANA_ASM_PAUSE);
		if (hw->phy.media_type == ixgbe_media_type_backplane)
			reg_bp &= ~(IXGBE_AUTOC_SYM_PAUSE |
				    IXGBE_AUTOC_ASM_PAUSE);
		else if (hw->phy.media_type == ixgbe_media_type_copper)
			reg_cu &= ~(IXGBE_TAF_SYM_PAUSE | IXGBE_TAF_ASM_PAUSE);
		break;
	case ixgbe_fc_tx_pause:
		/*
		 * Tx Flow control is enabled, and Rx Flow control is
		 * disabled by software override.
		 */
		reg |= IXGBE_PCS1GANA_ASM_PAUSE;
		reg &= ~IXGBE_PCS1GANA_SYM_PAUSE;
		if (hw->phy.media_type == ixgbe_media_type_backplane) {
			reg_bp |= IXGBE_AUTOC_ASM_PAUSE;
			reg_bp &= ~IXGBE_AUTOC_SYM_PAUSE;
		} else if (hw->phy.media_type == ixgbe_media_type_copper) {
			reg_cu |= IXGBE_TAF_ASM_PAUSE;
			reg_cu &= ~IXGBE_TAF_SYM_PAUSE;
		}
		break;
	case ixgbe_fc_rx_pause:
		/*
		 * Rx Flow control is enabled and Tx Flow control is
		 * disabled by software override. Since there really
		 * isn't a way to advertise that we are capable of RX
		 * Pause ONLY, we will advertise that we support both
		 * symmetric and asymmetric Rx PAUSE, as such we fall
		 * through to the fc_full statement.  Later, we will
		 * disable the adapter's ability to send PAUSE frames.
		 */
	case ixgbe_fc_full:
		/* Flow control (both Rx and Tx) is enabled by SW override. */
		reg |= IXGBE_PCS1GANA_SYM_PAUSE | IXGBE_PCS1GANA_ASM_PAUSE;
		if (hw->phy.media_type == ixgbe_media_type_backplane)
			reg_bp |= IXGBE_AUTOC_SYM_PAUSE |
				  IXGBE_AUTOC_ASM_PAUSE;
		else if (hw->phy.media_type == ixgbe_media_type_copper)
			reg_cu |= IXGBE_TAF_SYM_PAUSE | IXGBE_TAF_ASM_PAUSE;
		break;
	default:
		hw_dbg(hw, "Flow control param set incorrectly\n");
		return IXGBE_ERR_CONFIG;
	}

	if (hw->mac.type != ixgbe_mac_X540) {
		/*
		 * Enable auto-negotiation between the MAC & PHY;
		 * the MAC will advertise clause 37 flow control.
		 */
		IXGBE_WRITE_REG(hw, IXGBE_PCS1GANA, reg);
		reg = IXGBE_READ_REG(hw, IXGBE_PCS1GLCTL);

		/* Disable AN timeout */
		if (hw->fc.strict_ieee)
			reg &= ~IXGBE_PCS1GLCTL_AN_1G_TIMEOUT_EN;

		IXGBE_WRITE_REG(hw, IXGBE_PCS1GLCTL, reg);
		hw_dbg(hw, "Set up FC; PCS1GLCTL = 0x%08X\n", reg);
	}

	/*
	 * AUTOC restart handles negotiation of 1G and 10G on backplane
	 * and copper. There is no need to set the PCS1GCTL register.
	 *
	 */
	if (hw->phy.media_type == ixgbe_media_type_backplane) {
		/* Need the SW/FW semaphore around AUTOC writes if 82599 and
		 * LESM is on, likewise reset_pipeline requries the lock as
		 * it also writes AUTOC.
		 */
		ret_val = hw->mac.ops.prot_autoc_write(hw, reg_bp, locked);
		if (ret_val)
			return ret_val;

	} else if ((hw->phy.media_type == ixgbe_media_type_copper) &&
		   ixgbe_device_supports_autoneg_fc(hw)) {
		hw->phy.ops.write_reg(hw, MDIO_AN_ADVERTISE,
				      MDIO_MMD_AN, reg_cu);
	}

	hw_dbg(hw, "Set up FC; IXGBE_AUTOC = 0x%08X\n", reg);
	return ret_val;
}