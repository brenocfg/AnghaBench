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
struct kvm_vcpu {int dummy; } ;
struct kvm_lapic_irq {scalar_t__ shorthand; } ;
struct kvm_lapic {struct kvm_vcpu* vcpu; } ;
struct kvm_apic_map {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  apic_map; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 unsigned long find_first_bit (unsigned long*,int) ; 
 int hweight16 (unsigned long) ; 
 scalar_t__ kvm_apic_map_get_dest_lapic (struct kvm*,int /*<<< orphan*/ *,struct kvm_lapic_irq*,struct kvm_apic_map*,struct kvm_lapic***,unsigned long*) ; 
 struct kvm_apic_map* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

bool kvm_intr_is_single_vcpu_fast(struct kvm *kvm, struct kvm_lapic_irq *irq,
			struct kvm_vcpu **dest_vcpu)
{
	struct kvm_apic_map *map;
	unsigned long bitmap;
	struct kvm_lapic **dst = NULL;
	bool ret = false;

	if (irq->shorthand)
		return false;

	rcu_read_lock();
	map = rcu_dereference(kvm->arch.apic_map);

	if (kvm_apic_map_get_dest_lapic(kvm, NULL, irq, map, &dst, &bitmap) &&
			hweight16(bitmap) == 1) {
		unsigned long i = find_first_bit(&bitmap, 16);

		if (dst[i]) {
			*dest_vcpu = dst[i]->vcpu;
			ret = true;
		}
	}

	rcu_read_unlock();
	return ret;
}