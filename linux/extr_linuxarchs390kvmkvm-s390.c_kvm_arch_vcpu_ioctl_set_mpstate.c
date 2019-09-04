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
struct kvm_vcpu {TYPE_2__* kvm; } ;
struct kvm_mp_state {int mp_state; } ;
struct TYPE_3__ {int user_cpu_state_ctrl; } ;
struct TYPE_4__ {TYPE_1__ arch; } ;

/* Variables and functions */
 int ENXIO ; 
#define  KVM_MP_STATE_CHECK_STOP 131 
#define  KVM_MP_STATE_LOAD 130 
#define  KVM_MP_STATE_OPERATING 129 
#define  KVM_MP_STATE_STOPPED 128 
 int /*<<< orphan*/  kvm_s390_vcpu_start (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_s390_vcpu_stop (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_load (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_put (struct kvm_vcpu*) ; 

int kvm_arch_vcpu_ioctl_set_mpstate(struct kvm_vcpu *vcpu,
				    struct kvm_mp_state *mp_state)
{
	int rc = 0;

	vcpu_load(vcpu);

	/* user space knows about this interface - let it control the state */
	vcpu->kvm->arch.user_cpu_state_ctrl = 1;

	switch (mp_state->mp_state) {
	case KVM_MP_STATE_STOPPED:
		kvm_s390_vcpu_stop(vcpu);
		break;
	case KVM_MP_STATE_OPERATING:
		kvm_s390_vcpu_start(vcpu);
		break;
	case KVM_MP_STATE_LOAD:
	case KVM_MP_STATE_CHECK_STOP:
		/* fall through - CHECK_STOP and LOAD are not supported yet */
	default:
		rc = -ENXIO;
	}

	vcpu_put(vcpu);
	return rc;
}