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

/* Variables and functions */

void arch_init_registers(int pid)
{
#ifdef PTRACE_GETREGSET
	void * fp_regs;
	struct iovec iov;

	fp_regs = malloc(FP_SIZE * sizeof(unsigned long));
	if(fp_regs == NULL)
		return;

	iov.iov_base = fp_regs;
	iov.iov_len = FP_SIZE * sizeof(unsigned long);
	if (ptrace(PTRACE_GETREGSET, pid, NT_X86_XSTATE, &iov) == 0)
		have_xstate_support = 1;

	free(fp_regs);
#endif
}