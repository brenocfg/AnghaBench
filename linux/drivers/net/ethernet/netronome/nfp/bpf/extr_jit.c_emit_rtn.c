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
struct nfp_insn_ur_regs {int /*<<< orphan*/  src_lmextn; int /*<<< orphan*/  dst_lmextn; int /*<<< orphan*/  breg; int /*<<< orphan*/  areg; } ;

/* Variables and functions */
 int /*<<< orphan*/  __emit_br_alu (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_imm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_none () ; 
 int swreg_to_unrestricted (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nfp_insn_ur_regs*) ; 

__attribute__((used)) static void emit_rtn(struct nfp_prog *nfp_prog, swreg base, u8 defer)
{
	struct nfp_insn_ur_regs reg;
	int err;

	err = swreg_to_unrestricted(reg_none(), base, reg_imm(0), &reg);
	if (err) {
		nfp_prog->error = err;
		return;
	}

	__emit_br_alu(nfp_prog, reg.areg, reg.breg, 0, defer, reg.dst_lmextn,
		      reg.src_lmextn);
}