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
typedef  int u16 ;
typedef  int /*<<< orphan*/  swreg ;
struct nfp_prog {int error; } ;
struct nfp_insn_ur_regs {int /*<<< orphan*/  src_lmextn; int /*<<< orphan*/  dst_lmextn; int /*<<< orphan*/  wr_both; int /*<<< orphan*/  breg; int /*<<< orphan*/  areg; int /*<<< orphan*/  dst; } ;
typedef  enum immed_width { ____Placeholder_immed_width } immed_width ;
typedef  enum immed_shift { ____Placeholder_immed_shift } immed_shift ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ NN_REG_IMM ; 
 scalar_t__ NN_REG_NONE ; 
 int /*<<< orphan*/  __emit_immed (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_imm (int) ; 
 int swreg_to_unrestricted (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfp_insn_ur_regs*) ; 
 scalar_t__ swreg_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
emit_immed(struct nfp_prog *nfp_prog, swreg dst, u16 imm,
	   enum immed_width width, bool invert, enum immed_shift shift)
{
	struct nfp_insn_ur_regs reg;
	int err;

	if (swreg_type(dst) == NN_REG_IMM) {
		nfp_prog->error = -EFAULT;
		return;
	}

	err = swreg_to_unrestricted(dst, dst, reg_imm(imm & 0xff), &reg);
	if (err) {
		nfp_prog->error = err;
		return;
	}

	/* Use reg.dst when destination is No-Dest. */
	__emit_immed(nfp_prog,
		     swreg_type(dst) == NN_REG_NONE ? reg.dst : reg.areg,
		     reg.breg, imm >> 8, width, invert, shift,
		     reg.wr_both, reg.dst_lmextn, reg.src_lmextn);
}