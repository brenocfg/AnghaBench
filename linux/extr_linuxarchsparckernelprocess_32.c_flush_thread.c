#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct TYPE_8__ {scalar_t__ w_saved; } ;
struct TYPE_6__ {int flags; struct pt_regs* kregs; int /*<<< orphan*/  fpqdepth; int /*<<< orphan*/ * fpqueue; int /*<<< orphan*/  fsr; int /*<<< orphan*/ * float_regs; } ;
struct TYPE_7__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int PSR_EF ; 
 int SPARC_FLAG_KTHREAD ; 
 scalar_t__ THREAD_SIZE ; 
 scalar_t__ TRACEREG_SZ ; 
 TYPE_2__* current ; 
 TYPE_4__* current_thread_info () ; 
 int /*<<< orphan*/  fpsave (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int get_psr () ; 
 TYPE_2__* last_task_used_math ; 
 int /*<<< orphan*/  put_psr (int) ; 
 scalar_t__ task_stack_page (TYPE_2__*) ; 

void flush_thread(void)
{
	current_thread_info()->w_saved = 0;

#ifndef CONFIG_SMP
	if(last_task_used_math == current) {
#else
	if (test_thread_flag(TIF_USEDFPU)) {
#endif
		/* Clean the fpu. */
		put_psr(get_psr() | PSR_EF);
		fpsave(&current->thread.float_regs[0], &current->thread.fsr,
		       &current->thread.fpqueue[0], &current->thread.fpqdepth);
#ifndef CONFIG_SMP
		last_task_used_math = NULL;
#else
		clear_thread_flag(TIF_USEDFPU);
#endif
	}

	/* This task is no longer a kernel thread. */
	if (current->thread.flags & SPARC_FLAG_KTHREAD) {
		current->thread.flags &= ~SPARC_FLAG_KTHREAD;

		/* We must fixup kregs as well. */
		/* XXX This was not fixed for ti for a while, worked. Unused? */
		current->thread.kregs = (struct pt_regs *)
		    (task_stack_page(current) + (THREAD_SIZE - TRACEREG_SZ));
	}
}