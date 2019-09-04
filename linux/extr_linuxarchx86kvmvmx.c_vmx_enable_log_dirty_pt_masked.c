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
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_mmu_clear_dirty_pt_masked (struct kvm*,struct kvm_memory_slot*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void vmx_enable_log_dirty_pt_masked(struct kvm *kvm,
					   struct kvm_memory_slot *memslot,
					   gfn_t offset, unsigned long mask)
{
	kvm_mmu_clear_dirty_pt_masked(kvm, memslot, offset, mask);
}