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
struct pt_regs {scalar_t__* gprs; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEFAULT ; 
 int /*<<< orphan*/  show_last_breaking_event (struct pt_regs*) ; 
 int /*<<< orphan*/  show_registers (struct pt_regs*) ; 
 int /*<<< orphan*/  show_regs_print_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_stack (int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 

void show_regs(struct pt_regs *regs)
{
	show_regs_print_info(KERN_DEFAULT);
	show_registers(regs);
	/* Show stack backtrace if pt_regs is from kernel mode */
	if (!user_mode(regs))
		show_stack(NULL, (unsigned long *) regs->gprs[15]);
	show_last_breaking_event(regs);
}