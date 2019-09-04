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
 int check_tsc_unstable () ; 

__attribute__((used)) static inline bool kvm_check_tsc_unstable(void)
{
#ifdef CONFIG_X86_64
	/*
	 * TSC is marked unstable when we're running on Hyper-V,
	 * 'TSC page' clocksource is good.
	 */
	if (pvclock_gtod_data.clock.vclock_mode == VCLOCK_HVCLOCK)
		return false;
#endif
	return check_tsc_unstable();
}