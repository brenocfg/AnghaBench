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
struct TYPE_6__ {int media_type; scalar_t__ id; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* check_for_link ) (struct igc_hw*) ;} ;
struct TYPE_5__ {scalar_t__ type; int /*<<< orphan*/  get_link_status; TYPE_1__ ops; } ;
struct igc_hw {TYPE_3__ phy; TYPE_2__ mac; } ;
struct igc_adapter {int flags; int /*<<< orphan*/  link_check_timeout; int /*<<< orphan*/  netdev; struct igc_hw hw; } ;

/* Variables and functions */
 scalar_t__ I225_I_PHY_ID ; 
 int IGC_FLAG_NEED_LINK_UPDATE ; 
 scalar_t__ igc_i225 ; 
#define  igc_media_type_copper 129 
#define  igc_media_type_unknown 128 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct igc_hw*) ; 

bool igc_has_link(struct igc_adapter *adapter)
{
	struct igc_hw *hw = &adapter->hw;
	bool link_active = false;

	/* get_link_status is set on LSC (link status) interrupt or
	 * rx sequence error interrupt.  get_link_status will stay
	 * false until the igc_check_for_link establishes link
	 * for copper adapters ONLY
	 */
	switch (hw->phy.media_type) {
	case igc_media_type_copper:
		if (!hw->mac.get_link_status)
			return true;
		hw->mac.ops.check_for_link(hw);
		link_active = !hw->mac.get_link_status;
		break;
	default:
	case igc_media_type_unknown:
		break;
	}

	if (hw->mac.type == igc_i225 &&
	    hw->phy.id == I225_I_PHY_ID) {
		if (!netif_carrier_ok(adapter->netdev)) {
			adapter->flags &= ~IGC_FLAG_NEED_LINK_UPDATE;
		} else if (!(adapter->flags & IGC_FLAG_NEED_LINK_UPDATE)) {
			adapter->flags |= IGC_FLAG_NEED_LINK_UPDATE;
			adapter->link_check_timeout = jiffies;
		}
	}

	return link_active;
}