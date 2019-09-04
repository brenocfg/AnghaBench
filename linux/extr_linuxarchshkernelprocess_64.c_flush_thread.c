#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct TYPE_3__ {struct pt_regs* kregs; struct pt_regs* uregs; } ;
struct TYPE_4__ {TYPE_1__ thread; } ;

/* Variables and functions */
 scalar_t__ THREAD_SIZE ; 
 TYPE_2__* current ; 
 struct pt_regs fake_swapper_regs ; 

void flush_thread(void)
{

	/* Called by fs/exec.c (setup_new_exec) to remove traces of a
	 * previously running executable. */
#ifdef CONFIG_SH_FPU
	if (last_task_used_math == current) {
		last_task_used_math = NULL;
	}
	/* Force FPU state to be reinitialised after exec */
	clear_used_math();
#endif

	/* if we are a kernel thread, about to change to user thread,
         * update kreg
         */
	if(current->thread.kregs==&fake_swapper_regs) {
          current->thread.kregs =
             ((struct pt_regs *)(THREAD_SIZE + (unsigned long) current) - 1);
	  current->thread.uregs = current->thread.kregs;
	}
}