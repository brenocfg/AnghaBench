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
struct list_head {int dummy; } ;
struct ice_switch_info {TYPE_1__* recp_list; } ;
struct ice_hw {struct ice_switch_info* switch_info; } ;
struct TYPE_2__ {struct list_head filt_replay_rules; } ;

/* Variables and functions */
 size_t ICE_SW_LKUP_LAST ; 
 int /*<<< orphan*/  ice_rem_sw_rule_info (struct ice_hw*,struct list_head*) ; 
 int /*<<< orphan*/  list_empty (struct list_head*) ; 

void ice_rm_all_sw_replay_rule_info(struct ice_hw *hw)
{
	struct ice_switch_info *sw = hw->switch_info;
	u8 i;

	if (!sw)
		return;

	for (i = 0; i < ICE_SW_LKUP_LAST; i++) {
		if (!list_empty(&sw->recp_list[i].filt_replay_rules)) {
			struct list_head *l_head;

			l_head = &sw->recp_list[i].filt_replay_rules;
			ice_rem_sw_rule_info(hw, l_head);
		}
	}
}