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
struct TYPE_2__ {int /*<<< orphan*/  proto; int /*<<< orphan*/  vid; } ;
struct flow_action_entry {int id; TYPE_1__ vlan; } ;
struct bnxt_tc_actions {int /*<<< orphan*/  push_vlan_tpid; int /*<<< orphan*/  push_vlan_tci; int /*<<< orphan*/  flags; } ;
struct bnxt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_TC_ACTION_FLAG_POP_VLAN ; 
 int /*<<< orphan*/  BNXT_TC_ACTION_FLAG_PUSH_VLAN ; 
 int EOPNOTSUPP ; 
#define  FLOW_ACTION_VLAN_POP 129 
#define  FLOW_ACTION_VLAN_PUSH 128 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_tc_parse_vlan(struct bnxt *bp,
			      struct bnxt_tc_actions *actions,
			      const struct flow_action_entry *act)
{
	switch (act->id) {
	case FLOW_ACTION_VLAN_POP:
		actions->flags |= BNXT_TC_ACTION_FLAG_POP_VLAN;
		break;
	case FLOW_ACTION_VLAN_PUSH:
		actions->flags |= BNXT_TC_ACTION_FLAG_PUSH_VLAN;
		actions->push_vlan_tci = htons(act->vlan.vid);
		actions->push_vlan_tpid = act->vlan.proto;
		break;
	default:
		return -EOPNOTSUPP;
	}
	return 0;
}