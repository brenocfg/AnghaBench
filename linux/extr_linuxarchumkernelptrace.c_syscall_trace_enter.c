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
struct pt_regs {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_SYSCALL_TRACE ; 
 int /*<<< orphan*/  UPT_SYSCALL_ARG1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UPT_SYSCALL_ARG2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UPT_SYSCALL_ARG3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UPT_SYSCALL_ARG4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UPT_SYSCALL_NR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  audit_syscall_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_thread_flag (int /*<<< orphan*/ ) ; 
 int tracehook_report_syscall_entry (struct pt_regs*) ; 

int syscall_trace_enter(struct pt_regs *regs)
{
	audit_syscall_entry(UPT_SYSCALL_NR(&regs->regs),
			    UPT_SYSCALL_ARG1(&regs->regs),
			    UPT_SYSCALL_ARG2(&regs->regs),
			    UPT_SYSCALL_ARG3(&regs->regs),
			    UPT_SYSCALL_ARG4(&regs->regs));

	if (!test_thread_flag(TIF_SYSCALL_TRACE))
		return 0;

	return tracehook_report_syscall_entry(regs);
}