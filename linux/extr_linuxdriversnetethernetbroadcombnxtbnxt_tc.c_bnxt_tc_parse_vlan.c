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
struct tc_action {int dummy; } ;
struct bnxt_tc_actions {int /*<<< orphan*/  push_vlan_tpid; int /*<<< orphan*/  push_vlan_tci; int /*<<< orphan*/  flags; } ;
struct bnxt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_TC_ACTION_FLAG_POP_VLAN ; 
 int /*<<< orphan*/  BNXT_TC_ACTION_FLAG_PUSH_VLAN ; 
 int EOPNOTSUPP ; 
#define  TCA_VLAN_ACT_POP 129 
#define  TCA_VLAN_ACT_PUSH 128 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int tcf_vlan_action (struct tc_action const*) ; 
 int /*<<< orphan*/  tcf_vlan_push_proto (struct tc_action const*) ; 
 int /*<<< orphan*/  tcf_vlan_push_vid (struct tc_action const*) ; 

__attribute__((used)) static int bnxt_tc_parse_vlan(struct bnxt *bp,
			      struct bnxt_tc_actions *actions,
			      const struct tc_action *tc_act)
{
	switch (tcf_vlan_action(tc_act)) {
	case TCA_VLAN_ACT_POP:
		actions->flags |= BNXT_TC_ACTION_FLAG_POP_VLAN;
		break;
	case TCA_VLAN_ACT_PUSH:
		actions->flags |= BNXT_TC_ACTION_FLAG_PUSH_VLAN;
		actions->push_vlan_tci = htons(tcf_vlan_push_vid(tc_act));
		actions->push_vlan_tpid = tcf_vlan_push_proto(tc_act);
		break;
	default:
		return -EOPNOTSUPP;
	}
	return 0;
}