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
struct kvm_lapic {int /*<<< orphan*/  vcpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_EVENT ; 
 int /*<<< orphan*/  kvm_ioapic_send_eoi (struct kvm_lapic*,int) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_kvm_eoi (struct kvm_lapic*,int) ; 

void kvm_apic_set_eoi_accelerated(struct kvm_vcpu *vcpu, int vector)
{
	struct kvm_lapic *apic = vcpu->arch.apic;

	trace_kvm_eoi(apic, vector);

	kvm_ioapic_send_eoi(apic, vector);
	kvm_make_request(KVM_REQ_EVENT, apic->vcpu);
}