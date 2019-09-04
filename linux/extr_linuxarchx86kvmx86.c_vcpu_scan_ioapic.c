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
struct TYPE_3__ {int load_eoi_exitmap_pending; int /*<<< orphan*/  ioapic_handled_vectors; scalar_t__ apicv_active; } ;
struct kvm_vcpu {TYPE_1__ arch; int /*<<< orphan*/  kvm; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* sync_pir_to_irr ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_LOAD_EOI_EXITMAP ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ioapic_in_kernel (int /*<<< orphan*/ ) ; 
 scalar_t__ irqchip_split (int /*<<< orphan*/ ) ; 
 scalar_t__ is_guest_mode (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_apic_present (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_ioapic_scan_entry (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_scan_ioapic_routes (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 TYPE_2__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*) ; 

__attribute__((used)) static void vcpu_scan_ioapic(struct kvm_vcpu *vcpu)
{
	if (!kvm_apic_present(vcpu))
		return;

	bitmap_zero(vcpu->arch.ioapic_handled_vectors, 256);

	if (irqchip_split(vcpu->kvm))
		kvm_scan_ioapic_routes(vcpu, vcpu->arch.ioapic_handled_vectors);
	else {
		if (vcpu->arch.apicv_active)
			kvm_x86_ops->sync_pir_to_irr(vcpu);
		if (ioapic_in_kernel(vcpu->kvm))
			kvm_ioapic_scan_entry(vcpu, vcpu->arch.ioapic_handled_vectors);
	}

	if (is_guest_mode(vcpu))
		vcpu->arch.load_eoi_exitmap_pending = true;
	else
		kvm_make_request(KVM_REQ_LOAD_EOI_EXITMAP, vcpu);
}