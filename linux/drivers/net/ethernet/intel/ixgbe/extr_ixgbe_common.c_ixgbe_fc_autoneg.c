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
struct TYPE_8__ {int fc_was_autonegged; int /*<<< orphan*/  requested_mode; int /*<<< orphan*/  current_mode; scalar_t__ disable_fc_autoneg; } ;
struct TYPE_7__ {int media_type; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* check_link ) (struct ixgbe_hw*,int /*<<< orphan*/ *,int*,int) ;} ;
struct TYPE_6__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_4__ fc; TYPE_3__ phy; TYPE_2__ mac; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  ixgbe_link_speed ;

/* Variables and functions */
 scalar_t__ IXGBE_ERR_FC_NOT_NEGOTIATED ; 
 int /*<<< orphan*/  IXGBE_LINK_SPEED_1GB_FULL ; 
 int /*<<< orphan*/  ixgbe_device_supports_autoneg_fc (struct ixgbe_hw*) ; 
 scalar_t__ ixgbe_fc_autoneg_backplane (struct ixgbe_hw*) ; 
 scalar_t__ ixgbe_fc_autoneg_copper (struct ixgbe_hw*) ; 
 scalar_t__ ixgbe_fc_autoneg_fiber (struct ixgbe_hw*) ; 
#define  ixgbe_media_type_backplane 130 
#define  ixgbe_media_type_copper 129 
#define  ixgbe_media_type_fiber 128 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*,int /*<<< orphan*/ *,int*,int) ; 

void ixgbe_fc_autoneg(struct ixgbe_hw *hw)
{
	s32 ret_val = IXGBE_ERR_FC_NOT_NEGOTIATED;
	ixgbe_link_speed speed;
	bool link_up;

	/*
	 * AN should have completed when the cable was plugged in.
	 * Look for reasons to bail out.  Bail out if:
	 * - FC autoneg is disabled, or if
	 * - link is not up.
	 *
	 * Since we're being called from an LSC, link is already known to be up.
	 * So use link_up_wait_to_complete=false.
	 */
	if (hw->fc.disable_fc_autoneg)
		goto out;

	hw->mac.ops.check_link(hw, &speed, &link_up, false);
	if (!link_up)
		goto out;

	switch (hw->phy.media_type) {
	/* Autoneg flow control on fiber adapters */
	case ixgbe_media_type_fiber:
		if (speed == IXGBE_LINK_SPEED_1GB_FULL)
			ret_val = ixgbe_fc_autoneg_fiber(hw);
		break;

	/* Autoneg flow control on backplane adapters */
	case ixgbe_media_type_backplane:
		ret_val = ixgbe_fc_autoneg_backplane(hw);
		break;

	/* Autoneg flow control on copper adapters */
	case ixgbe_media_type_copper:
		if (ixgbe_device_supports_autoneg_fc(hw))
			ret_val = ixgbe_fc_autoneg_copper(hw);
		break;

	default:
		break;
	}

out:
	if (ret_val == 0) {
		hw->fc.fc_was_autonegged = true;
	} else {
		hw->fc.fc_was_autonegged = false;
		hw->fc.current_mode = hw->fc.requested_mode;
	}
}