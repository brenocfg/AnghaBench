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
struct TYPE_6__ {int media_type; scalar_t__ type; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* check_for_link ) (struct e1000_hw*) ;} ;
struct TYPE_5__ {int serdes_has_link; TYPE_1__ ops; int /*<<< orphan*/  get_link_status; } ;
struct e1000_hw {TYPE_3__ phy; TYPE_2__ mac; } ;
struct e1000_adapter {struct e1000_hw hw; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  E1000_ERR_PHY ; 
 int E1000_PHY_CTRL_GBE_DISABLE ; 
 int E1000_STATUS_LU ; 
 int /*<<< orphan*/  STATUS ; 
#define  e1000_media_type_copper 131 
#define  e1000_media_type_fiber 130 
#define  e1000_media_type_internal_serdes 129 
#define  e1000_media_type_unknown 128 
 scalar_t__ e1000_phy_igp_3 ; 
 int /*<<< orphan*/  e_info (char*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub2 (struct e1000_hw*) ; 
 int /*<<< orphan*/  stub3 (struct e1000_hw*) ; 

__attribute__((used)) static bool e1000e_has_link(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	bool link_active = false;
	s32 ret_val = 0;

	/* get_link_status is set on LSC (link status) interrupt or
	 * Rx sequence error interrupt.  get_link_status will stay
	 * true until the check_for_link establishes link
	 * for copper adapters ONLY
	 */
	switch (hw->phy.media_type) {
	case e1000_media_type_copper:
		if (hw->mac.get_link_status) {
			ret_val = hw->mac.ops.check_for_link(hw);
			link_active = !hw->mac.get_link_status;
		} else {
			link_active = true;
		}
		break;
	case e1000_media_type_fiber:
		ret_val = hw->mac.ops.check_for_link(hw);
		link_active = !!(er32(STATUS) & E1000_STATUS_LU);
		break;
	case e1000_media_type_internal_serdes:
		ret_val = hw->mac.ops.check_for_link(hw);
		link_active = hw->mac.serdes_has_link;
		break;
	default:
	case e1000_media_type_unknown:
		break;
	}

	if ((ret_val == -E1000_ERR_PHY) && (hw->phy.type == e1000_phy_igp_3) &&
	    (er32(CTRL) & E1000_PHY_CTRL_GBE_DISABLE)) {
		/* See e1000_kmrn_lock_loss_workaround_ich8lan() */
		e_info("Gigabit has been disabled, downgrading speed\n");
	}

	return link_active;
}