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
struct kvm_memory_slot {int dummy; } ;
struct kvm {int /*<<< orphan*/  mmu_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_mmu_zap_collapsible_spte ; 
 int /*<<< orphan*/  slot_handle_leaf (struct kvm*,struct kvm_memory_slot*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void kvm_mmu_zap_collapsible_sptes(struct kvm *kvm,
				   const struct kvm_memory_slot *memslot)
{
	/* FIXME: const-ify all uses of struct kvm_memory_slot.  */
	spin_lock(&kvm->mmu_lock);
	slot_handle_leaf(kvm, (struct kvm_memory_slot *)memslot,
			 kvm_mmu_zap_collapsible_spte, true);
	spin_unlock(&kvm->mmu_lock);
}