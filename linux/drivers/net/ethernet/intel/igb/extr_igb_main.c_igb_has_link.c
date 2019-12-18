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
struct TYPE_4__ {int /*<<< orphan*/  (* check_for_link ) (struct e1000_hw*) ;} ;
struct TYPE_5__ {scalar_t__ type; int /*<<< orphan*/  get_link_status; TYPE_1__ ops; } ;
struct e1000_hw {TYPE_3__ phy; TYPE_2__ mac; } ;
struct igb_adapter {int flags; int /*<<< orphan*/  link_check_timeout; int /*<<< orphan*/  netdev; struct e1000_hw hw; } ;

/* Variables and functions */
 scalar_t__ I210_I_PHY_ID ; 
 int IGB_FLAG_NEED_LINK_UPDATE ; 
 scalar_t__ e1000_i210 ; 
 scalar_t__ e1000_i211 ; 
#define  e1000_media_type_copper 130 
#define  e1000_media_type_internal_serdes 129 
#define  e1000_media_type_unknown 128 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*) ; 

bool igb_has_link(struct igb_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	bool link_active = false;

	/* get_link_status is set on LSC (link status) interrupt or
	 * rx sequence error interrupt.  get_link_status will stay
	 * false until the e1000_check_for_link establishes link
	 * for copper adapters ONLY
	 */
	switch (hw->phy.media_type) {
	case e1000_media_type_copper:
		if (!hw->mac.get_link_status)
			return true;
		/* fall through */
	case e1000_media_type_internal_serdes:
		hw->mac.ops.check_for_link(hw);
		link_active = !hw->mac.get_link_status;
		break;
	default:
	case e1000_media_type_unknown:
		break;
	}

	if (((hw->mac.type == e1000_i210) ||
	     (hw->mac.type == e1000_i211)) &&
	     (hw->phy.id == I210_I_PHY_ID)) {
		if (!netif_carrier_ok(adapter->netdev)) {
			adapter->flags &= ~IGB_FLAG_NEED_LINK_UPDATE;
		} else if (!(adapter->flags & IGB_FLAG_NEED_LINK_UPDATE)) {
			adapter->flags |= IGB_FLAG_NEED_LINK_UPDATE;
			adapter->link_check_timeout = jiffies;
		}
	}

	return link_active;
}