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
struct nfp_prog {int dummy; } ;
struct bpf_insn {int dst_reg; int src_reg; int /*<<< orphan*/  off; } ;
struct nfp_insn_meta {struct bpf_insn insn; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALU_OP_OR ; 
 int /*<<< orphan*/  ALU_OP_XOR ; 
 int /*<<< orphan*/  BR_BEQ ; 
 int /*<<< orphan*/  emit_alu (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_br (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imm_a (struct nfp_prog*) ; 
 int /*<<< orphan*/  imm_b (struct nfp_prog*) ; 
 scalar_t__ is_mbpf_jmp64 (struct nfp_insn_meta*) ; 
 int /*<<< orphan*/  reg_a (int) ; 
 int /*<<< orphan*/  reg_b (int) ; 
 int /*<<< orphan*/  reg_none () ; 

__attribute__((used)) static int jeq_reg(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta)
{
	const struct bpf_insn *insn = &meta->insn;

	emit_alu(nfp_prog, imm_a(nfp_prog), reg_a(insn->dst_reg * 2),
		 ALU_OP_XOR, reg_b(insn->src_reg * 2));
	if (is_mbpf_jmp64(meta)) {
		emit_alu(nfp_prog, imm_b(nfp_prog),
			 reg_a(insn->dst_reg * 2 + 1), ALU_OP_XOR,
			 reg_b(insn->src_reg * 2 + 1));
		emit_alu(nfp_prog, reg_none(), imm_a(nfp_prog), ALU_OP_OR,
			 imm_b(nfp_prog));
	}
	emit_br(nfp_prog, BR_BEQ, insn->off, 0);

	return 0;
}