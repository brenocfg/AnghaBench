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

/* Variables and functions */
 int /*<<< orphan*/  STACK_FRAME_OVERHEAD ; 
 int /*<<< orphan*/  STACK_LR (unsigned long*) ; 
 unsigned long STACK_SP (unsigned long*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  oprofile_add_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_sp (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long kernel_getsp(unsigned long sp, int is_first)
{
	unsigned long *stack_frame = (unsigned long *)sp;

	if (!validate_sp(sp, current, STACK_FRAME_OVERHEAD))
		return 0;

	if (!is_first)
		oprofile_add_trace(STACK_LR(stack_frame));

	/*
	 * We do not enforce increasing stack addresses here because
	 * we might be transitioning from an interrupt stack to a kernel
	 * stack. validate_sp() is designed to understand this, so just
	 * use it.
	 */
	return STACK_SP(stack_frame);
}