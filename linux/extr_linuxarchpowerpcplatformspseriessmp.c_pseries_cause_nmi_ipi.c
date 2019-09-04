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
 int H_SIGNAL_SYS_RESET_ALL_OTHERS ; 
 scalar_t__ H_SUCCESS ; 
 int NMI_IPI_ALL_OTHERS ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int get_hard_smp_processor_id (int) ; 
 scalar_t__ plpar_signal_sys_reset (int) ; 

__attribute__((used)) static int pseries_cause_nmi_ipi(int cpu)
{
	int hwcpu;

	if (cpu == NMI_IPI_ALL_OTHERS) {
		hwcpu = H_SIGNAL_SYS_RESET_ALL_OTHERS;
	} else {
		if (cpu < 0) {
			WARN_ONCE(true, "incorrect cpu parameter %d", cpu);
			return 0;
		}

		hwcpu = get_hard_smp_processor_id(cpu);
	}

	if (plpar_signal_sys_reset(hwcpu) == H_SUCCESS)
		return 1;

	return 0;
}