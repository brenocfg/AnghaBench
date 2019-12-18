#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ requested_mode; scalar_t__ current_mode; int /*<<< orphan*/  pause_time; } ;
struct TYPE_4__ {scalar_t__ (* setup_physical_interface ) (struct igc_hw*) ;} ;
struct TYPE_5__ {TYPE_1__ ops; } ;
struct igc_hw {TYPE_3__ fc; TYPE_2__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FLOW_CONTROL_ADDRESS_HIGH ; 
 int /*<<< orphan*/  FLOW_CONTROL_ADDRESS_LOW ; 
 int /*<<< orphan*/  FLOW_CONTROL_TYPE ; 
 int /*<<< orphan*/  IGC_FCAH ; 
 int /*<<< orphan*/  IGC_FCAL ; 
 int /*<<< orphan*/  IGC_FCT ; 
 int /*<<< orphan*/  IGC_FCTTV ; 
 int /*<<< orphan*/  hw_dbg (char*,...) ; 
 scalar_t__ igc_check_reset_block (struct igc_hw*) ; 
 scalar_t__ igc_fc_default ; 
 scalar_t__ igc_fc_full ; 
 scalar_t__ igc_set_fc_watermarks (struct igc_hw*) ; 
 scalar_t__ stub1 (struct igc_hw*) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

s32 igc_setup_link(struct igc_hw *hw)
{
	s32 ret_val = 0;

	/* In the case of the phy reset being blocked, we already have a link.
	 * We do not need to set it up again.
	 */
	if (igc_check_reset_block(hw))
		goto out;

	/* If requested flow control is set to default, set flow control
	 * to the both 'rx' and 'tx' pause frames.
	 */
	if (hw->fc.requested_mode == igc_fc_default)
		hw->fc.requested_mode = igc_fc_full;

	/* We want to save off the original Flow Control configuration just
	 * in case we get disconnected and then reconnected into a different
	 * hub or switch with different Flow Control capabilities.
	 */
	hw->fc.current_mode = hw->fc.requested_mode;

	hw_dbg("After fix-ups FlowControl is now = %x\n", hw->fc.current_mode);

	/* Call the necessary media_type subroutine to configure the link. */
	ret_val = hw->mac.ops.setup_physical_interface(hw);
	if (ret_val)
		goto out;

	/* Initialize the flow control address, type, and PAUSE timer
	 * registers to their default values.  This is done even if flow
	 * control is disabled, because it does not hurt anything to
	 * initialize these registers.
	 */
	hw_dbg("Initializing the Flow Control address, type and timer regs\n");
	wr32(IGC_FCT, FLOW_CONTROL_TYPE);
	wr32(IGC_FCAH, FLOW_CONTROL_ADDRESS_HIGH);
	wr32(IGC_FCAL, FLOW_CONTROL_ADDRESS_LOW);

	wr32(IGC_FCTTV, hw->fc.pause_time);

	ret_val = igc_set_fc_watermarks(hw);

out:
	return ret_val;
}