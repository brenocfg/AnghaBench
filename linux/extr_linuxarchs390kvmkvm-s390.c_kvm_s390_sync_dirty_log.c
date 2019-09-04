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
struct kvm_memory_slot {scalar_t__ base_gfn; scalar_t__ npages; } ;
struct TYPE_2__ {struct gmap* gmap; } ;
struct kvm {TYPE_1__ arch; } ;
struct gmap {int dummy; } ;
typedef  scalar_t__ gfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_BITMAP (int /*<<< orphan*/ ,int) ; 
 int _PAGE_ENTRIES ; 
 int /*<<< orphan*/  bitmap ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ fatal_signal_pending (int /*<<< orphan*/ ) ; 
 unsigned long gfn_to_gpa (scalar_t__) ; 
 unsigned long gfn_to_hva_memslot (struct kvm_memory_slot*,scalar_t__) ; 
 int /*<<< orphan*/  gmap_sync_dirty_log_pmd (struct gmap*,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 scalar_t__ kvm_is_error_hva (unsigned long) ; 
 int /*<<< orphan*/  mark_page_dirty (struct kvm*,scalar_t__) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvm_s390_sync_dirty_log(struct kvm *kvm,
				    struct kvm_memory_slot *memslot)
{
	int i;
	gfn_t cur_gfn, last_gfn;
	unsigned long gaddr, vmaddr;
	struct gmap *gmap = kvm->arch.gmap;
	DECLARE_BITMAP(bitmap, _PAGE_ENTRIES);

	/* Loop over all guest segments */
	cur_gfn = memslot->base_gfn;
	last_gfn = memslot->base_gfn + memslot->npages;
	for (; cur_gfn <= last_gfn; cur_gfn += _PAGE_ENTRIES) {
		gaddr = gfn_to_gpa(cur_gfn);
		vmaddr = gfn_to_hva_memslot(memslot, cur_gfn);
		if (kvm_is_error_hva(vmaddr))
			continue;

		bitmap_zero(bitmap, _PAGE_ENTRIES);
		gmap_sync_dirty_log_pmd(gmap, bitmap, gaddr, vmaddr);
		for (i = 0; i < _PAGE_ENTRIES; i++) {
			if (test_bit(i, bitmap))
				mark_page_dirty(kvm, cur_gfn + i);
		}

		if (fatal_signal_pending(current))
			return;
		cond_resched();
	}
}