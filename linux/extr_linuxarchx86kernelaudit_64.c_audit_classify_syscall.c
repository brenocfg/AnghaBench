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
#define  __NR_execve 131 
#define  __NR_execveat 130 
#define  __NR_open 129 
#define  __NR_openat 128 

int audit_classify_syscall(int abi, unsigned syscall)
{
#ifdef CONFIG_IA32_EMULATION
	extern int ia32_classify_syscall(unsigned);
	if (abi == AUDIT_ARCH_I386)
		return ia32_classify_syscall(syscall);
#endif
	switch(syscall) {
	case __NR_open:
		return 2;
	case __NR_openat:
		return 3;
	case __NR_execve:
	case __NR_execveat:
		return 5;
	default:
		return 0;
	}
}