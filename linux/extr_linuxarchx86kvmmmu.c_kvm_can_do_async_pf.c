#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  delivery_as_pf_vmexit; } ;
struct TYPE_5__ {scalar_t__ pending; } ;
struct TYPE_7__ {TYPE_2__ apf; TYPE_1__ exception; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;
struct TYPE_8__ {int (* interrupt_allowed ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 scalar_t__ is_guest_mode (struct kvm_vcpu*) ; 
 scalar_t__ kvm_event_needs_reinjection (struct kvm_vcpu*) ; 
 TYPE_4__* kvm_x86_ops ; 
 int /*<<< orphan*/  lapic_in_kernel (struct kvm_vcpu*) ; 
 int stub1 (struct kvm_vcpu*) ; 
 scalar_t__ unlikely (int) ; 

bool kvm_can_do_async_pf(struct kvm_vcpu *vcpu)
{
	if (unlikely(!lapic_in_kernel(vcpu) ||
		     kvm_event_needs_reinjection(vcpu) ||
		     vcpu->arch.exception.pending))
		return false;

	if (!vcpu->arch.apf.delivery_as_pf_vmexit && is_guest_mode(vcpu))
		return false;

	return kvm_x86_ops->interrupt_allowed(vcpu);
}