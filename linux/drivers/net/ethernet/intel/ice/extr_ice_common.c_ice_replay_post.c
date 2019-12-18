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
struct ice_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ice_rm_all_sw_replay_rule_info (struct ice_hw*) ; 

void ice_replay_post(struct ice_hw *hw)
{
	/* Delete old entries from replay filter list head */
	ice_rm_all_sw_replay_rule_info(hw);
}