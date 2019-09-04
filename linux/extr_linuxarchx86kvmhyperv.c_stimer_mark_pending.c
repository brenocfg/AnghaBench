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
struct kvm_vcpu_hv_stimer {int /*<<< orphan*/  index; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  stimer_pending_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_HV_STIMER ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_kick (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct kvm_vcpu* stimer_to_vcpu (struct kvm_vcpu_hv_stimer*) ; 
 TYPE_1__* vcpu_to_hv_vcpu (struct kvm_vcpu*) ; 

__attribute__((used)) static void stimer_mark_pending(struct kvm_vcpu_hv_stimer *stimer,
				bool vcpu_kick)
{
	struct kvm_vcpu *vcpu = stimer_to_vcpu(stimer);

	set_bit(stimer->index,
		vcpu_to_hv_vcpu(vcpu)->stimer_pending_bitmap);
	kvm_make_request(KVM_REQ_HV_STIMER, vcpu);
	if (vcpu_kick)
		kvm_vcpu_kick(vcpu);
}