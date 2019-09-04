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
struct TYPE_3__ {int nr; } ;
struct TYPE_4__ {TYPE_1__ interrupt; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;

/* Variables and functions */
 int kvm_cpu_get_extint (struct kvm_vcpu*) ; 
 int kvm_get_apic_interrupt (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  lapic_in_kernel (struct kvm_vcpu*) ; 

int kvm_cpu_get_interrupt(struct kvm_vcpu *v)
{
	int vector;

	if (!lapic_in_kernel(v))
		return v->arch.interrupt.nr;

	vector = kvm_cpu_get_extint(v);

	if (vector != -1)
		return vector;			/* PIC */

	return kvm_get_apic_interrupt(v);	/* APIC */
}