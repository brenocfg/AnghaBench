#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {size_t len_lw; int /*<<< orphan*/  jump_id; } ;
struct nfp_fl_push_mpls {int /*<<< orphan*/  lse; int /*<<< orphan*/  ethtype; TYPE_1__ head; } ;
struct netlink_ext_ack {int dummy; } ;
struct TYPE_4__ {int bos; int tc; int label; int ttl; int /*<<< orphan*/  proto; } ;
struct flow_action_entry {TYPE_2__ mpls_push; } ;

/* Variables and functions */
 int ACT_MPLS_BOS_NOT_SET ; 
 int ACT_MPLS_TC_NOT_SET ; 
 int EOPNOTSUPP ; 
 int MPLS_LS_LABEL_SHIFT ; 
 int MPLS_LS_S_SHIFT ; 
 int MPLS_LS_TC_SHIFT ; 
 int MPLS_LS_TTL_SHIFT ; 
 int /*<<< orphan*/  NFP_FL_ACTION_OPCODE_PUSH_MPLS ; 
 size_t NFP_FL_LW_SIZ ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 

__attribute__((used)) static int
nfp_fl_push_mpls(struct nfp_fl_push_mpls *push_mpls,
		 const struct flow_action_entry *act,
		 struct netlink_ext_ack *extack)
{
	size_t act_size = sizeof(struct nfp_fl_push_mpls);
	u32 mpls_lse = 0;

	push_mpls->head.jump_id = NFP_FL_ACTION_OPCODE_PUSH_MPLS;
	push_mpls->head.len_lw = act_size >> NFP_FL_LW_SIZ;

	/* BOS is optional in the TC action but required for offload. */
	if (act->mpls_push.bos != ACT_MPLS_BOS_NOT_SET) {
		mpls_lse |= act->mpls_push.bos << MPLS_LS_S_SHIFT;
	} else {
		NL_SET_ERR_MSG_MOD(extack, "unsupported offload: BOS field must explicitly be set for MPLS push");
		return -EOPNOTSUPP;
	}

	/* Leave MPLS TC as a default value of 0 if not explicitly set. */
	if (act->mpls_push.tc != ACT_MPLS_TC_NOT_SET)
		mpls_lse |= act->mpls_push.tc << MPLS_LS_TC_SHIFT;

	/* Proto, label and TTL are enforced and verified for MPLS push. */
	mpls_lse |= act->mpls_push.label << MPLS_LS_LABEL_SHIFT;
	mpls_lse |= act->mpls_push.ttl << MPLS_LS_TTL_SHIFT;
	push_mpls->ethtype = act->mpls_push.proto;
	push_mpls->lse = cpu_to_be32(mpls_lse);

	return 0;
}