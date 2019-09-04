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
struct TYPE_3__ {int injected; } ;
struct TYPE_4__ {TYPE_1__ interrupt; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
 int kvm_apic_has_interrupt (struct kvm_vcpu*) ; 
 scalar_t__ kvm_cpu_has_extint (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  lapic_in_kernel (struct kvm_vcpu*) ; 

int kvm_cpu_has_interrupt(struct kvm_vcpu *v)
{
	/*
	 * FIXME: interrupt.injected represents an interrupt that it's
	 * side-effects have already been applied (e.g. bit from IRR
	 * already moved to ISR). Therefore, it is incorrect to rely
	 * on interrupt.injected to know if there is a pending
	 * interrupt in the user-mode LAPIC.
	 * This leads to nVMX/nSVM not be able to distinguish
	 * if it should exit from L2 to L1 on EXTERNAL_INTERRUPT on
	 * pending interrupt or should re-inject an injected
	 * interrupt.
	 */
	if (!lapic_in_kernel(v))
		return v->arch.interrupt.injected;

	if (kvm_cpu_has_extint(v))
		return 1;

	return kvm_apic_has_interrupt(v) != -1;	/* LAPIC */
}