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
struct TYPE_3__ {int /*<<< orphan*/  dr6; } ;
struct kvm_vcpu {int guest_debug; TYPE_1__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_dr6 ) (struct kvm_vcpu*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int KVM_GUESTDBG_USE_HW_BP ; 
 TYPE_2__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvm_update_dr6(struct kvm_vcpu *vcpu)
{
	if (!(vcpu->guest_debug & KVM_GUESTDBG_USE_HW_BP))
		kvm_x86_ops->set_dr6(vcpu, vcpu->arch.dr6);
}