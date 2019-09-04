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
struct pt_regs {unsigned long r6; unsigned long r7; unsigned long sp; unsigned long pc; scalar_t__* uregs; scalar_t__ osp; } ;
struct TYPE_2__ {struct pt_regs cpu_context; } ;
struct task_struct {int flags; TYPE_1__ thread; } ;
struct cpu_context {int dummy; } ;

/* Variables and functions */
 unsigned long CLONE_SETTLS ; 
 int PF_KTHREAD ; 
 struct pt_regs* current_pt_regs () ; 
 int /*<<< orphan*/  memset (struct pt_regs*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ret_from_fork ; 
 struct pt_regs* task_pt_regs (struct task_struct*) ; 
 scalar_t__ unlikely (int) ; 

int copy_thread(unsigned long clone_flags, unsigned long stack_start,
	    unsigned long stk_sz, struct task_struct *p)
{
	struct pt_regs *childregs = task_pt_regs(p);

	memset(&p->thread.cpu_context, 0, sizeof(struct cpu_context));

	if (unlikely(p->flags & PF_KTHREAD)) {
		memset(childregs, 0, sizeof(struct pt_regs));
		/* kernel thread fn */
		p->thread.cpu_context.r6 = stack_start;
		/* kernel thread argument */
		p->thread.cpu_context.r7 = stk_sz;
	} else {
		*childregs = *current_pt_regs();
		if (stack_start)
			childregs->sp = stack_start;
		/* child get zero as ret. */
		childregs->uregs[0] = 0;
		childregs->osp = 0;
		if (clone_flags & CLONE_SETTLS)
			childregs->uregs[25] = childregs->uregs[3];
	}
	/* cpu context switching  */
	p->thread.cpu_context.pc = (unsigned long)ret_from_fork;
	p->thread.cpu_context.sp = (unsigned long)childregs;

#ifdef CONFIG_HWZOL
	childregs->lb = 0;
	childregs->le = 0;
	childregs->lc = 0;
#endif

	return 0;
}