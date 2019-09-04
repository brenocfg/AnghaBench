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
struct cpuinfo_x86 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_PLATFORM_INFO ; 
 int MSR_PLATFORM_INFO_CPUID_FAULT ; 
 int /*<<< orphan*/  X86_FEATURE_CPUID_FAULT ; 
 int /*<<< orphan*/  rdmsrl_safe (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  set_cpu_cap (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_cpuid_fault(struct cpuinfo_x86 *c)
{
	u64 msr;

	if (!rdmsrl_safe(MSR_PLATFORM_INFO, &msr)) {
		if (msr & MSR_PLATFORM_INFO_CPUID_FAULT)
			set_cpu_cap(c, X86_FEATURE_CPUID_FAULT);
	}
}