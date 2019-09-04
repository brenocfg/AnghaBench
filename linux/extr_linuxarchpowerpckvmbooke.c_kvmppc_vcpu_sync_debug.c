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
struct TYPE_4__ {int shadow_msr; TYPE_1__* shared; } ;
struct kvm_vcpu {TYPE_2__ arch; scalar_t__ guest_debug; } ;
struct TYPE_3__ {int msr; } ;

/* Variables and functions */
 int MSR_DE ; 

__attribute__((used)) static void kvmppc_vcpu_sync_debug(struct kvm_vcpu *vcpu)
{
	/* Synchronize guest's desire to get debug interrupts into shadow MSR */
#ifndef CONFIG_KVM_BOOKE_HV
	vcpu->arch.shadow_msr &= ~MSR_DE;
	vcpu->arch.shadow_msr |= vcpu->arch.shared->msr & MSR_DE;
#endif

	/* Force enable debug interrupts when user space wants to debug */
	if (vcpu->guest_debug) {
#ifdef CONFIG_KVM_BOOKE_HV
		/*
		 * Since there is no shadow MSR, sync MSR_DE into the guest
		 * visible MSR.
		 */
		vcpu->arch.shared->msr |= MSR_DE;
#else
		vcpu->arch.shadow_msr |= MSR_DE;
		vcpu->arch.shared->msr &= ~MSR_DE;
#endif
	}
}