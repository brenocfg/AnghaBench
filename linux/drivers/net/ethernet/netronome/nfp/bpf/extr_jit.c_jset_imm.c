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
struct nfp_insn_meta {struct bpf_insn insn; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALU_OP_AND ; 
 int /*<<< orphan*/  ALU_OP_OR ; 
 int /*<<< orphan*/  BR_BNE ; 
 int /*<<< orphan*/  emit_alu (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_br (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imm_b (struct nfp_prog*) ; 
 scalar_t__ is_mbpf_jmp64 (struct nfp_insn_meta*) ; 
 int /*<<< orphan*/  reg_a (int) ; 
 int /*<<< orphan*/  reg_none () ; 
 int /*<<< orphan*/  ur_load_imm_any (struct nfp_prog*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jset_imm(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta)
{
	const struct bpf_insn *insn = &meta->insn;
	u64 imm = insn->imm; /* sign extend */
	u8 dst_gpr = insn->dst_reg * 2;
	swreg tmp_reg;

	tmp_reg = ur_load_imm_any(nfp_prog, imm & ~0U, imm_b(nfp_prog));
	emit_alu(nfp_prog, imm_b(nfp_prog),
		 reg_a(dst_gpr), ALU_OP_AND, tmp_reg);
	/* Upper word of the mask can only be 0 or ~0 from sign extension,
	 * so either ignore it or OR the whole thing in.
	 */
	if (is_mbpf_jmp64(meta) && imm >> 32) {
		emit_alu(nfp_prog, reg_none(),
			 reg_a(dst_gpr + 1), ALU_OP_OR, imm_b(nfp_prog));
	}
	emit_br(nfp_prog, BR_BNE, insn->off, 0);

	return 0;
}