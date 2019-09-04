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
struct bpf_insn {int dst_reg; } ;
struct nfp_insn_meta {struct bpf_insn insn; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALU_OP_SUB ; 
 int /*<<< orphan*/  ALU_OP_SUB_C ; 
 int /*<<< orphan*/  emit_alu (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_b (int) ; 
 int /*<<< orphan*/  reg_both (int) ; 
 int /*<<< orphan*/  reg_imm (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int neg_reg64(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta)
{
	const struct bpf_insn *insn = &meta->insn;

	emit_alu(nfp_prog, reg_both(insn->dst_reg * 2), reg_imm(0),
		 ALU_OP_SUB, reg_b(insn->dst_reg * 2));
	emit_alu(nfp_prog, reg_both(insn->dst_reg * 2 + 1), reg_imm(0),
		 ALU_OP_SUB_C, reg_b(insn->dst_reg * 2 + 1));

	return 0;
}