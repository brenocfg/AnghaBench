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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  swreg ;
struct nfp_prog {int error; } ;
struct nfp_insn_re_regs {int /*<<< orphan*/  src_lmextn; int /*<<< orphan*/  dst_lmextn; int /*<<< orphan*/  wr_both; int /*<<< orphan*/  swap; int /*<<< orphan*/  i8; int /*<<< orphan*/  breg; int /*<<< orphan*/  areg; int /*<<< orphan*/  dst_ab; int /*<<< orphan*/  dst; } ;
typedef  enum shf_sc { ____Placeholder_shf_sc } shf_sc ;
typedef  enum shf_op { ____Placeholder_shf_op } shf_op ;

/* Variables and functions */
 int /*<<< orphan*/  __emit_shf (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int swreg_to_restricted (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfp_insn_re_regs*,int) ; 

__attribute__((used)) static void
emit_shf(struct nfp_prog *nfp_prog, swreg dst,
	 swreg lreg, enum shf_op op, swreg rreg, enum shf_sc sc, u8 shift)
{
	struct nfp_insn_re_regs reg;
	int err;

	err = swreg_to_restricted(dst, lreg, rreg, &reg, true);
	if (err) {
		nfp_prog->error = err;
		return;
	}

	__emit_shf(nfp_prog, reg.dst, reg.dst_ab, sc, shift,
		   reg.areg, op, reg.breg, reg.i8, reg.swap, reg.wr_both,
		   reg.dst_lmextn, reg.src_lmextn);
}