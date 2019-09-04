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
 int /*<<< orphan*/  PTRACE_ARCH_PRCTL ; 
 int ptrace (int /*<<< orphan*/ ,int,unsigned long,int) ; 

int os_arch_prctl(int pid, int option, unsigned long *arg2)
{
	return ptrace(PTRACE_ARCH_PRCTL, pid, (unsigned long) arg2, option);
}