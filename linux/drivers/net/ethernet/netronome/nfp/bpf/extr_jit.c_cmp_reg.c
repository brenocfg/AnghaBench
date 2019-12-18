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
struct bpf_insn {int dst_reg; int src_reg; int /*<<< orphan*/  off; } ;
struct nfp_insn_meta {struct bpf_insn insn; } ;
struct jmp_code_map {int /*<<< orphan*/  br_mask; scalar_t__ swap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALU_OP_SUB ; 
 int /*<<< orphan*/  ALU_OP_SUB_C ; 
 int EINVAL ; 
 int /*<<< orphan*/  emit_alu (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_br (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_mbpf_jmp64 (struct nfp_insn_meta*) ; 
 struct jmp_code_map* nfp_jmp_code_get (struct nfp_insn_meta*) ; 
 int /*<<< orphan*/  reg_a (int) ; 
 int /*<<< orphan*/  reg_b (int) ; 
 int /*<<< orphan*/  reg_none () ; 

__attribute__((used)) static int cmp_reg(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta)
{
	const struct bpf_insn *insn = &meta->insn;
	const struct jmp_code_map *code;
	u8 areg, breg;

	code = nfp_jmp_code_get(meta);
	if (!code)
		return -EINVAL;

	areg = insn->dst_reg * 2;
	breg = insn->src_reg * 2;

	if (code->swap) {
		areg ^= breg;
		breg ^= areg;
		areg ^= breg;
	}

	emit_alu(nfp_prog, reg_none(), reg_a(areg), ALU_OP_SUB, reg_b(breg));
	if (is_mbpf_jmp64(meta))
		emit_alu(nfp_prog, reg_none(),
			 reg_a(areg + 1), ALU_OP_SUB_C, reg_b(breg + 1));
	emit_br(nfp_prog, code->br_mask, insn->off, 0);

	return 0;
}