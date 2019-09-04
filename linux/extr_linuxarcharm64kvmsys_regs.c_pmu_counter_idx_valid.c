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
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int ARMV8_PMU_CYCLE_IDX ; 
 int ARMV8_PMU_PMCR_N_MASK ; 
 int ARMV8_PMU_PMCR_N_SHIFT ; 
 int /*<<< orphan*/  PMCR_EL0 ; 
 int __vcpu_sys_reg (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_inject_undefined (struct kvm_vcpu*) ; 

__attribute__((used)) static bool pmu_counter_idx_valid(struct kvm_vcpu *vcpu, u64 idx)
{
	u64 pmcr, val;

	pmcr = __vcpu_sys_reg(vcpu, PMCR_EL0);
	val = (pmcr >> ARMV8_PMU_PMCR_N_SHIFT) & ARMV8_PMU_PMCR_N_MASK;
	if (idx >= val && idx != ARMV8_PMU_CYCLE_IDX) {
		kvm_inject_undefined(vcpu);
		return false;
	}

	return true;
}