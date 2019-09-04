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
struct TYPE_2__ {struct kvm_lapic* apic; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_lapic {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ APIC_IRR ; 
 scalar_t__ APIC_ISR ; 
 scalar_t__ apic_test_vector (int,scalar_t__) ; 

bool kvm_apic_pending_eoi(struct kvm_vcpu *vcpu, int vector)
{
	struct kvm_lapic *apic = vcpu->arch.apic;

	return apic_test_vector(vector, apic->regs + APIC_ISR) ||
		apic_test_vector(vector, apic->regs + APIC_IRR);
}