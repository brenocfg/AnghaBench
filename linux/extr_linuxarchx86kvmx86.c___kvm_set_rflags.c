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
struct TYPE_3__ {int /*<<< orphan*/  singlestep_rip; } ;
struct kvm_vcpu {int guest_debug; TYPE_1__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_rflags ) (struct kvm_vcpu*,unsigned long) ;} ;

/* Variables and functions */
 int KVM_GUESTDBG_SINGLESTEP ; 
 unsigned long X86_EFLAGS_TF ; 
 scalar_t__ kvm_is_linear_rip (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 TYPE_2__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,unsigned long) ; 

__attribute__((used)) static void __kvm_set_rflags(struct kvm_vcpu *vcpu, unsigned long rflags)
{
	if (vcpu->guest_debug & KVM_GUESTDBG_SINGLESTEP &&
	    kvm_is_linear_rip(vcpu, vcpu->arch.singlestep_rip))
		rflags |= X86_EFLAGS_TF;
	kvm_x86_ops->set_rflags(vcpu, rflags);
}