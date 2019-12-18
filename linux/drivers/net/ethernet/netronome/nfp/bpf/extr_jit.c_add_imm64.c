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
typedef  unsigned int u64 ;
struct nfp_prog {int dummy; } ;
struct bpf_insn {unsigned int imm; int dst_reg; } ;
struct nfp_insn_meta {struct bpf_insn insn; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALU_OP_ADD ; 
 int /*<<< orphan*/  ALU_OP_ADD_C ; 
 int /*<<< orphan*/  wrp_alu_imm (struct nfp_prog*,int,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int add_imm64(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta)
{
	const struct bpf_insn *insn = &meta->insn;
	u64 imm = insn->imm; /* sign extend */

	wrp_alu_imm(nfp_prog, insn->dst_reg * 2, ALU_OP_ADD, imm & ~0U);
	wrp_alu_imm(nfp_prog, insn->dst_reg * 2 + 1, ALU_OP_ADD_C, imm >> 32);

	return 0;
}