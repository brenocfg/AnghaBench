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
typedef  scalar_t__ u8 ;
struct bpf_insn {scalar_t__ src_reg; scalar_t__ dst_reg; scalar_t__ off; } ;
struct nfp_insn_meta {int flags; struct bpf_insn insn; } ;
typedef  scalar_t__ s16 ;

/* Variables and functions */
 scalar_t__ BPF_LDST_BYTES (struct bpf_insn*) ; 
 int FLAG_INSN_IS_JUMP_DST ; 

__attribute__((used)) static bool
curr_pair_chain_with_previous(struct nfp_insn_meta *ld_meta,
			      struct nfp_insn_meta *st_meta,
			      struct bpf_insn *prev_ld,
			      struct bpf_insn *prev_st)
{
	u8 prev_size, curr_size, prev_ld_base, prev_st_base, prev_ld_dst;
	struct bpf_insn *ld = &ld_meta->insn;
	struct bpf_insn *st = &st_meta->insn;
	s16 prev_ld_off, prev_st_off;

	/* This pair is the start pair. */
	if (!prev_ld)
		return true;

	prev_size = BPF_LDST_BYTES(prev_ld);
	curr_size = BPF_LDST_BYTES(ld);
	prev_ld_base = prev_ld->src_reg;
	prev_st_base = prev_st->dst_reg;
	prev_ld_dst = prev_ld->dst_reg;
	prev_ld_off = prev_ld->off;
	prev_st_off = prev_st->off;

	if (ld->dst_reg != prev_ld_dst)
		return false;

	if (ld->src_reg != prev_ld_base || st->dst_reg != prev_st_base)
		return false;

	if (curr_size != prev_size)
		return false;

	/* There is jump to the head of this pair. */
	if (ld_meta->flags & FLAG_INSN_IS_JUMP_DST)
		return false;

	/* Both in ascending order. */
	if (prev_ld_off + prev_size == ld->off &&
	    prev_st_off + prev_size == st->off)
		return true;

	/* Both in descending order. */
	if (ld->off + curr_size == prev_ld_off &&
	    st->off + curr_size == prev_st_off)
		return true;

	return false;
}