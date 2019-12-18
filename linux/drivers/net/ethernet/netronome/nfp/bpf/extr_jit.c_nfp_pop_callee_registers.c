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
typedef  scalar_t__ u8 ;
struct nfp_prog {int /*<<< orphan*/  tgt_call_pop_regs; } ;

/* Variables and functions */
 scalar_t__ BPF_REG_0 ; 
 scalar_t__ BPF_REG_6 ; 
 scalar_t__ BPF_REG_8 ; 
 scalar_t__ BPF_REG_9 ; 
 int /*<<< orphan*/  emit_rtn (struct nfp_prog*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfp_prog_current_offset (struct nfp_prog*) ; 
 int /*<<< orphan*/  reg_both (scalar_t__) ; 
 int /*<<< orphan*/  reg_lm (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ret_reg (struct nfp_prog*) ; 
 int /*<<< orphan*/  wrp_mov (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfp_pop_callee_registers(struct nfp_prog *nfp_prog)
{
	u8 reg;

	/* Subroutine: Restore all callee saved registers (R6 ~ R9).
	 * ret_reg() holds the return address.
	 */
	nfp_prog->tgt_call_pop_regs = nfp_prog_current_offset(nfp_prog);
	for (reg = BPF_REG_6; reg <= BPF_REG_9; reg++) {
		u8 adj = (reg - BPF_REG_0) * 2;
		u8 idx = (reg - BPF_REG_6) * 2;

		/* The first slot in the stack frame holds the return address,
		 * start popping just after that.
		 */
		wrp_mov(nfp_prog, reg_both(adj), reg_lm(0, 1 + idx));

		if (reg == BPF_REG_8)
			/* Prepare to jump back, last 3 insns use defer slots */
			emit_rtn(nfp_prog, ret_reg(nfp_prog), 3);

		wrp_mov(nfp_prog, reg_both(adj + 1), reg_lm(0, 1 + idx + 1));
	}
}