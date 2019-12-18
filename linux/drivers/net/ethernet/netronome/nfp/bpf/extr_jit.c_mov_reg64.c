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
typedef  int /*<<< orphan*/  swreg ;
struct nfp_prog {int /*<<< orphan*/  stack_frame_depth; } ;
struct bpf_insn {int dst_reg; int src_reg; } ;
struct nfp_insn_meta {struct bpf_insn insn; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALU_OP_ADD ; 
 int BPF_REG_10 ; 
 int /*<<< orphan*/  emit_alu (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_both (int) ; 
 int /*<<< orphan*/  stack_imm (struct nfp_prog*) ; 
 int /*<<< orphan*/  stack_reg (struct nfp_prog*) ; 
 int /*<<< orphan*/  ur_load_imm_any (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrp_immed (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrp_reg_mov (struct nfp_prog*,int,int) ; 

__attribute__((used)) static int mov_reg64(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta)
{
	const struct bpf_insn *insn = &meta->insn;
	u8 dst = insn->dst_reg * 2;
	u8 src = insn->src_reg * 2;

	if (insn->src_reg == BPF_REG_10) {
		swreg stack_depth_reg;

		stack_depth_reg = ur_load_imm_any(nfp_prog,
						  nfp_prog->stack_frame_depth,
						  stack_imm(nfp_prog));
		emit_alu(nfp_prog, reg_both(dst), stack_reg(nfp_prog),
			 ALU_OP_ADD, stack_depth_reg);
		wrp_immed(nfp_prog, reg_both(dst + 1), 0);
	} else {
		wrp_reg_mov(nfp_prog, dst, src);
		wrp_reg_mov(nfp_prog, dst + 1, src + 1);
	}

	return 0;
}