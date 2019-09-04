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
struct TYPE_2__ {int /*<<< orphan*/  fpqdepth; int /*<<< orphan*/ * fpqueue; int /*<<< orphan*/  fsr; int /*<<< orphan*/ * float_regs; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
 int PSR_EF ; 
 int /*<<< orphan*/  fpsave (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int get_psr () ; 
 struct task_struct* last_task_used_math ; 
 int /*<<< orphan*/  put_psr (int) ; 

void exit_thread(struct task_struct *tsk)
{
#ifndef CONFIG_SMP
	if (last_task_used_math == tsk) {
#else
	if (test_ti_thread_flag(task_thread_info(tsk), TIF_USEDFPU)) {
#endif
		/* Keep process from leaving FPU in a bogon state. */
		put_psr(get_psr() | PSR_EF);
		fpsave(&tsk->thread.float_regs[0], &tsk->thread.fsr,
		       &tsk->thread.fpqueue[0], &tsk->thread.fpqdepth);
#ifndef CONFIG_SMP
		last_task_used_math = NULL;
#else
		clear_ti_thread_flag(task_thread_info(tsk), TIF_USEDFPU);
#endif
	}
}