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
struct kvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_mmu_slot_largepage_remove_write_access (struct kvm*,struct kvm_memory_slot*) ; 
 int /*<<< orphan*/  kvm_mmu_slot_leaf_clear_dirty (struct kvm*,struct kvm_memory_slot*) ; 

__attribute__((used)) static void vmx_slot_enable_log_dirty(struct kvm *kvm,
				     struct kvm_memory_slot *slot)
{
	kvm_mmu_slot_leaf_clear_dirty(kvm, slot);
	kvm_mmu_slot_largepage_remove_write_access(kvm, slot);
}