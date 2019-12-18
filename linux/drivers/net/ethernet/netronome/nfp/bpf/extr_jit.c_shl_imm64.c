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

/* Variables and functions */
 int __shl_imm64 (struct nfp_prog*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int shl_imm64(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta)
{
	const struct bpf_insn *insn = &meta->insn;
	u8 dst = insn->dst_reg * 2;

	return __shl_imm64(nfp_prog, dst, insn->imm);
}