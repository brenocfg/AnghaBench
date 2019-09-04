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
struct TYPE_3__ {scalar_t__ pv_unhalted; } ;
struct TYPE_4__ {scalar_t__ mp_state; TYPE_1__ pv; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
struct kvm_mp_state {scalar_t__ mp_state; } ;

/* Variables and functions */
 scalar_t__ KVM_MP_STATE_HALTED ; 
 scalar_t__ KVM_MP_STATE_RUNNABLE ; 
 int /*<<< orphan*/  kvm_apic_accept_events (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_load (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_put (struct kvm_vcpu*) ; 

int kvm_arch_vcpu_ioctl_get_mpstate(struct kvm_vcpu *vcpu,
				    struct kvm_mp_state *mp_state)
{
	vcpu_load(vcpu);

	kvm_apic_accept_events(vcpu);
	if (vcpu->arch.mp_state == KVM_MP_STATE_HALTED &&
					vcpu->arch.pv.pv_unhalted)
		mp_state->mp_state = KVM_MP_STATE_RUNNABLE;
	else
		mp_state->mp_state = vcpu->arch.mp_state;

	vcpu_put(vcpu);
	return 0;
}