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
struct ice_switch_info {TYPE_1__* recp_list; } ;
struct ice_hw {struct ice_switch_info* switch_info; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;
struct TYPE_2__ {int /*<<< orphan*/  filt_replay_rules; int /*<<< orphan*/  filt_rules; } ;

/* Variables and functions */
 size_t ICE_SW_LKUP_LAST ; 
 int /*<<< orphan*/  ice_rm_all_sw_replay_rule_info (struct ice_hw*) ; 
 int /*<<< orphan*/  list_replace_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum ice_status ice_replay_pre_init(struct ice_hw *hw)
{
	struct ice_switch_info *sw = hw->switch_info;
	u8 i;

	/* Delete old entries from replay filter list head if there is any */
	ice_rm_all_sw_replay_rule_info(hw);
	/* In start of replay, move entries into replay_rules list, it
	 * will allow adding rules entries back to filt_rules list,
	 * which is operational list.
	 */
	for (i = 0; i < ICE_SW_LKUP_LAST; i++)
		list_replace_init(&sw->recp_list[i].filt_rules,
				  &sw->recp_list[i].filt_replay_rules);

	return 0;
}