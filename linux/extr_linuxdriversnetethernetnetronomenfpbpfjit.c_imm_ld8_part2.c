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
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct nfp_prog {int dummy; } ;
struct TYPE_2__ {int dst_reg; scalar_t__ imm; } ;
struct nfp_insn_meta {TYPE_1__ insn; } ;

/* Variables and functions */
 struct nfp_insn_meta* nfp_meta_prev (struct nfp_insn_meta*) ; 
 int /*<<< orphan*/  reg_a (int) ; 
 int /*<<< orphan*/  reg_both (int) ; 
 int /*<<< orphan*/  wrp_immed (struct nfp_prog*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wrp_mov (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imm_ld8_part2(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta)
{
	struct nfp_insn_meta *prev = nfp_meta_prev(meta);
	u32 imm_lo, imm_hi;
	u8 dst;

	dst = prev->insn.dst_reg * 2;
	imm_lo = prev->insn.imm;
	imm_hi = meta->insn.imm;

	wrp_immed(nfp_prog, reg_both(dst), imm_lo);

	/* mov is always 1 insn, load imm may be two, so try to use mov */
	if (imm_hi == imm_lo)
		wrp_mov(nfp_prog, reg_both(dst + 1), reg_a(dst));
	else
		wrp_immed(nfp_prog, reg_both(dst + 1), imm_hi);

	return 0;
}