#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct nfp_prog {int dummy; } ;
struct TYPE_2__ {int dst_reg; int src_reg; } ;
struct nfp_insn_meta {TYPE_1__ insn; } ;
typedef  enum alu_op { ____Placeholder_alu_op } alu_op ;

/* Variables and functions */
 int /*<<< orphan*/  emit_alu (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_a (int) ; 
 int /*<<< orphan*/  reg_b (int) ; 
 int /*<<< orphan*/  reg_both (int) ; 

__attribute__((used)) static int
wrp_alu64_reg(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta,
	      enum alu_op alu_op)
{
	u8 dst = meta->insn.dst_reg * 2, src = meta->insn.src_reg * 2;

	emit_alu(nfp_prog, reg_both(dst), reg_a(dst), alu_op, reg_b(src));
	emit_alu(nfp_prog, reg_both(dst + 1),
		 reg_a(dst + 1), alu_op, reg_b(src + 1));

	return 0;
}