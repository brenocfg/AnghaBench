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
typedef  int /*<<< orphan*/  u32 ;
struct codegen_context {int seen; int /*<<< orphan*/  stack_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_PPC_STACKFRAME ; 
 int BPF_PPC_STACK_SAVE ; 
 int BPF_REG_10 ; 
 int BPF_REG_6 ; 
 size_t BPF_REG_FP ; 
 int /*<<< orphan*/  EMIT (int) ; 
 int /*<<< orphan*/  PPC_ADDI (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  PPC_BPF_STL (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  PPC_BPF_STLU (int,int,int /*<<< orphan*/ ) ; 
 int PPC_INST_MFLR ; 
 int /*<<< orphan*/  PPC_LI (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PPC_LR_STKOFF ; 
 int /*<<< orphan*/  PPC_NOP () ; 
 int /*<<< orphan*/  R0 ; 
 int SEEN_FUNC ; 
 int SEEN_TAILCALL ; 
 scalar_t__ STACK_FRAME_MIN_SIZE ; 
 size_t TMP_REG_1 ; 
 int __PPC_RT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * b2p ; 
 scalar_t__ bpf_has_stack_frame (struct codegen_context*) ; 
 scalar_t__ bpf_is_seen_register (struct codegen_context*,size_t) ; 
 int bpf_jit_stack_offsetof (struct codegen_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bpf_jit_build_prologue(u32 *image, struct codegen_context *ctx)
{
	int i;

	/*
	 * Initialize tail_call_cnt if we do tail calls.
	 * Otherwise, put in NOPs so that it can be skipped when we are
	 * invoked through a tail call.
	 */
	if (ctx->seen & SEEN_TAILCALL) {
		PPC_LI(b2p[TMP_REG_1], 0);
		/* this goes in the redzone */
		PPC_BPF_STL(b2p[TMP_REG_1], 1, -(BPF_PPC_STACK_SAVE + 8));
	} else {
		PPC_NOP();
		PPC_NOP();
	}

#define BPF_TAILCALL_PROLOGUE_SIZE	8

	if (bpf_has_stack_frame(ctx)) {
		/*
		 * We need a stack frame, but we don't necessarily need to
		 * save/restore LR unless we call other functions
		 */
		if (ctx->seen & SEEN_FUNC) {
			EMIT(PPC_INST_MFLR | __PPC_RT(R0));
			PPC_BPF_STL(0, 1, PPC_LR_STKOFF);
		}

		PPC_BPF_STLU(1, 1, -(BPF_PPC_STACKFRAME + ctx->stack_size));
	}

	/*
	 * Back up non-volatile regs -- BPF registers 6-10
	 * If we haven't created our own stack frame, we save these
	 * in the protected zone below the previous stack frame
	 */
	for (i = BPF_REG_6; i <= BPF_REG_10; i++)
		if (bpf_is_seen_register(ctx, i))
			PPC_BPF_STL(b2p[i], 1, bpf_jit_stack_offsetof(ctx, b2p[i]));

	/* Setup frame pointer to point to the bpf stack area */
	if (bpf_is_seen_register(ctx, BPF_REG_FP))
		PPC_ADDI(b2p[BPF_REG_FP], 1,
				STACK_FRAME_MIN_SIZE + ctx->stack_size);
}