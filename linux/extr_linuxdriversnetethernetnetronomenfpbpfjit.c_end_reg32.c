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
struct nfp_prog {int dummy; } ;
struct bpf_insn {int dst_reg; int imm; } ;
struct nfp_insn_meta {struct bpf_insn insn; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHF_SC_R_ROT ; 
 int /*<<< orphan*/  SHF_SC_R_SHF ; 
 int /*<<< orphan*/  emit_ld_field (struct nfp_prog*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  imm_a (struct nfp_prog*) ; 
 int /*<<< orphan*/  reg_a (int) ; 
 int /*<<< orphan*/  reg_b (int) ; 
 int /*<<< orphan*/  reg_both (int) ; 
 int /*<<< orphan*/  wrp_end32 (struct nfp_prog*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wrp_immed (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrp_mov (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int end_reg32(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta)
{
	const struct bpf_insn *insn = &meta->insn;
	u8 gpr = insn->dst_reg * 2;

	switch (insn->imm) {
	case 16:
		emit_ld_field(nfp_prog, reg_both(gpr), 0x9, reg_b(gpr),
			      SHF_SC_R_ROT, 8);
		emit_ld_field(nfp_prog, reg_both(gpr), 0xe, reg_a(gpr),
			      SHF_SC_R_SHF, 16);

		wrp_immed(nfp_prog, reg_both(gpr + 1), 0);
		break;
	case 32:
		wrp_end32(nfp_prog, reg_a(gpr), gpr);
		wrp_immed(nfp_prog, reg_both(gpr + 1), 0);
		break;
	case 64:
		wrp_mov(nfp_prog, imm_a(nfp_prog), reg_b(gpr + 1));

		wrp_end32(nfp_prog, reg_a(gpr), gpr + 1);
		wrp_end32(nfp_prog, imm_a(nfp_prog), gpr);
		break;
	}

	return 0;
}