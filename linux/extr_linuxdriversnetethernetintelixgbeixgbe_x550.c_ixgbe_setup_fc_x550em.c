#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {int requested_mode; int disable_fc_autoneg; scalar_t__ strict_ieee; } ;
struct TYPE_7__ {int /*<<< orphan*/  lan_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* write_iosf_sb_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* read_iosf_sb_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_6__ {TYPE_1__ ops; } ;
struct ixgbe_hw {int device_id; TYPE_4__ fc; TYPE_3__ bus; TYPE_2__ mac; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
#define  IXGBE_DEV_ID_X550EM_A_KR 135 
#define  IXGBE_DEV_ID_X550EM_A_KR_L 134 
#define  IXGBE_DEV_ID_X550EM_X_KR 133 
#define  IXGBE_DEV_ID_X550EM_X_XFI 132 
 int /*<<< orphan*/  IXGBE_ERR_CONFIG ; 
 int /*<<< orphan*/  IXGBE_ERR_INVALID_LINK_SETTINGS ; 
 int /*<<< orphan*/  IXGBE_KRM_AN_CNTL_1 (int /*<<< orphan*/ ) ; 
 int IXGBE_KRM_AN_CNTL_1_ASM_PAUSE ; 
 int IXGBE_KRM_AN_CNTL_1_SYM_PAUSE ; 
 int /*<<< orphan*/  IXGBE_SB_IOSF_TARGET_KR_PHY ; 
 int /*<<< orphan*/  hw_err (struct ixgbe_hw*,char*) ; 
 int ixgbe_fc_default ; 
#define  ixgbe_fc_full 131 
#define  ixgbe_fc_none 130 
#define  ixgbe_fc_rx_pause 129 
#define  ixgbe_fc_tx_pause 128 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 ixgbe_setup_fc_x550em(struct ixgbe_hw *hw)
{
	bool pause, asm_dir;
	u32 reg_val;
	s32 rc = 0;

	/* Validate the requested mode */
	if (hw->fc.strict_ieee && hw->fc.requested_mode == ixgbe_fc_rx_pause) {
		hw_err(hw, "ixgbe_fc_rx_pause not valid in strict IEEE mode\n");
		return IXGBE_ERR_INVALID_LINK_SETTINGS;
	}

	/* 10gig parts do not have a word in the EEPROM to determine the
	 * default flow control setting, so we explicitly set it to full.
	 */
	if (hw->fc.requested_mode == ixgbe_fc_default)
		hw->fc.requested_mode = ixgbe_fc_full;

	/* Determine PAUSE and ASM_DIR bits. */
	switch (hw->fc.requested_mode) {
	case ixgbe_fc_none:
		pause = false;
		asm_dir = false;
		break;
	case ixgbe_fc_tx_pause:
		pause = false;
		asm_dir = true;
		break;
	case ixgbe_fc_rx_pause:
		/* Rx Flow control is enabled and Tx Flow control is
		 * disabled by software override. Since there really
		 * isn't a way to advertise that we are capable of RX
		 * Pause ONLY, we will advertise that we support both
		 * symmetric and asymmetric Rx PAUSE, as such we fall
		 * through to the fc_full statement.  Later, we will
		 * disable the adapter's ability to send PAUSE frames.
		 */
		/* Fallthrough */
	case ixgbe_fc_full:
		pause = true;
		asm_dir = true;
		break;
	default:
		hw_err(hw, "Flow control param set incorrectly\n");
		return IXGBE_ERR_CONFIG;
	}

	switch (hw->device_id) {
	case IXGBE_DEV_ID_X550EM_X_KR:
	case IXGBE_DEV_ID_X550EM_A_KR:
	case IXGBE_DEV_ID_X550EM_A_KR_L:
		rc = hw->mac.ops.read_iosf_sb_reg(hw,
					    IXGBE_KRM_AN_CNTL_1(hw->bus.lan_id),
					    IXGBE_SB_IOSF_TARGET_KR_PHY,
					    &reg_val);
		if (rc)
			return rc;

		reg_val &= ~(IXGBE_KRM_AN_CNTL_1_SYM_PAUSE |
			     IXGBE_KRM_AN_CNTL_1_ASM_PAUSE);
		if (pause)
			reg_val |= IXGBE_KRM_AN_CNTL_1_SYM_PAUSE;
		if (asm_dir)
			reg_val |= IXGBE_KRM_AN_CNTL_1_ASM_PAUSE;
		rc = hw->mac.ops.write_iosf_sb_reg(hw,
					    IXGBE_KRM_AN_CNTL_1(hw->bus.lan_id),
					    IXGBE_SB_IOSF_TARGET_KR_PHY,
					    reg_val);

		/* This device does not fully support AN. */
		hw->fc.disable_fc_autoneg = true;
		break;
	case IXGBE_DEV_ID_X550EM_X_XFI:
		hw->fc.disable_fc_autoneg = true;
		break;
	default:
		break;
	}
	return rc;
}