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
 int /*<<< orphan*/  PTRACE_GETREGS ; 
 int /*<<< orphan*/  arch_init_registers (int) ; 
 int errno ; 
 int /*<<< orphan*/  exec_fp_regs ; 
 int /*<<< orphan*/  exec_regs ; 
 int /*<<< orphan*/  get_fp_registers (int,int /*<<< orphan*/ ) ; 
 int ptrace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int init_registers(int pid)
{
	int err;

	err = ptrace(PTRACE_GETREGS, pid, 0, exec_regs);
	if (err < 0)
		return -errno;

	arch_init_registers(pid);
	get_fp_registers(pid, exec_fp_regs);
	return 0;
}