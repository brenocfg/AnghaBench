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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct list_head {int dummy; } ;
struct ice_switch_info {TYPE_1__* recp_list; } ;
struct ice_hw {struct ice_switch_info* switch_info; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_2__ {struct list_head filt_replay_rules; } ;

/* Variables and functions */
 size_t ICE_SW_LKUP_LAST ; 
 int ice_replay_vsi_fltr (struct ice_hw*,int /*<<< orphan*/ ,size_t,struct list_head*) ; 

enum ice_status ice_replay_vsi_all_fltr(struct ice_hw *hw, u16 vsi_handle)
{
	struct ice_switch_info *sw = hw->switch_info;
	enum ice_status status = 0;
	u8 i;

	for (i = 0; i < ICE_SW_LKUP_LAST; i++) {
		struct list_head *head;

		head = &sw->recp_list[i].filt_replay_rules;
		status = ice_replay_vsi_fltr(hw, vsi_handle, i, head);
		if (status)
			return status;
	}
	return status;
}