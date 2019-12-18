#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct e1000_hw {int media_type; int get_link_status; int serdes_has_link; int /*<<< orphan*/  mac_type; } ;
struct e1000_adapter {struct e1000_hw hw; } ;

/* Variables and functions */
 int E1000_STATUS_LU ; 
 int /*<<< orphan*/  STATUS ; 
 int /*<<< orphan*/  e1000_ce4100 ; 
 int /*<<< orphan*/  e1000_check_for_link (struct e1000_hw*) ; 
#define  e1000_media_type_copper 130 
#define  e1000_media_type_fiber 129 
#define  e1000_media_type_internal_serdes 128 
 int er32 (int /*<<< orphan*/ ) ; 

bool e1000_has_link(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	bool link_active = false;

	/* get_link_status is set on LSC (link status) interrupt or rx
	 * sequence error interrupt (except on intel ce4100).
	 * get_link_status will stay false until the
	 * e1000_check_for_link establishes link for copper adapters
	 * ONLY
	 */
	switch (hw->media_type) {
	case e1000_media_type_copper:
		if (hw->mac_type == e1000_ce4100)
			hw->get_link_status = 1;
		if (hw->get_link_status) {
			e1000_check_for_link(hw);
			link_active = !hw->get_link_status;
		} else {
			link_active = true;
		}
		break;
	case e1000_media_type_fiber:
		e1000_check_for_link(hw);
		link_active = !!(er32(STATUS) & E1000_STATUS_LU);
		break;
	case e1000_media_type_internal_serdes:
		e1000_check_for_link(hw);
		link_active = hw->serdes_has_link;
		break;
	default:
		break;
	}

	return link_active;
}