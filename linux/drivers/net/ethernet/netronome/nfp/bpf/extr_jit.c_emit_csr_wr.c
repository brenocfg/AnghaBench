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
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  swreg ;
struct nfp_prog {int error; } ;
struct nfp_insn_ur_regs {int /*<<< orphan*/  src_lmextn; int /*<<< orphan*/  breg; int /*<<< orphan*/  areg; } ;

/* Variables and functions */
 scalar_t__ NN_REG_IMM ; 
 int /*<<< orphan*/  __emit_lcsr (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_imm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_none () ; 
 int swreg_to_unrestricted (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfp_insn_ur_regs*) ; 
 scalar_t__ swreg_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void emit_csr_wr(struct nfp_prog *nfp_prog, swreg src, u16 addr)
{
	struct nfp_insn_ur_regs reg;
	int err;

	/* This instruction takes immeds instead of reg_none() for the ignored
	 * operand, but we can't encode 2 immeds in one instr with our normal
	 * swreg infra so if param is an immed, we encode as reg_none() and
	 * copy the immed to both operands.
	 */
	if (swreg_type(src) == NN_REG_IMM) {
		err = swreg_to_unrestricted(reg_none(), src, reg_none(), &reg);
		reg.breg = reg.areg;
	} else {
		err = swreg_to_unrestricted(reg_none(), src, reg_imm(0), &reg);
	}
	if (err) {
		nfp_prog->error = err;
		return;
	}

	__emit_lcsr(nfp_prog, reg.areg, reg.breg, true, addr,
		    false, reg.src_lmextn);
}