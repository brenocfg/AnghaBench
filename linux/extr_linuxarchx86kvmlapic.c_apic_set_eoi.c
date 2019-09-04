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
struct kvm_lapic {int /*<<< orphan*/  vcpu; } ;
struct TYPE_2__ {int /*<<< orphan*/  vec_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_EVENT ; 
 int /*<<< orphan*/  apic_clear_isr (int,struct kvm_lapic*) ; 
 int apic_find_highest_isr (struct kvm_lapic*) ; 
 int /*<<< orphan*/  apic_update_ppr (struct kvm_lapic*) ; 
 int /*<<< orphan*/  kvm_hv_synic_send_eoi (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kvm_ioapic_send_eoi (struct kvm_lapic*,int) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_kvm_eoi (struct kvm_lapic*,int) ; 
 TYPE_1__* vcpu_to_synic (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apic_set_eoi(struct kvm_lapic *apic)
{
	int vector = apic_find_highest_isr(apic);

	trace_kvm_eoi(apic, vector);

	/*
	 * Not every write EOI will has corresponding ISR,
	 * one example is when Kernel check timer on setup_IO_APIC
	 */
	if (vector == -1)
		return vector;

	apic_clear_isr(vector, apic);
	apic_update_ppr(apic);

	if (test_bit(vector, vcpu_to_synic(apic->vcpu)->vec_bitmap))
		kvm_hv_synic_send_eoi(apic->vcpu, vector);

	kvm_ioapic_send_eoi(apic, vector);
	kvm_make_request(KVM_REQ_EVENT, apic->vcpu);
	return vector;
}