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
struct TYPE_2__ {unsigned long* rmap; } ;
struct kvm_memory_slot {unsigned long npages; TYPE_1__ arch; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int kvm_test_clear_dirty_npages (struct kvm*,unsigned long*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  set_dirty_bits (unsigned long*,unsigned long,int) ; 

long kvmppc_hv_get_dirty_log_hpt(struct kvm *kvm,
			struct kvm_memory_slot *memslot, unsigned long *map)
{
	unsigned long i;
	unsigned long *rmapp;

	preempt_disable();
	rmapp = memslot->arch.rmap;
	for (i = 0; i < memslot->npages; ++i) {
		int npages = kvm_test_clear_dirty_npages(kvm, rmapp);
		/*
		 * Note that if npages > 0 then i must be a multiple of npages,
		 * since we always put huge-page HPTEs in the rmap chain
		 * corresponding to their page base address.
		 */
		if (npages)
			set_dirty_bits(map, i, npages);
		++rmapp;
	}
	preempt_enable();
	return 0;
}