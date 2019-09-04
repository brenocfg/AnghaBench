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
struct TYPE_2__ {int posted_intr_nv; int pi_pending; } ;
struct vcpu_vmx {TYPE_1__ nested; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_EVENT ; 
 scalar_t__ is_guest_mode (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_kick (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_trigger_posted_interrupt (struct kvm_vcpu*,int) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 

__attribute__((used)) static int vmx_deliver_nested_posted_interrupt(struct kvm_vcpu *vcpu,
						int vector)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);

	if (is_guest_mode(vcpu) &&
	    vector == vmx->nested.posted_intr_nv) {
		/*
		 * If a posted intr is not recognized by hardware,
		 * we will accomplish it in the next vmentry.
		 */
		vmx->nested.pi_pending = true;
		kvm_make_request(KVM_REQ_EVENT, vcpu);
		/* the PIR and ON have been set by L1. */
		if (!kvm_vcpu_trigger_posted_interrupt(vcpu, true))
			kvm_vcpu_kick(vcpu);
		return 0;
	}
	return -1;
}