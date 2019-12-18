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
typedef  unsigned int u64 ;
typedef  int /*<<< orphan*/  swreg ;
struct nfp_prog {int dummy; } ;
struct bpf_insn {unsigned int imm; int dst_reg; int /*<<< orphan*/  off; } ;
struct nfp_insn_meta {scalar_t__ jump_neg_op; struct bpf_insn insn; } ;
struct jmp_code_map {int /*<<< orphan*/  br_mask; int /*<<< orphan*/  swap; } ;
typedef  enum alu_op { ____Placeholder_alu_op } alu_op ;

/* Variables and functions */
 int ALU_OP_ADD ; 
 int ALU_OP_ADD_C ; 
 int ALU_OP_SUB ; 
 int ALU_OP_SUB_C ; 
 int EINVAL ; 
 int /*<<< orphan*/  emit_alu (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_br (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imm_b (struct nfp_prog*) ; 
 scalar_t__ is_mbpf_jmp64 (struct nfp_insn_meta*) ; 
 struct jmp_code_map* nfp_jmp_code_get (struct nfp_insn_meta*) ; 
 int /*<<< orphan*/  reg_a (int) ; 
 int /*<<< orphan*/  reg_none () ; 
 int /*<<< orphan*/  ur_load_imm_any (struct nfp_prog*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmp_imm(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta)
{
	const struct bpf_insn *insn = &meta->insn;
	u64 imm = insn->imm; /* sign extend */
	const struct jmp_code_map *code;
	enum alu_op alu_op, carry_op;
	u8 reg = insn->dst_reg * 2;
	swreg tmp_reg;

	code = nfp_jmp_code_get(meta);
	if (!code)
		return -EINVAL;

	alu_op = meta->jump_neg_op ? ALU_OP_ADD : ALU_OP_SUB;
	carry_op = meta->jump_neg_op ? ALU_OP_ADD_C : ALU_OP_SUB_C;

	tmp_reg = ur_load_imm_any(nfp_prog, imm & ~0U, imm_b(nfp_prog));
	if (!code->swap)
		emit_alu(nfp_prog, reg_none(), reg_a(reg), alu_op, tmp_reg);
	else
		emit_alu(nfp_prog, reg_none(), tmp_reg, alu_op, reg_a(reg));

	if (is_mbpf_jmp64(meta)) {
		tmp_reg = ur_load_imm_any(nfp_prog, imm >> 32, imm_b(nfp_prog));
		if (!code->swap)
			emit_alu(nfp_prog, reg_none(),
				 reg_a(reg + 1), carry_op, tmp_reg);
		else
			emit_alu(nfp_prog, reg_none(),
				 tmp_reg, carry_op, reg_a(reg + 1));
	}

	emit_br(nfp_prog, code->br_mask, insn->off, 0);

	return 0;
}