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
struct kvm_pmu {unsigned int nr_arch_gp_counters; unsigned int nr_arch_fixed_counters; struct kvm_pmc* gp_counters; struct kvm_pmc* fixed_counters; } ;
struct kvm_pmc {int dummy; } ;

/* Variables and functions */
 struct kvm_pmu* vcpu_to_pmu (struct kvm_vcpu*) ; 

__attribute__((used)) static struct kvm_pmc *intel_msr_idx_to_pmc(struct kvm_vcpu *vcpu,
					    unsigned idx)
{
	struct kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	bool fixed = idx & (1u << 30);
	struct kvm_pmc *counters;

	idx &= ~(3u << 30);
	if (!fixed && idx >= pmu->nr_arch_gp_counters)
		return NULL;
	if (fixed && idx >= pmu->nr_arch_fixed_counters)
		return NULL;
	counters = fixed ? pmu->fixed_counters : pmu->gp_counters;

	return &counters[idx];
}