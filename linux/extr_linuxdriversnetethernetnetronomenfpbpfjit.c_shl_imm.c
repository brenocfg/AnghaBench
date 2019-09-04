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
struct bpf_insn {int dst_reg; int /*<<< orphan*/  imm; } ;
struct nfp_insn_meta {struct bpf_insn insn; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHF_OP_NONE ; 
 int /*<<< orphan*/  SHF_SC_L_SHF ; 
 int /*<<< orphan*/  emit_shf (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_b (int) ; 
 int /*<<< orphan*/  reg_both (int) ; 
 int /*<<< orphan*/  reg_none () ; 
 int /*<<< orphan*/  wrp_immed (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int shl_imm(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta)
{
	const struct bpf_insn *insn = &meta->insn;

	if (!insn->imm)
		return 1; /* TODO: zero shift means indirect */

	emit_shf(nfp_prog, reg_both(insn->dst_reg * 2),
		 reg_none(), SHF_OP_NONE, reg_b(insn->dst_reg * 2),
		 SHF_SC_L_SHF, insn->imm);
	wrp_immed(nfp_prog, reg_both(insn->dst_reg * 2 + 1), 0);

	return 0;
}