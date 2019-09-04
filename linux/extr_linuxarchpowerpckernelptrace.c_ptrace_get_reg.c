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
struct TYPE_2__ {int /*<<< orphan*/ * regs; } ;
struct task_struct {TYPE_1__ thread; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int PT_DSCR ; 
 int PT_MSR ; 
 int get_user_dscr (struct task_struct*,unsigned long*) ; 
 unsigned long get_user_msr (struct task_struct*) ; 

int ptrace_get_reg(struct task_struct *task, int regno, unsigned long *data)
{
	if ((task->thread.regs == NULL) || !data)
		return -EIO;

	if (regno == PT_MSR) {
		*data = get_user_msr(task);
		return 0;
	}

	if (regno == PT_DSCR)
		return get_user_dscr(task, data);

#ifdef CONFIG_PPC64
	/*
	 * softe copies paca->irq_soft_mask variable state. Since irq_soft_mask is
	 * no more used as a flag, lets force usr to alway see the softe value as 1
	 * which means interrupts are not soft disabled.
	 */
	if (regno == PT_SOFTE) {
		*data = 1;
		return  0;
	}
#endif

	if (regno < (sizeof(struct pt_regs) / sizeof(unsigned long))) {
		*data = ((unsigned long *)task->thread.regs)[regno];
		return 0;
	}

	return -EIO;
}