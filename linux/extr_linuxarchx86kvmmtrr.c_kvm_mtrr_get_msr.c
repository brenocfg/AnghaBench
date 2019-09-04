#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long u64 ;
typedef  int u32 ;
struct TYPE_5__ {unsigned long long deftype; TYPE_1__* var_ranges; int /*<<< orphan*/ * fixed_ranges; } ;
struct TYPE_6__ {unsigned long long pat; TYPE_2__ mtrr_state; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;
struct TYPE_4__ {unsigned long long base; unsigned long long mask; } ;

/* Variables and functions */
 int KVM_NR_VAR_MTRR ; 
 int MSR_IA32_CR_PAT ; 
 int MSR_MTRRcap ; 
 int MSR_MTRRdefType ; 
 unsigned long long cpuid_maxphyaddr (struct kvm_vcpu*) ; 
 int fixed_msr_to_range_index (int) ; 
 int /*<<< orphan*/  msr_mtrr_valid (int) ; 

int kvm_mtrr_get_msr(struct kvm_vcpu *vcpu, u32 msr, u64 *pdata)
{
	int index;

	/* MSR_MTRRcap is a readonly MSR. */
	if (msr == MSR_MTRRcap) {
		/*
		 * SMRR = 0
		 * WC = 1
		 * FIX = 1
		 * VCNT = KVM_NR_VAR_MTRR
		 */
		*pdata = 0x500 | KVM_NR_VAR_MTRR;
		return 0;
	}

	if (!msr_mtrr_valid(msr))
		return 1;

	index = fixed_msr_to_range_index(msr);
	if (index >= 0)
		*pdata = *(u64 *)&vcpu->arch.mtrr_state.fixed_ranges[index];
	else if (msr == MSR_MTRRdefType)
		*pdata = vcpu->arch.mtrr_state.deftype;
	else if (msr == MSR_IA32_CR_PAT)
		*pdata = vcpu->arch.pat;
	else {	/* Variable MTRRs */
		int is_mtrr_mask;

		index = (msr - 0x200) / 2;
		is_mtrr_mask = msr - 0x200 - 2 * index;
		if (!is_mtrr_mask)
			*pdata = vcpu->arch.mtrr_state.var_ranges[index].base;
		else
			*pdata = vcpu->arch.mtrr_state.var_ranges[index].mask;

		*pdata &= (1ULL << cpuid_maxphyaddr(vcpu)) - 1;
	}

	return 0;
}