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
typedef  scalar_t__ u64 ;
struct nfp_prog {int dummy; } ;
struct bpf_insn {int dst_reg; int src_reg; } ;
struct nfp_insn_meta {scalar_t__ umin_src; scalar_t__ umax_src; struct bpf_insn insn; } ;

/* Variables and functions */
 int __shl_imm (struct nfp_prog*,struct nfp_insn_meta*,int,scalar_t__) ; 
 int /*<<< orphan*/  shl_reg64_lt32_low (struct nfp_prog*,int,int) ; 
 int /*<<< orphan*/  wrp_zext (struct nfp_prog*,struct nfp_insn_meta*,int) ; 

__attribute__((used)) static int shl_reg(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta)
{
	const struct bpf_insn *insn = &meta->insn;
	u64 umin, umax;
	u8 dst, src;

	dst = insn->dst_reg * 2;
	umin = meta->umin_src;
	umax = meta->umax_src;
	if (umin == umax)
		return __shl_imm(nfp_prog, meta, dst, umin);

	src = insn->src_reg * 2;
	shl_reg64_lt32_low(nfp_prog, dst, src);
	wrp_zext(nfp_prog, meta, dst);
	return 0;
}