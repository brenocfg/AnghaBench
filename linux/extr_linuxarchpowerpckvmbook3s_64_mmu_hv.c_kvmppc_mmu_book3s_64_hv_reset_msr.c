#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned long msr; } ;
struct TYPE_4__ {unsigned long intr_msr; TYPE_1__ shregs; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
 scalar_t__ MSR_TM_TRANSACTIONAL (unsigned long) ; 
 unsigned long MSR_TS_MASK ; 
 unsigned long MSR_TS_S ; 
 int /*<<< orphan*/  kvmppc_set_msr (struct kvm_vcpu*,unsigned long) ; 

__attribute__((used)) static void kvmppc_mmu_book3s_64_hv_reset_msr(struct kvm_vcpu *vcpu)
{
	unsigned long msr = vcpu->arch.intr_msr;

	/* If transactional, change to suspend mode on IRQ delivery */
	if (MSR_TM_TRANSACTIONAL(vcpu->arch.shregs.msr))
		msr |= MSR_TS_S;
	else
		msr |= vcpu->arch.shregs.msr & MSR_TS_MASK;
	kvmppc_set_msr(vcpu, msr);
}