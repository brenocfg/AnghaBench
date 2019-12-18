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
typedef  int /*<<< orphan*/  swreg ;
struct nfp_prog {int error; } ;
struct nfp_insn_ur_regs {int /*<<< orphan*/  src_lmextn; int /*<<< orphan*/  dst_lmextn; int /*<<< orphan*/  wr_both; int /*<<< orphan*/  swap; int /*<<< orphan*/  breg; int /*<<< orphan*/  areg; int /*<<< orphan*/  dst_ab; int /*<<< orphan*/  dst; } ;
typedef  enum alu_op { ____Placeholder_alu_op } alu_op ;

/* Variables and functions */
 int /*<<< orphan*/  __emit_alu (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int swreg_to_unrestricted (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfp_insn_ur_regs*) ; 

__attribute__((used)) static void
emit_alu(struct nfp_prog *nfp_prog, swreg dst,
	 swreg lreg, enum alu_op op, swreg rreg)
{
	struct nfp_insn_ur_regs reg;
	int err;

	err = swreg_to_unrestricted(dst, lreg, rreg, &reg);
	if (err) {
		nfp_prog->error = err;
		return;
	}

	__emit_alu(nfp_prog, reg.dst, reg.dst_ab,
		   reg.areg, op, reg.breg, reg.swap, reg.wr_both,
		   reg.dst_lmextn, reg.src_lmextn);
}