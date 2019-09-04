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
struct task_struct {struct mm_struct* active_mm; } ;
struct pt_regs {int dummy; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEGV_MAPERR ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  __do_kernel_fault (struct mm_struct*,unsigned long,unsigned int,struct pt_regs*) ; 
 int /*<<< orphan*/  __do_user_fault (struct task_struct*,unsigned long,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pt_regs*) ; 
 struct task_struct* current ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

void do_bad_area(unsigned long addr, unsigned int fsr, struct pt_regs *regs)
{
	struct task_struct *tsk = current;
	struct mm_struct *mm = tsk->active_mm;

	/*
	 * If we are in kernel mode at this point, we
	 * have no context to handle this fault with.
	 */
	if (user_mode(regs))
		__do_user_fault(tsk, addr, fsr, SIGSEGV, SEGV_MAPERR, regs);
	else
		__do_kernel_fault(mm, addr, fsr, regs);
}