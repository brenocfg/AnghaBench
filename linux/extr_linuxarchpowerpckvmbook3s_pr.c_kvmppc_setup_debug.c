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
struct kvm_vcpu {int guest_debug; } ;

/* Variables and functions */
 int KVM_GUESTDBG_SINGLESTEP ; 
 int MSR_SE ; 
 int kvmppc_get_msr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_set_msr (struct kvm_vcpu*,int) ; 

__attribute__((used)) static void kvmppc_setup_debug(struct kvm_vcpu *vcpu)
{
	if (vcpu->guest_debug & KVM_GUESTDBG_SINGLESTEP) {
		u64 msr = kvmppc_get_msr(vcpu);

		kvmppc_set_msr(vcpu, msr | MSR_SE);
	}
}