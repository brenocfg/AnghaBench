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
struct task_struct {int dummy; } ;

/* Variables and functions */
#define  ARCH_GET_CPUID 129 
#define  ARCH_SET_CPUID 128 
 long EINVAL ; 
 long get_cpuid_mode () ; 
 long set_cpuid_mode (struct task_struct*,unsigned long) ; 

long do_arch_prctl_common(struct task_struct *task, int option,
			  unsigned long cpuid_enabled)
{
	switch (option) {
	case ARCH_GET_CPUID:
		return get_cpuid_mode();
	case ARCH_SET_CPUID:
		return set_cpuid_mode(task, cpuid_enabled);
	}

	return -EINVAL;
}