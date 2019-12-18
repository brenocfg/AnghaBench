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
typedef  int /*<<< orphan*/  u64 ;
struct rvu {int dummy; } ;
struct npc_kpu_profile_action {int /*<<< orphan*/  shift; int /*<<< orphan*/  right; int /*<<< orphan*/  mask; int /*<<< orphan*/  offset; int /*<<< orphan*/  ptr_advance; int /*<<< orphan*/  flags; int /*<<< orphan*/  ltype; int /*<<< orphan*/  lid; int /*<<< orphan*/  next_state; int /*<<< orphan*/  parse_done; int /*<<< orphan*/  cap_ena; int /*<<< orphan*/  bypass_count; int /*<<< orphan*/  dp2_offset; int /*<<< orphan*/  dp1_offset; int /*<<< orphan*/  dp0_offset; int /*<<< orphan*/  errcode; int /*<<< orphan*/  errlev; } ;
struct npc_kpu_action1 {int /*<<< orphan*/  dp2_offset; int /*<<< orphan*/  dp1_offset; int /*<<< orphan*/  dp0_offset; int /*<<< orphan*/  errcode; int /*<<< orphan*/  errlev; int /*<<< orphan*/  member_0; } ;
struct npc_kpu_action0 {int /*<<< orphan*/  var_len_shift; int /*<<< orphan*/  var_len_right; int /*<<< orphan*/  var_len_mask; int /*<<< orphan*/  var_len_offset; int /*<<< orphan*/  ptr_advance; int /*<<< orphan*/  capture_flags; int /*<<< orphan*/  capture_ltype; int /*<<< orphan*/  capture_lid; int /*<<< orphan*/  next_state; int /*<<< orphan*/  parse_done; int /*<<< orphan*/  capture_ena; int /*<<< orphan*/  byp_count; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  NPC_AF_KPUX_ENTRYX_ACTION0 (int,int) ; 
 int /*<<< orphan*/  NPC_AF_KPUX_ENTRYX_ACTION1 (int,int) ; 
 int /*<<< orphan*/  NPC_AF_PKINDX_ACTION0 (int) ; 
 int /*<<< orphan*/  NPC_AF_PKINDX_ACTION1 (int) ; 
 int /*<<< orphan*/  rvu_write64 (struct rvu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void npc_config_kpuaction(struct rvu *rvu, int blkaddr,
				 struct npc_kpu_profile_action *kpuaction,
				 int kpu, int entry, bool pkind)
{
	struct npc_kpu_action0 action0 = {0};
	struct npc_kpu_action1 action1 = {0};
	u64 reg;

	action1.errlev = kpuaction->errlev;
	action1.errcode = kpuaction->errcode;
	action1.dp0_offset = kpuaction->dp0_offset;
	action1.dp1_offset = kpuaction->dp1_offset;
	action1.dp2_offset = kpuaction->dp2_offset;

	if (pkind)
		reg = NPC_AF_PKINDX_ACTION1(entry);
	else
		reg = NPC_AF_KPUX_ENTRYX_ACTION1(kpu, entry);

	rvu_write64(rvu, blkaddr, reg, *(u64 *)&action1);

	action0.byp_count = kpuaction->bypass_count;
	action0.capture_ena = kpuaction->cap_ena;
	action0.parse_done = kpuaction->parse_done;
	action0.next_state = kpuaction->next_state;
	action0.capture_lid = kpuaction->lid;
	action0.capture_ltype = kpuaction->ltype;
	action0.capture_flags = kpuaction->flags;
	action0.ptr_advance = kpuaction->ptr_advance;
	action0.var_len_offset = kpuaction->offset;
	action0.var_len_mask = kpuaction->mask;
	action0.var_len_right = kpuaction->right;
	action0.var_len_shift = kpuaction->shift;

	if (pkind)
		reg = NPC_AF_PKINDX_ACTION0(entry);
	else
		reg = NPC_AF_KPUX_ENTRYX_ACTION0(kpu, entry);

	rvu_write64(rvu, blkaddr, reg, *(u64 *)&action0);
}