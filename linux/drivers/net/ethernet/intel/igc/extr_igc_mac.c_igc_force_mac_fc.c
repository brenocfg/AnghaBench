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
typedef  int u32 ;
struct TYPE_2__ {int current_mode; } ;
struct igc_hw {TYPE_1__ fc; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IGC_CTRL ; 
 int IGC_CTRL_RFCE ; 
 int IGC_CTRL_TFCE ; 
 int /*<<< orphan*/  IGC_ERR_CONFIG ; 
 int /*<<< orphan*/  hw_dbg (char*,...) ; 
#define  igc_fc_full 131 
#define  igc_fc_none 130 
#define  igc_fc_rx_pause 129 
#define  igc_fc_tx_pause 128 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int) ; 

s32 igc_force_mac_fc(struct igc_hw *hw)
{
	s32 ret_val = 0;
	u32 ctrl;

	ctrl = rd32(IGC_CTRL);

	/* Because we didn't get link via the internal auto-negotiation
	 * mechanism (we either forced link or we got link via PHY
	 * auto-neg), we have to manually enable/disable transmit an
	 * receive flow control.
	 *
	 * The "Case" statement below enables/disable flow control
	 * according to the "hw->fc.current_mode" parameter.
	 *
	 * The possible values of the "fc" parameter are:
	 *      0:  Flow control is completely disabled
	 *      1:  Rx flow control is enabled (we can receive pause
	 *          frames but not send pause frames).
	 *      2:  Tx flow control is enabled (we can send pause frames
	 *          frames but we do not receive pause frames).
	 *      3:  Both Rx and TX flow control (symmetric) is enabled.
	 *  other:  No other values should be possible at this point.
	 */
	hw_dbg("hw->fc.current_mode = %u\n", hw->fc.current_mode);

	switch (hw->fc.current_mode) {
	case igc_fc_none:
		ctrl &= (~(IGC_CTRL_TFCE | IGC_CTRL_RFCE));
		break;
	case igc_fc_rx_pause:
		ctrl &= (~IGC_CTRL_TFCE);
		ctrl |= IGC_CTRL_RFCE;
		break;
	case igc_fc_tx_pause:
		ctrl &= (~IGC_CTRL_RFCE);
		ctrl |= IGC_CTRL_TFCE;
		break;
	case igc_fc_full:
		ctrl |= (IGC_CTRL_TFCE | IGC_CTRL_RFCE);
		break;
	default:
		hw_dbg("Flow control param set incorrectly\n");
		ret_val = -IGC_ERR_CONFIG;
		goto out;
	}

	wr32(IGC_CTRL, ctrl);

out:
	return ret_val;
}