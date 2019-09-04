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
struct pt_regs {int /*<<< orphan*/  result; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_SINGLESTEP ; 
 int /*<<< orphan*/  TIF_SYSCALL_TRACE ; 
 int /*<<< orphan*/  TIF_SYSCALL_TRACEPOINT ; 
 int /*<<< orphan*/  audit_syscall_exit (struct pt_regs*) ; 
 int test_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_sys_exit (struct pt_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tracehook_report_syscall_exit (struct pt_regs*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  user_enter () ; 

void do_syscall_trace_leave(struct pt_regs *regs)
{
	int step;

	audit_syscall_exit(regs);

	if (unlikely(test_thread_flag(TIF_SYSCALL_TRACEPOINT)))
		trace_sys_exit(regs, regs->result);

	step = test_thread_flag(TIF_SINGLESTEP);
	if (step || test_thread_flag(TIF_SYSCALL_TRACE))
		tracehook_report_syscall_exit(regs, step);

	user_enter();
}