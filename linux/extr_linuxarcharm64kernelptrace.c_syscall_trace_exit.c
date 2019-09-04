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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTRACE_SYSCALL_EXIT ; 
 int /*<<< orphan*/  TIF_SYSCALL_TRACE ; 
 int /*<<< orphan*/  TIF_SYSCALL_TRACEPOINT ; 
 int /*<<< orphan*/  audit_syscall_exit (struct pt_regs*) ; 
 int /*<<< orphan*/  regs_return_value (struct pt_regs*) ; 
 int /*<<< orphan*/  rseq_syscall (struct pt_regs*) ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_sys_exit (struct pt_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tracehook_report_syscall (struct pt_regs*,int /*<<< orphan*/ ) ; 

void syscall_trace_exit(struct pt_regs *regs)
{
	audit_syscall_exit(regs);

	if (test_thread_flag(TIF_SYSCALL_TRACEPOINT))
		trace_sys_exit(regs, regs_return_value(regs));

	if (test_thread_flag(TIF_SYSCALL_TRACE))
		tracehook_report_syscall(regs, PTRACE_SYSCALL_EXIT);

	rseq_syscall(regs);
}