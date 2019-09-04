#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct kvm_lapic_irq {int dummy; } ;
struct kvm_kernel_irq_routing_entry {int type; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EWOULDBLOCK ; 
#define  KVM_IRQ_ROUTING_HV_SINT 129 
#define  KVM_IRQ_ROUTING_MSI 128 
 int kvm_hv_set_sint (struct kvm_kernel_irq_routing_entry*,struct kvm*,int,int,int) ; 
 int /*<<< orphan*/  kvm_irq_delivery_to_apic_fast (struct kvm*,int /*<<< orphan*/ *,struct kvm_lapic_irq*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_msi_route_invalid (struct kvm*,struct kvm_kernel_irq_routing_entry*) ; 
 int /*<<< orphan*/  kvm_set_msi_irq (struct kvm*,struct kvm_kernel_irq_routing_entry*,struct kvm_lapic_irq*) ; 

int kvm_arch_set_irq_inatomic(struct kvm_kernel_irq_routing_entry *e,
			      struct kvm *kvm, int irq_source_id, int level,
			      bool line_status)
{
	struct kvm_lapic_irq irq;
	int r;

	switch (e->type) {
	case KVM_IRQ_ROUTING_HV_SINT:
		return kvm_hv_set_sint(e, kvm, irq_source_id, level,
				       line_status);

	case KVM_IRQ_ROUTING_MSI:
		if (kvm_msi_route_invalid(kvm, e))
			return -EINVAL;

		kvm_set_msi_irq(kvm, e, &irq);

		if (kvm_irq_delivery_to_apic_fast(kvm, NULL, &irq, &r, NULL))
			return r;
		break;

	default:
		break;
	}

	return -EWOULDBLOCK;
}