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
struct pt_regs {unsigned long sp; unsigned long pc; unsigned long r4; unsigned long r5; unsigned long UCreg_sp; int /*<<< orphan*/  UCreg_03; int /*<<< orphan*/  UCreg_16; scalar_t__ UCreg_00; } ;
struct thread_info {struct pt_regs cpu_context; } ;
struct task_struct {int flags; } ;
struct cpu_context_save {int dummy; } ;

/* Variables and functions */
 unsigned long CLONE_SETTLS ; 
 int PF_KTHREAD ; 
 struct pt_regs* current_pt_regs () ; 
 int /*<<< orphan*/  memset (struct pt_regs*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ret_from_fork ; 
 scalar_t__ ret_from_kernel_thread ; 
 struct pt_regs* task_pt_regs (struct task_struct*) ; 
 struct thread_info* task_thread_info (struct task_struct*) ; 
 scalar_t__ unlikely (int) ; 

int
copy_thread(unsigned long clone_flags, unsigned long stack_start,
	    unsigned long stk_sz, struct task_struct *p)
{
	struct thread_info *thread = task_thread_info(p);
	struct pt_regs *childregs = task_pt_regs(p);

	memset(&thread->cpu_context, 0, sizeof(struct cpu_context_save));
	thread->cpu_context.sp = (unsigned long)childregs;
	if (unlikely(p->flags & PF_KTHREAD)) {
		thread->cpu_context.pc = (unsigned long)ret_from_kernel_thread;
		thread->cpu_context.r4 = stack_start;
		thread->cpu_context.r5 = stk_sz;
		memset(childregs, 0, sizeof(struct pt_regs));
	} else {
		thread->cpu_context.pc = (unsigned long)ret_from_fork;
		*childregs = *current_pt_regs();
		childregs->UCreg_00 = 0;
		if (stack_start)
			childregs->UCreg_sp = stack_start;

		if (clone_flags & CLONE_SETTLS)
			childregs->UCreg_16 = childregs->UCreg_03;
	}
	return 0;
}