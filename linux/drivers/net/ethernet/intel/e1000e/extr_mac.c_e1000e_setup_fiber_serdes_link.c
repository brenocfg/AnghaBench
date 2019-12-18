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
typedef  int u32 ;
struct TYPE_6__ {scalar_t__ media_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* config_collision_dist ) (struct e1000_hw*) ;} ;
struct TYPE_5__ {TYPE_1__ ops; } ;
struct e1000_hw {TYPE_3__ phy; TYPE_2__ mac; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int E1000_CTRL_LRST ; 
 int E1000_CTRL_SWDPIN1 ; 
 scalar_t__ e1000_commit_fc_settings_generic (struct e1000_hw*) ; 
 scalar_t__ e1000_media_type_internal_serdes ; 
 scalar_t__ e1000_poll_fiber_serdes_link_generic (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1e_flush () ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

s32 e1000e_setup_fiber_serdes_link(struct e1000_hw *hw)
{
	u32 ctrl;
	s32 ret_val;

	ctrl = er32(CTRL);

	/* Take the link out of reset */
	ctrl &= ~E1000_CTRL_LRST;

	hw->mac.ops.config_collision_dist(hw);

	ret_val = e1000_commit_fc_settings_generic(hw);
	if (ret_val)
		return ret_val;

	/* Since auto-negotiation is enabled, take the link out of reset (the
	 * link will be in reset, because we previously reset the chip). This
	 * will restart auto-negotiation.  If auto-negotiation is successful
	 * then the link-up status bit will be set and the flow control enable
	 * bits (RFCE and TFCE) will be set according to their negotiated value.
	 */
	e_dbg("Auto-negotiation enabled\n");

	ew32(CTRL, ctrl);
	e1e_flush();
	usleep_range(1000, 2000);

	/* For these adapters, the SW definable pin 1 is set when the optics
	 * detect a signal.  If we have a signal, then poll for a "Link-Up"
	 * indication.
	 */
	if (hw->phy.media_type == e1000_media_type_internal_serdes ||
	    (er32(CTRL) & E1000_CTRL_SWDPIN1)) {
		ret_val = e1000_poll_fiber_serdes_link_generic(hw);
	} else {
		e_dbg("No signal detected\n");
	}

	return ret_val;
}