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
struct TYPE_2__ {scalar_t__ prodded; scalar_t__ pending_exceptions; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 scalar_t__ kvmppc_doorbell_pending (struct kvm_vcpu*) ; 
 scalar_t__ xive_interrupt_pending (struct kvm_vcpu*) ; 

__attribute__((used)) static bool kvmppc_vcpu_woken(struct kvm_vcpu *vcpu)
{
	if (vcpu->arch.pending_exceptions || vcpu->arch.prodded ||
	    kvmppc_doorbell_pending(vcpu) || xive_interrupt_pending(vcpu))
		return true;

	return false;
}