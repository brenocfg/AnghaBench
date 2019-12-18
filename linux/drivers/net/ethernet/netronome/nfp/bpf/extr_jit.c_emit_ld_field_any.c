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
struct nfp_insn_re_regs {int /*<<< orphan*/  src_lmextn; int /*<<< orphan*/  dst_lmextn; int /*<<< orphan*/  wr_both; int /*<<< orphan*/  swap; int /*<<< orphan*/  i8; int /*<<< orphan*/  breg; int /*<<< orphan*/  areg; } ;
typedef  enum shf_sc { ____Placeholder_shf_sc } shf_sc ;

/* Variables and functions */
 int /*<<< orphan*/  __emit_ld_field (struct nfp_prog*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int swreg_to_restricted (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfp_insn_re_regs*,int) ; 

__attribute__((used)) static void
emit_ld_field_any(struct nfp_prog *nfp_prog, swreg dst, u8 bmask, swreg src,
		  enum shf_sc sc, u8 shift, bool zero)
{
	struct nfp_insn_re_regs reg;
	int err;

	/* Note: ld_field is special as it uses one of the src regs as dst */
	err = swreg_to_restricted(dst, dst, src, &reg, true);
	if (err) {
		nfp_prog->error = err;
		return;
	}

	__emit_ld_field(nfp_prog, sc, reg.areg, bmask, reg.breg, shift,
			reg.i8, zero, reg.swap, reg.wr_both,
			reg.dst_lmextn, reg.src_lmextn);
}