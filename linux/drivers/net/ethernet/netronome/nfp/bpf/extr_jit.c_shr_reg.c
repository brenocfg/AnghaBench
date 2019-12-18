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
typedef  int u8 ;
typedef  scalar_t__ u64 ;
struct nfp_prog {int dummy; } ;
struct bpf_insn {int dst_reg; int src_reg; } ;
struct nfp_insn_meta {scalar_t__ umin_src; scalar_t__ umax_src; struct bpf_insn insn; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALU_OP_OR ; 
 int /*<<< orphan*/  SHF_OP_NONE ; 
 int /*<<< orphan*/  SHF_SC_R_SHF ; 
 int __shr_imm (struct nfp_prog*,struct nfp_insn_meta*,int,scalar_t__) ; 
 int /*<<< orphan*/  emit_alu (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_shf_indir (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_a (int) ; 
 int /*<<< orphan*/  reg_b (int) ; 
 int /*<<< orphan*/  reg_both (int) ; 
 int /*<<< orphan*/  reg_imm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_none () ; 
 int /*<<< orphan*/  wrp_zext (struct nfp_prog*,struct nfp_insn_meta*,int) ; 

__attribute__((used)) static int shr_reg(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta)
{
	const struct bpf_insn *insn = &meta->insn;
	u64 umin, umax;
	u8 dst, src;

	dst = insn->dst_reg * 2;
	umin = meta->umin_src;
	umax = meta->umax_src;
	if (umin == umax)
		return __shr_imm(nfp_prog, meta, dst, umin);

	src = insn->src_reg * 2;
	emit_alu(nfp_prog, reg_none(), reg_a(src), ALU_OP_OR, reg_imm(0));
	emit_shf_indir(nfp_prog, reg_both(dst), reg_none(), SHF_OP_NONE,
		       reg_b(dst), SHF_SC_R_SHF);
	wrp_zext(nfp_prog, meta, dst);
	return 0;
}