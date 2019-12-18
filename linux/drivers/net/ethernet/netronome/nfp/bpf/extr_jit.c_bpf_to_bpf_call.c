#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
typedef  int /*<<< orphan*/  swreg ;
struct nfp_prog {TYPE_1__* subprog; int /*<<< orphan*/  stack_frame_depth; } ;
struct TYPE_6__ {int /*<<< orphan*/  imm; } ;
struct nfp_insn_meta {void* num_insns_after_br; TYPE_3__ insn; TYPE_2__* jmp_dst; } ;
struct TYPE_5__ {size_t subprog_idx; } ;
struct TYPE_4__ {scalar_t__ needs_reg_push; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALU_OP_ADD ; 
 int /*<<< orphan*/  ALU_OP_SUB ; 
 int /*<<< orphan*/  BR_OFF_RELO ; 
 int /*<<< orphan*/  BR_UNC ; 
 int EINVAL ; 
 int ELOOP ; 
 int /*<<< orphan*/  NFP_CSR_ACT_LM_ADDR0 ; 
 int /*<<< orphan*/  RELO_BR_GO_CALL_PUSH_REGS ; 
 int /*<<< orphan*/  RELO_IMMED_REL ; 
 int /*<<< orphan*/  STACK_FRAME_ALIGN ; 
 int /*<<< orphan*/  emit_alu (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_br (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_br_relo (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_csr_wr (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imm_b (struct nfp_prog*) ; 
 int /*<<< orphan*/  nfp_prog_confirm_current_offset (struct nfp_prog*,void*) ; 
 void* nfp_prog_current_offset (struct nfp_prog*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  ret_reg (struct nfp_prog*) ; 
 void* round_up (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_imm (struct nfp_prog*) ; 
 int /*<<< orphan*/  stack_reg (struct nfp_prog*) ; 
 int /*<<< orphan*/  ur_load_imm_any (struct nfp_prog*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrp_immed_relo (struct nfp_prog*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrp_nops (struct nfp_prog*,int) ; 

__attribute__((used)) static int
bpf_to_bpf_call(struct nfp_prog *nfp_prog, struct nfp_insn_meta *meta)
{
	u32 ret_tgt, stack_depth, offset_br;
	swreg tmp_reg;

	stack_depth = round_up(nfp_prog->stack_frame_depth, STACK_FRAME_ALIGN);
	/* Space for saving the return address is accounted for by the callee,
	 * so stack_depth can be zero for the main function.
	 */
	if (stack_depth) {
		tmp_reg = ur_load_imm_any(nfp_prog, stack_depth,
					  stack_imm(nfp_prog));
		emit_alu(nfp_prog, stack_reg(nfp_prog),
			 stack_reg(nfp_prog), ALU_OP_ADD, tmp_reg);
		emit_csr_wr(nfp_prog, stack_reg(nfp_prog),
			    NFP_CSR_ACT_LM_ADDR0);
	}

	/* Two cases for jumping to the callee:
	 *
	 * - If callee uses and needs to save R6~R9 then:
	 *     1. Put the start offset of the callee into imm_b(). This will
	 *        require a fixup step, as we do not necessarily know this
	 *        address yet.
	 *     2. Put the return address from the callee to the caller into
	 *        register ret_reg().
	 *     3. (After defer slots are consumed) Jump to the subroutine that
	 *        pushes the registers to the stack.
	 *   The subroutine acts as a trampoline, and returns to the address in
	 *   imm_b(), i.e. jumps to the callee.
	 *
	 * - If callee does not need to save R6~R9 then just load return
	 *   address to the caller in ret_reg(), and jump to the callee
	 *   directly.
	 *
	 * Using ret_reg() to pass the return address to the callee is set here
	 * as a convention. The callee can then push this address onto its
	 * stack frame in its prologue. The advantages of passing the return
	 * address through ret_reg(), instead of pushing it to the stack right
	 * here, are the following:
	 * - It looks cleaner.
	 * - If the called function is called multiple time, we get a lower
	 *   program size.
	 * - We save two no-op instructions that should be added just before
	 *   the emit_br() when stack depth is not null otherwise.
	 * - If we ever find a register to hold the return address during whole
	 *   execution of the callee, we will not have to push the return
	 *   address to the stack for leaf functions.
	 */
	if (!meta->jmp_dst) {
		pr_err("BUG: BPF-to-BPF call has no destination recorded\n");
		return -ELOOP;
	}
	if (nfp_prog->subprog[meta->jmp_dst->subprog_idx].needs_reg_push) {
		ret_tgt = nfp_prog_current_offset(nfp_prog) + 3;
		emit_br_relo(nfp_prog, BR_UNC, BR_OFF_RELO, 2,
			     RELO_BR_GO_CALL_PUSH_REGS);
		offset_br = nfp_prog_current_offset(nfp_prog);
		wrp_immed_relo(nfp_prog, imm_b(nfp_prog), 0, RELO_IMMED_REL);
	} else {
		ret_tgt = nfp_prog_current_offset(nfp_prog) + 2;
		emit_br(nfp_prog, BR_UNC, meta->insn.imm, 1);
		offset_br = nfp_prog_current_offset(nfp_prog);
	}
	wrp_immed_relo(nfp_prog, ret_reg(nfp_prog), ret_tgt, RELO_IMMED_REL);

	if (!nfp_prog_confirm_current_offset(nfp_prog, ret_tgt))
		return -EINVAL;

	if (stack_depth) {
		tmp_reg = ur_load_imm_any(nfp_prog, stack_depth,
					  stack_imm(nfp_prog));
		emit_alu(nfp_prog, stack_reg(nfp_prog),
			 stack_reg(nfp_prog), ALU_OP_SUB, tmp_reg);
		emit_csr_wr(nfp_prog, stack_reg(nfp_prog),
			    NFP_CSR_ACT_LM_ADDR0);
		wrp_nops(nfp_prog, 3);
	}

	meta->num_insns_after_br = nfp_prog_current_offset(nfp_prog);
	meta->num_insns_after_br -= offset_br;

	return 0;
}