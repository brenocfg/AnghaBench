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
struct nfp_prog {TYPE_1__* subprog; } ;
struct nfp_insn_meta {size_t subprog_idx; } ;
struct TYPE_2__ {scalar_t__ needs_reg_push; } ;

/* Variables and functions */
 int /*<<< orphan*/  BR_OFF_RELO ; 
 int /*<<< orphan*/  BR_UNC ; 
 int /*<<< orphan*/  RELO_BR_GO_CALL_POP_REGS ; 
 int /*<<< orphan*/  emit_br_relo (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_rtn (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_lm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ret_reg (struct nfp_prog*) ; 
 int /*<<< orphan*/  wrp_mov (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfp_subprog_epilogue(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta)
{
	if (nfp_prog->subprog[meta->subprog_idx].needs_reg_push) {
		/* Pop R6~R9 to the stack via related subroutine.
		 * We loaded the return address to the caller into ret_reg().
		 * This means that the subroutine does not come back here, we
		 * make it jump back to the subprogram caller directly!
		 */
		emit_br_relo(nfp_prog, BR_UNC, BR_OFF_RELO, 1,
			     RELO_BR_GO_CALL_POP_REGS);
		/* Pop return address from the stack. */
		wrp_mov(nfp_prog, ret_reg(nfp_prog), reg_lm(0, 0));
	} else {
		/* Pop return address from the stack. */
		wrp_mov(nfp_prog, ret_reg(nfp_prog), reg_lm(0, 0));
		/* Jump back to caller if no callee-saved registers were used
		 * by the subprogram.
		 */
		emit_rtn(nfp_prog, ret_reg(nfp_prog), 0);
	}

	return 0;
}