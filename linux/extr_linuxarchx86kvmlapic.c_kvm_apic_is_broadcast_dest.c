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
struct kvm_lapic_irq {scalar_t__ dest_id; } ;
struct kvm_lapic {int dummy; } ;
struct kvm_apic_map {scalar_t__ mode; } ;
struct TYPE_2__ {scalar_t__ x2apic_broadcast_quirk_disabled; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 scalar_t__ APIC_BROADCAST ; 
 scalar_t__ KVM_APIC_MODE_X2APIC ; 
 scalar_t__ X2APIC_BROADCAST ; 
 scalar_t__ apic_x2apic_mode (struct kvm_lapic*) ; 

__attribute__((used)) static bool kvm_apic_is_broadcast_dest(struct kvm *kvm, struct kvm_lapic **src,
		struct kvm_lapic_irq *irq, struct kvm_apic_map *map)
{
	if (kvm->arch.x2apic_broadcast_quirk_disabled) {
		if ((irq->dest_id == APIC_BROADCAST &&
				map->mode != KVM_APIC_MODE_X2APIC))
			return true;
		if (irq->dest_id == X2APIC_BROADCAST)
			return true;
	} else {
		bool x2apic_ipi = src && *src && apic_x2apic_mode(*src);
		if (irq->dest_id == (x2apic_ipi ?
		                     X2APIC_BROADCAST : APIC_BROADCAST))
			return true;
	}

	return false;
}