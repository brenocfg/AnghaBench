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
struct bpf_insn {int dst_reg; int /*<<< orphan*/  imm; } ;
struct nfp_insn_meta {struct bpf_insn insn; } ;
typedef  enum alu_op { ____Placeholder_alu_op } alu_op ;

/* Variables and functions */
 int /*<<< orphan*/  wrp_alu_imm (struct nfp_prog*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrp_zext (struct nfp_prog*,struct nfp_insn_meta*,int) ; 

__attribute__((used)) static int
wrp_alu32_imm(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta,
	      enum alu_op alu_op)
{
	const struct bpf_insn *insn = &meta->insn;
	u8 dst = insn->dst_reg * 2;

	wrp_alu_imm(nfp_prog, dst, alu_op, insn->imm);
	wrp_zext(nfp_prog, meta, dst);

	return 0;
}