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
struct nfp_fl_set_mpls {void* lse_mask; void* lse; TYPE_1__ head; } ;
struct TYPE_4__ {int label; int tc; int bos; int ttl; } ;
struct flow_action_entry {TYPE_2__ mpls_mangle; } ;

/* Variables and functions */
 int ACT_MPLS_BOS_NOT_SET ; 
 int ACT_MPLS_LABEL_NOT_SET ; 
 int ACT_MPLS_TC_NOT_SET ; 
 int MPLS_LS_LABEL_MASK ; 
 int MPLS_LS_LABEL_SHIFT ; 
 int MPLS_LS_S_MASK ; 
 int MPLS_LS_S_SHIFT ; 
 int MPLS_LS_TC_MASK ; 
 int MPLS_LS_TC_SHIFT ; 
 int MPLS_LS_TTL_MASK ; 
 int MPLS_LS_TTL_SHIFT ; 
 int /*<<< orphan*/  NFP_FL_ACTION_OPCODE_SET_MPLS ; 
 size_t NFP_FL_LW_SIZ ; 
 void* cpu_to_be32 (int) ; 

__attribute__((used)) static void
nfp_fl_set_mpls(struct nfp_fl_set_mpls *set_mpls,
		const struct flow_action_entry *act)
{
	size_t act_size = sizeof(struct nfp_fl_set_mpls);
	u32 mpls_lse = 0, mpls_mask = 0;

	set_mpls->head.jump_id = NFP_FL_ACTION_OPCODE_SET_MPLS;
	set_mpls->head.len_lw = act_size >> NFP_FL_LW_SIZ;

	if (act->mpls_mangle.label != ACT_MPLS_LABEL_NOT_SET) {
		mpls_lse |= act->mpls_mangle.label << MPLS_LS_LABEL_SHIFT;
		mpls_mask |= MPLS_LS_LABEL_MASK;
	}
	if (act->mpls_mangle.tc != ACT_MPLS_TC_NOT_SET) {
		mpls_lse |= act->mpls_mangle.tc << MPLS_LS_TC_SHIFT;
		mpls_mask |= MPLS_LS_TC_MASK;
	}
	if (act->mpls_mangle.bos != ACT_MPLS_BOS_NOT_SET) {
		mpls_lse |= act->mpls_mangle.bos << MPLS_LS_S_SHIFT;
		mpls_mask |= MPLS_LS_S_MASK;
	}
	if (act->mpls_mangle.ttl) {
		mpls_lse |= act->mpls_mangle.ttl << MPLS_LS_TTL_SHIFT;
		mpls_mask |= MPLS_LS_TTL_MASK;
	}

	set_mpls->lse = cpu_to_be32(mpls_lse);
	set_mpls->lse_mask = cpu_to_be32(mpls_mask);
}