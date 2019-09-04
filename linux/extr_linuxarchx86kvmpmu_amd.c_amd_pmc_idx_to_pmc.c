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
struct kvm_pmc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMU_TYPE_COUNTER ; 
 int /*<<< orphan*/  X86_FEATURE_PERFCTR_CORE ; 
 struct kvm_pmc* get_gp_pmc_amd (struct kvm_pmu*,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int get_msr_base (struct kvm_pmu*,int /*<<< orphan*/ ) ; 
 scalar_t__ guest_cpuid_has (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 struct kvm_vcpu* pmu_to_vcpu (struct kvm_pmu*) ; 

__attribute__((used)) static struct kvm_pmc *amd_pmc_idx_to_pmc(struct kvm_pmu *pmu, int pmc_idx)
{
	unsigned int base = get_msr_base(pmu, PMU_TYPE_COUNTER);
	struct kvm_vcpu *vcpu = pmu_to_vcpu(pmu);

	if (guest_cpuid_has(vcpu, X86_FEATURE_PERFCTR_CORE)) {
		/*
		 * The idx is contiguous. The MSRs are not. The counter MSRs
		 * are interleaved with the event select MSRs.
		 */
		pmc_idx *= 2;
	}

	return get_gp_pmc_amd(pmu, base + pmc_idx, PMU_TYPE_COUNTER);
}