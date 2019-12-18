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
struct flow_action_entry {scalar_t__ id; } ;
struct flow_action {int num_entries; struct flow_action_entry* entries; } ;

/* Variables and functions */
 scalar_t__ FLOW_ACTION_MANGLE ; 

__attribute__((used)) static bool nfp_fl_check_mangle_end(struct flow_action *flow_act,
				    int current_act_idx)
{
	struct flow_action_entry current_act;
	struct flow_action_entry next_act;

	current_act = flow_act->entries[current_act_idx];
	if (current_act.id != FLOW_ACTION_MANGLE)
		return false;

	if (current_act_idx == flow_act->num_entries)
		return true;

	next_act = flow_act->entries[current_act_idx + 1];

	return next_act.id != FLOW_ACTION_MANGLE;
}