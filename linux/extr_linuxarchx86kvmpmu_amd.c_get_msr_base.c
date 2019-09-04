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
struct kvm_vcpu {int dummy; } ;
struct kvm_pmu {int dummy; } ;
typedef  enum pmu_type { ____Placeholder_pmu_type } pmu_type ;

/* Variables and functions */
 unsigned int MSR_F15H_PERF_CTL ; 
 unsigned int MSR_F15H_PERF_CTR ; 
 unsigned int MSR_K7_EVNTSEL0 ; 
 unsigned int MSR_K7_PERFCTR0 ; 
 int PMU_TYPE_COUNTER ; 
 int /*<<< orphan*/  X86_FEATURE_PERFCTR_CORE ; 
 scalar_t__ guest_cpuid_has (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 struct kvm_vcpu* pmu_to_vcpu (struct kvm_pmu*) ; 

__attribute__((used)) static unsigned int get_msr_base(struct kvm_pmu *pmu, enum pmu_type type)
{
	struct kvm_vcpu *vcpu = pmu_to_vcpu(pmu);

	if (guest_cpuid_has(vcpu, X86_FEATURE_PERFCTR_CORE)) {
		if (type == PMU_TYPE_COUNTER)
			return MSR_F15H_PERF_CTR;
		else
			return MSR_F15H_PERF_CTL;
	} else {
		if (type == PMU_TYPE_COUNTER)
			return MSR_K7_PERFCTR0;
		else
			return MSR_K7_EVNTSEL0;
	}
}