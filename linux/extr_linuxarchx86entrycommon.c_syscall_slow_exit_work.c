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
typedef  int u32 ;
struct pt_regs {int /*<<< orphan*/  ax; } ;

/* Variables and functions */
 int _TIF_SINGLESTEP ; 
 int _TIF_SYSCALL_EMU ; 
 int _TIF_SYSCALL_TRACE ; 
 int _TIF_SYSCALL_TRACEPOINT ; 
 int /*<<< orphan*/  audit_syscall_exit (struct pt_regs*) ; 
 int /*<<< orphan*/  trace_sys_exit (struct pt_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tracehook_report_syscall_exit (struct pt_regs*,int) ; 
 int unlikely (int) ; 

__attribute__((used)) static void syscall_slow_exit_work(struct pt_regs *regs, u32 cached_flags)
{
	bool step;

	audit_syscall_exit(regs);

	if (cached_flags & _TIF_SYSCALL_TRACEPOINT)
		trace_sys_exit(regs, regs->ax);

	/*
	 * If TIF_SYSCALL_EMU is set, we only get here because of
	 * TIF_SINGLESTEP (i.e. this is PTRACE_SYSEMU_SINGLESTEP).
	 * We already reported this syscall instruction in
	 * syscall_trace_enter().
	 */
	step = unlikely(
		(cached_flags & (_TIF_SINGLESTEP | _TIF_SYSCALL_EMU))
		== _TIF_SINGLESTEP);
	if (step || cached_flags & _TIF_SYSCALL_TRACE)
		tracehook_report_syscall_exit(regs, step);
}