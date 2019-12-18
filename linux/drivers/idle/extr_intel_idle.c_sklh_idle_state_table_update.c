#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_FEATURE_CONTROL ; 
 int /*<<< orphan*/  MSR_PKG_CST_CONFIG_CONTROL ; 
 int /*<<< orphan*/  cpuid (int,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 
 int max_cstate ; 
 int mwait_substates ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,unsigned long long) ; 
 TYPE_1__* skl_cstates ; 

__attribute__((used)) static void sklh_idle_state_table_update(void)
{
	unsigned long long msr;
	unsigned int eax, ebx, ecx, edx;


	/* if PC10 disabled via cmdline intel_idle.max_cstate=7 or shallower */
	if (max_cstate <= 7)
		return;

	/* if PC10 not present in CPUID.MWAIT.EDX */
	if ((mwait_substates & (0xF << 28)) == 0)
		return;

	rdmsrl(MSR_PKG_CST_CONFIG_CONTROL, msr);

	/* PC10 is not enabled in PKG C-state limit */
	if ((msr & 0xF) != 8)
		return;

	ecx = 0;
	cpuid(7, &eax, &ebx, &ecx, &edx);

	/* if SGX is present */
	if (ebx & (1 << 2)) {

		rdmsrl(MSR_IA32_FEATURE_CONTROL, msr);

		/* if SGX is enabled */
		if (msr & (1 << 18))
			return;
	}

	skl_cstates[5].disabled = 1;	/* C8-SKL */
	skl_cstates[6].disabled = 1;	/* C9-SKL */
}