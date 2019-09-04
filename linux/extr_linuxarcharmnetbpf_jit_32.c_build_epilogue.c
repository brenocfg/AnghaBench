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
struct jit_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_FP ; 
 int /*<<< orphan*/  ARM_MOV_R (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARM_POP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARM_SP ; 
 int /*<<< orphan*/  CALLEE_POP_MASK ; 
 int /*<<< orphan*/  emit (int /*<<< orphan*/ ,struct jit_ctx*) ; 

__attribute__((used)) static void build_epilogue(struct jit_ctx *ctx)
{
#ifdef CONFIG_FRAME_POINTER
	/* When using frame pointers, some additional registers need to
	 * be loaded. */
	u16 reg_set = CALLEE_POP_MASK | 1 << ARM_SP;
	emit(ARM_SUB_I(ARM_SP, ARM_FP, hweight16(reg_set) * 4), ctx);
	emit(ARM_LDM(ARM_SP, reg_set), ctx);
#else
	/* Restore callee saved registers. */
	emit(ARM_MOV_R(ARM_SP, ARM_FP), ctx);
	emit(ARM_POP(CALLEE_POP_MASK), ctx);
#endif
}