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
struct pt_regs {int* gpr; } ;

/* Variables and functions */
 long ENOSYS ; 
 int NR_syscalls ; 
 int /*<<< orphan*/  TIF_SYSCALL_TRACE ; 
 int /*<<< orphan*/  TIF_SYSCALL_TRACEPOINT ; 
 int /*<<< orphan*/  audit_syscall_entry (int,int,int,int,int) ; 
 scalar_t__ do_seccomp (struct pt_regs*) ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_sys_enter (struct pt_regs*,int) ; 
 scalar_t__ tracehook_report_syscall_entry (struct pt_regs*) ; 
 scalar_t__ unlikely (scalar_t__) ; 
 int /*<<< orphan*/  user_exit () ; 

long do_syscall_trace_enter(struct pt_regs *regs)
{
	user_exit();

	/*
	 * The tracer may decide to abort the syscall, if so tracehook
	 * will return !0. Note that the tracer may also just change
	 * regs->gpr[0] to an invalid syscall number, that is handled
	 * below on the exit path.
	 */
	if (test_thread_flag(TIF_SYSCALL_TRACE) &&
	    tracehook_report_syscall_entry(regs))
		goto skip;

	/* Run seccomp after ptrace; allow it to set gpr[3]. */
	if (do_seccomp(regs))
		return -1;

	/* Avoid trace and audit when syscall is invalid. */
	if (regs->gpr[0] >= NR_syscalls)
		goto skip;

	if (unlikely(test_thread_flag(TIF_SYSCALL_TRACEPOINT)))
		trace_sys_enter(regs, regs->gpr[0]);

#ifdef CONFIG_PPC64
	if (!is_32bit_task())
		audit_syscall_entry(regs->gpr[0], regs->gpr[3], regs->gpr[4],
				    regs->gpr[5], regs->gpr[6]);
	else
#endif
		audit_syscall_entry(regs->gpr[0],
				    regs->gpr[3] & 0xffffffff,
				    regs->gpr[4] & 0xffffffff,
				    regs->gpr[5] & 0xffffffff,
				    regs->gpr[6] & 0xffffffff);

	/* Return the possibly modified but valid syscall number */
	return regs->gpr[0];

skip:
	/*
	 * If we are aborting explicitly, or if the syscall number is
	 * now invalid, set the return value to -ENOSYS.
	 */
	regs->gpr[3] = -ENOSYS;
	return -1;
}