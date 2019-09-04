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
struct kvm_userspace_memory_region {unsigned long memory_size; } ;
struct kvm_memory_slot {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mmio_update; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kvmppc_core_commit_memory_region_hv(struct kvm *kvm,
				const struct kvm_userspace_memory_region *mem,
				const struct kvm_memory_slot *old,
				const struct kvm_memory_slot *new)
{
	unsigned long npages = mem->memory_size >> PAGE_SHIFT;

	/*
	 * If we are making a new memslot, it might make
	 * some address that was previously cached as emulated
	 * MMIO be no longer emulated MMIO, so invalidate
	 * all the caches of emulated MMIO translations.
	 */
	if (npages)
		atomic64_inc(&kvm->arch.mmio_update);
}