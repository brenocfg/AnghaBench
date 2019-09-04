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
struct TYPE_2__ {scalar_t__ requested_mode; void* current_mode; } ;
struct ixgbe_hw {TYPE_1__ fc; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_ERR_FC_NOT_NEGOTIATED ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*) ; 
 scalar_t__ ixgbe_fc_full ; 
 void* ixgbe_fc_none ; 
 void* ixgbe_fc_rx_pause ; 
 void* ixgbe_fc_tx_pause ; 

s32 ixgbe_negotiate_fc(struct ixgbe_hw *hw, u32 adv_reg, u32 lp_reg,
		       u32 adv_sym, u32 adv_asm, u32 lp_sym, u32 lp_asm)
{
	if ((!(adv_reg)) ||  (!(lp_reg)))
		return IXGBE_ERR_FC_NOT_NEGOTIATED;

	if ((adv_reg & adv_sym) && (lp_reg & lp_sym)) {
		/*
		 * Now we need to check if the user selected Rx ONLY
		 * of pause frames.  In this case, we had to advertise
		 * FULL flow control because we could not advertise RX
		 * ONLY. Hence, we must now check to see if we need to
		 * turn OFF the TRANSMISSION of PAUSE frames.
		 */
		if (hw->fc.requested_mode == ixgbe_fc_full) {
			hw->fc.current_mode = ixgbe_fc_full;
			hw_dbg(hw, "Flow Control = FULL.\n");
		} else {
			hw->fc.current_mode = ixgbe_fc_rx_pause;
			hw_dbg(hw, "Flow Control=RX PAUSE frames only\n");
		}
	} else if (!(adv_reg & adv_sym) && (adv_reg & adv_asm) &&
		   (lp_reg & lp_sym) && (lp_reg & lp_asm)) {
		hw->fc.current_mode = ixgbe_fc_tx_pause;
		hw_dbg(hw, "Flow Control = TX PAUSE frames only.\n");
	} else if ((adv_reg & adv_sym) && (adv_reg & adv_asm) &&
		   !(lp_reg & lp_sym) && (lp_reg & lp_asm)) {
		hw->fc.current_mode = ixgbe_fc_rx_pause;
		hw_dbg(hw, "Flow Control = RX PAUSE frames only.\n");
	} else {
		hw->fc.current_mode = ixgbe_fc_none;
		hw_dbg(hw, "Flow Control = NONE.\n");
	}
	return 0;
}