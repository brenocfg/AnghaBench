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
typedef  int u32 ;

/* Variables and functions */
 int MSR_CORE_PERF_FIXED_CTR0 ; 
#define  MSR_CORE_PERF_FIXED_CTR_CTRL 133 
#define  MSR_CORE_PERF_GLOBAL_CTRL 132 
#define  MSR_CORE_PERF_GLOBAL_OVF_CTRL 131 
#define  MSR_CORE_PERF_GLOBAL_STATUS 130 
#define  MSR_IA32_DS_AREA 129 
#define  MSR_IA32_PEBS_ENABLE 128 
 int MSR_IA32_PERFCTR0 ; 
 int MSR_P6_EVNTSEL0 ; 
 int MSR_PMC_ALIAS_MASK ; 
 int MSR_TYPE_ARCH_COUNTER ; 
 int MSR_TYPE_ARCH_CTRL ; 
 int MSR_TYPE_COUNTER ; 
 int MSR_TYPE_CTRL ; 
 int MSR_TYPE_GLOBAL ; 
 int intel_num_arch_counters ; 
 int intel_num_fixed_counters ; 

__attribute__((used)) static int is_intel_pmu_msr(u32 msr_index, int *type, int *index)
{
	u32 msr_index_pmc;

	switch (msr_index) {
	case MSR_CORE_PERF_FIXED_CTR_CTRL:
	case MSR_IA32_DS_AREA:
	case MSR_IA32_PEBS_ENABLE:
		*type = MSR_TYPE_CTRL;
		return true;

	case MSR_CORE_PERF_GLOBAL_CTRL:
	case MSR_CORE_PERF_GLOBAL_STATUS:
	case MSR_CORE_PERF_GLOBAL_OVF_CTRL:
		*type = MSR_TYPE_GLOBAL;
		return true;

	default:

		if ((msr_index >= MSR_CORE_PERF_FIXED_CTR0) &&
		    (msr_index < MSR_CORE_PERF_FIXED_CTR0 +
				 intel_num_fixed_counters)) {
			*index = msr_index - MSR_CORE_PERF_FIXED_CTR0;
			*type = MSR_TYPE_COUNTER;
			return true;
		}

		if ((msr_index >= MSR_P6_EVNTSEL0) &&
		    (msr_index < MSR_P6_EVNTSEL0 +  intel_num_arch_counters)) {
			*index = msr_index - MSR_P6_EVNTSEL0;
			*type = MSR_TYPE_ARCH_CTRL;
			return true;
		}

		msr_index_pmc = msr_index & MSR_PMC_ALIAS_MASK;
		if ((msr_index_pmc >= MSR_IA32_PERFCTR0) &&
		    (msr_index_pmc < MSR_IA32_PERFCTR0 +
				     intel_num_arch_counters)) {
			*type = MSR_TYPE_ARCH_COUNTER;
			*index = msr_index_pmc - MSR_IA32_PERFCTR0;
			return true;
		}
		return false;
	}
}