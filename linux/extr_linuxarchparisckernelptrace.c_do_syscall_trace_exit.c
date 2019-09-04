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
 int /*<<< orphan*/  TIF_BLOCKSTEP ; 
 int /*<<< orphan*/  TIF_SINGLESTEP ; 
 int /*<<< orphan*/  TIF_SYSCALL_TRACE ; 
 int /*<<< orphan*/  audit_syscall_exit (struct pt_regs*) ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tracehook_report_syscall_exit (struct pt_regs*,int) ; 

void do_syscall_trace_exit(struct pt_regs *regs)
{
	int stepping = test_thread_flag(TIF_SINGLESTEP) ||
		test_thread_flag(TIF_BLOCKSTEP);

	audit_syscall_exit(regs);

#ifdef CONFIG_HAVE_SYSCALL_TRACEPOINTS
	if (unlikely(test_thread_flag(TIF_SYSCALL_TRACEPOINT)))
		trace_sys_exit(regs, regs->gr[20]);
#endif

	if (stepping || test_thread_flag(TIF_SYSCALL_TRACE))
		tracehook_report_syscall_exit(regs, stepping);
}