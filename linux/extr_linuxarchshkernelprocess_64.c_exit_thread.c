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
struct task_struct {int dummy; } ;

/* Variables and functions */

void exit_thread(struct task_struct *tsk)
{
	/*
	 * See arch/sparc/kernel/process.c for the precedent for doing
	 * this -- RPC.
	 *
	 * The SH-5 FPU save/restore approach relies on
	 * last_task_used_math pointing to a live task_struct.  When
	 * another task tries to use the FPU for the 1st time, the FPUDIS
	 * trap handling (see arch/sh/kernel/cpu/sh5/fpu.c) will save the
	 * existing FPU state to the FP regs field within
	 * last_task_used_math before re-loading the new task's FPU state
	 * (or initialising it if the FPU has been used before).  So if
	 * last_task_used_math is stale, and its page has already been
	 * re-allocated for another use, the consequences are rather
	 * grim. Unless we null it here, there is no other path through
	 * which it would get safely nulled.
	 */
#ifdef CONFIG_SH_FPU
	if (last_task_used_math == tsk)
		last_task_used_math = NULL;
#endif
}