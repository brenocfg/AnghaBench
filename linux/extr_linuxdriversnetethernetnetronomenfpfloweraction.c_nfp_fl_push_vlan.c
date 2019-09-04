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
typedef  int u16 ;
struct tc_action {int dummy; } ;
struct TYPE_2__ {size_t len_lw; int /*<<< orphan*/  jump_id; } ;
struct nfp_fl_push_vlan {int /*<<< orphan*/  vlan_tci; int /*<<< orphan*/  vlan_tpid; scalar_t__ reserved; TYPE_1__ head; } ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFP_FL_ACTION_OPCODE_PUSH_VLAN ; 
 size_t NFP_FL_LW_SIZ ; 
 int /*<<< orphan*/  NFP_FL_PUSH_VLAN_PRIO ; 
 int /*<<< orphan*/  NFP_FL_PUSH_VLAN_VID ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  tcf_vlan_push_prio (struct tc_action const*) ; 
 int /*<<< orphan*/  tcf_vlan_push_proto (struct tc_action const*) ; 
 int /*<<< orphan*/  tcf_vlan_push_vid (struct tc_action const*) ; 

__attribute__((used)) static void
nfp_fl_push_vlan(struct nfp_fl_push_vlan *push_vlan,
		 const struct tc_action *action)
{
	size_t act_size = sizeof(struct nfp_fl_push_vlan);
	u16 tmp_push_vlan_tci;

	push_vlan->head.jump_id = NFP_FL_ACTION_OPCODE_PUSH_VLAN;
	push_vlan->head.len_lw = act_size >> NFP_FL_LW_SIZ;
	push_vlan->reserved = 0;
	push_vlan->vlan_tpid = tcf_vlan_push_proto(action);

	tmp_push_vlan_tci =
		FIELD_PREP(NFP_FL_PUSH_VLAN_PRIO, tcf_vlan_push_prio(action)) |
		FIELD_PREP(NFP_FL_PUSH_VLAN_VID, tcf_vlan_push_vid(action));
	push_vlan->vlan_tci = cpu_to_be16(tmp_push_vlan_tci);
}