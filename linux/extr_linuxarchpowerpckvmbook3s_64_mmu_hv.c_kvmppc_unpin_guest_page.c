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
struct page {int dummy; } ;
struct kvm_memory_slot {scalar_t__ dirty_bitmap; scalar_t__ base_gfn; } ;
struct kvm {int /*<<< orphan*/  srcu; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 struct kvm_memory_slot* gfn_to_memslot (struct kvm*,unsigned long) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_bit_le (scalar_t__,scalar_t__) ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 
 struct page* virt_to_page (void*) ; 

void kvmppc_unpin_guest_page(struct kvm *kvm, void *va, unsigned long gpa,
			     bool dirty)
{
	struct page *page = virt_to_page(va);
	struct kvm_memory_slot *memslot;
	unsigned long gfn;
	int srcu_idx;

	put_page(page);

	if (!dirty)
		return;

	/* We need to mark this page dirty in the memslot dirty_bitmap, if any */
	gfn = gpa >> PAGE_SHIFT;
	srcu_idx = srcu_read_lock(&kvm->srcu);
	memslot = gfn_to_memslot(kvm, gfn);
	if (memslot && memslot->dirty_bitmap)
		set_bit_le(gfn - memslot->base_gfn, memslot->dirty_bitmap);
	srcu_read_unlock(&kvm->srcu, srcu_idx);
}