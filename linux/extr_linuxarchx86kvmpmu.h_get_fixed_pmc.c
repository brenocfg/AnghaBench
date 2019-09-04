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
struct kvm_pmu {int nr_arch_fixed_counters; struct kvm_pmc* fixed_counters; } ;
struct kvm_pmc {int dummy; } ;

/* Variables and functions */
 int MSR_CORE_PERF_FIXED_CTR0 ; 

__attribute__((used)) static inline struct kvm_pmc *get_fixed_pmc(struct kvm_pmu *pmu, u32 msr)
{
	int base = MSR_CORE_PERF_FIXED_CTR0;

	if (msr >= base && msr < base + pmu->nr_arch_fixed_counters)
		return &pmu->fixed_counters[msr - base];

	return NULL;
}