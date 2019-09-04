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
typedef  int u64 ;

/* Variables and functions */
 int MCG_STATUS_RIPV ; 
 int /*<<< orphan*/  MSR_IA32_MCG_STATUS ; 
 scalar_t__ cpu_is_offline (int) ; 
 int crashing_cpu ; 
 int mce_rdmsrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mce_wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool __mc_check_crashing_cpu(int cpu)
{
	if (cpu_is_offline(cpu) ||
	    (crashing_cpu != -1 && crashing_cpu != cpu)) {
		u64 mcgstatus;

		mcgstatus = mce_rdmsrl(MSR_IA32_MCG_STATUS);
		if (mcgstatus & MCG_STATUS_RIPV) {
			mce_wrmsrl(MSR_IA32_MCG_STATUS, 0);
			return true;
		}
	}
	return false;
}