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
struct TYPE_8__ {int /*<<< orphan*/  lan_id; } ;
struct TYPE_6__ {scalar_t__ (* write_iosf_sb_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;scalar_t__ (* read_iosf_sb_reg ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_7__ {TYPE_2__ ops; } ;
struct TYPE_5__ {int requested_mode; scalar_t__ strict_ieee; } ;
struct ixgbe_hw {TYPE_4__ bus; TYPE_3__ mac; TYPE_1__ fc; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ IXGBE_ERR_CONFIG ; 
 scalar_t__ IXGBE_ERR_INVALID_LINK_SETTINGS ; 
 int /*<<< orphan*/  IXGBE_KRM_AN_CNTL_1 (int /*<<< orphan*/ ) ; 
 int IXGBE_KRM_AN_CNTL_1_ASM_PAUSE ; 
 int IXGBE_KRM_AN_CNTL_1_SYM_PAUSE ; 
 int /*<<< orphan*/  IXGBE_SB_IOSF_TARGET_KR_PHY ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*) ; 
 int /*<<< orphan*/  hw_err (struct ixgbe_hw*,char*) ; 
 int ixgbe_fc_default ; 
#define  ixgbe_fc_full 131 
#define  ixgbe_fc_none 130 
#define  ixgbe_fc_rx_pause 129 
#define  ixgbe_fc_tx_pause 128 
 scalar_t__ ixgbe_restart_an_internal_phy_x550em (struct ixgbe_hw*) ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 ixgbe_setup_fc_backplane_x550em_a(struct ixgbe_hw *hw)
{
	s32 status = 0;
	u32 an_cntl = 0;

	/* Validate the requested mode */
	if (hw->fc.strict_ieee && hw->fc.requested_mode == ixgbe_fc_rx_pause) {
		hw_err(hw, "ixgbe_fc_rx_pause not valid in strict IEEE mode\n");
		return IXGBE_ERR_INVALID_LINK_SETTINGS;
	}

	if (hw->fc.requested_mode == ixgbe_fc_default)
		hw->fc.requested_mode = ixgbe_fc_full;

	/* Set up the 1G and 10G flow control advertisement registers so the
	 * HW will be able to do FC autoneg once the cable is plugged in.  If
	 * we link at 10G, the 1G advertisement is harmless and vice versa.
	 */
	status = hw->mac.ops.read_iosf_sb_reg(hw,
					IXGBE_KRM_AN_CNTL_1(hw->bus.lan_id),
					IXGBE_SB_IOSF_TARGET_KR_PHY, &an_cntl);

	if (status) {
		hw_dbg(hw, "Auto-Negotiation did not complete\n");
		return status;
	}

	/* The possible values of fc.requested_mode are:
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
		an_cntl &= ~(IXGBE_KRM_AN_CNTL_1_SYM_PAUSE |
			     IXGBE_KRM_AN_CNTL_1_ASM_PAUSE);
		break;
	case ixgbe_fc_tx_pause:
		/* Tx Flow control is enabled, and Rx Flow control is
		 * disabled by software override.
		 */
		an_cntl |= IXGBE_KRM_AN_CNTL_1_ASM_PAUSE;
		an_cntl &= ~IXGBE_KRM_AN_CNTL_1_SYM_PAUSE;
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
	case ixgbe_fc_full:
		/* Flow control (both Rx and Tx) is enabled by SW override. */
		an_cntl |= IXGBE_KRM_AN_CNTL_1_SYM_PAUSE |
			   IXGBE_KRM_AN_CNTL_1_ASM_PAUSE;
		break;
	default:
		hw_err(hw, "Flow control param set incorrectly\n");
		return IXGBE_ERR_CONFIG;
	}

	status = hw->mac.ops.write_iosf_sb_reg(hw,
					IXGBE_KRM_AN_CNTL_1(hw->bus.lan_id),
					IXGBE_SB_IOSF_TARGET_KR_PHY, an_cntl);

	/* Restart auto-negotiation. */
	status = ixgbe_restart_an_internal_phy_x550em(hw);

	return status;
}