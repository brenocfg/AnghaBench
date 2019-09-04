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
struct kvm_vcpu {int dummy; } ;
struct kvm_pmu {TYPE_1__* gp_counters; } ;
struct TYPE_2__ {int idx; struct kvm_vcpu* vcpu; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int AMD64_NUM_COUNTERS_CORE ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int INTEL_PMC_MAX_GENERIC ; 
 int /*<<< orphan*/  KVM_PMC_GP ; 
 struct kvm_pmu* vcpu_to_pmu (struct kvm_vcpu*) ; 

__attribute__((used)) static void amd_pmu_init(struct kvm_vcpu *vcpu)
{
	struct kvm_pmu *pmu = vcpu_to_pmu(vcpu);
	int i;

	BUILD_BUG_ON(AMD64_NUM_COUNTERS_CORE > INTEL_PMC_MAX_GENERIC);

	for (i = 0; i < AMD64_NUM_COUNTERS_CORE ; i++) {
		pmu->gp_counters[i].type = KVM_PMC_GP;
		pmu->gp_counters[i].vcpu = vcpu;
		pmu->gp_counters[i].idx = i;
	}
}