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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  swreg ;
struct nfp_prog {int dummy; } ;
typedef  enum alu_op { ____Placeholder_alu_op } alu_op ;

/* Variables and functions */
 int ALU_OP_AND ; 
 int ALU_OP_NOT ; 
 int ALU_OP_OR ; 
 int ALU_OP_XOR ; 
 int /*<<< orphan*/  emit_alu (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imm_b (struct nfp_prog*) ; 
 int /*<<< orphan*/  reg_a (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_b (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_both (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_none () ; 
 int /*<<< orphan*/  ur_load_imm_any (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrp_immed (struct nfp_prog*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void
wrp_alu_imm(struct nfp_prog *nfp_prog, u8 dst, enum alu_op alu_op, u32 imm)
{
	swreg tmp_reg;

	if (alu_op == ALU_OP_AND) {
		if (!imm)
			wrp_immed(nfp_prog, reg_both(dst), 0);
		if (!imm || !~imm)
			return;
	}
	if (alu_op == ALU_OP_OR) {
		if (!~imm)
			wrp_immed(nfp_prog, reg_both(dst), ~0U);
		if (!imm || !~imm)
			return;
	}
	if (alu_op == ALU_OP_XOR) {
		if (!~imm)
			emit_alu(nfp_prog, reg_both(dst), reg_none(),
				 ALU_OP_NOT, reg_b(dst));
		if (!imm || !~imm)
			return;
	}

	tmp_reg = ur_load_imm_any(nfp_prog, imm, imm_b(nfp_prog));
	emit_alu(nfp_prog, reg_both(dst), reg_a(dst), alu_op, tmp_reg);
}