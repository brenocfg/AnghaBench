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
struct pt_regs {unsigned long* regs; unsigned long cp0_epc; } ;

/* Variables and functions */
 int /*<<< orphan*/  __kernel_text_address (unsigned long) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  pr_cont (char*) ; 
 int /*<<< orphan*/  print_ip_sym (unsigned long) ; 
 int /*<<< orphan*/  printk (char*) ; 
 scalar_t__ raw_show_trace ; 
 int /*<<< orphan*/  show_raw_backtrace (unsigned long) ; 
 unsigned long unwind_stack (struct task_struct*,unsigned long*,unsigned long,unsigned long*) ; 
 scalar_t__ user_mode (struct pt_regs const*) ; 

__attribute__((used)) static void show_backtrace(struct task_struct *task, const struct pt_regs *regs)
{
	unsigned long sp = regs->regs[29];
	unsigned long ra = regs->regs[31];
	unsigned long pc = regs->cp0_epc;

	if (!task)
		task = current;

	if (raw_show_trace || user_mode(regs) || !__kernel_text_address(pc)) {
		show_raw_backtrace(sp);
		return;
	}
	printk("Call Trace:\n");
	do {
		print_ip_sym(pc);
		pc = unwind_stack(task, &sp, pc, &ra);
	} while (pc);
	pr_cont("\n");
}