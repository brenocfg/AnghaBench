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
struct kvm_pmu {struct kvm_pmc* gp_counters; } ;
struct kvm_pmc {scalar_t__ eventsel; scalar_t__ counter; } ;

/* Variables and functions */
 int AMD64_NUM_COUNTERS_CORE ; 
 int /*<<< orphan*/  pmc_stop_counter (struct kvm_pmc*) ; 
 struct kvm_pmu* vcpu_to_pmu (struct kvm_vcpu*) ; 

__attribute__((used)) static void amd_pmu_reset(struct kvm_vcpu *vcpu)
{
	struct kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	int i;

	for (i = 0; i < AMD64_NUM_COUNTERS_CORE; i++) {
		struct kvm_pmc *pmc = &pmu->gp_counters[i];

		pmc_stop_counter(pmc);
		pmc->counter = pmc->eventsel = 0;
	}
}