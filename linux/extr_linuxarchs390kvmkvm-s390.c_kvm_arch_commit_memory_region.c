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
struct kvm_userspace_memory_region {scalar_t__ userspace_addr; int guest_phys_addr; int memory_size; } ;
struct kvm_memory_slot {scalar_t__ userspace_addr; int base_gfn; int npages; } ;
struct TYPE_2__ {int /*<<< orphan*/  gmap; } ;
struct kvm {TYPE_1__ arch; } ;
typedef  enum kvm_mr_change { ____Placeholder_kvm_mr_change } kvm_mr_change ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int gmap_map_segment (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

void kvm_arch_commit_memory_region(struct kvm *kvm,
				const struct kvm_userspace_memory_region *mem,
				const struct kvm_memory_slot *old,
				const struct kvm_memory_slot *new,
				enum kvm_mr_change change)
{
	int rc;

	/* If the basics of the memslot do not change, we do not want
	 * to update the gmap. Every update causes several unnecessary
	 * segment translation exceptions. This is usually handled just
	 * fine by the normal fault handler + gmap, but it will also
	 * cause faults on the prefix page of running guest CPUs.
	 */
	if (old->userspace_addr == mem->userspace_addr &&
	    old->base_gfn * PAGE_SIZE == mem->guest_phys_addr &&
	    old->npages * PAGE_SIZE == mem->memory_size)
		return;

	rc = gmap_map_segment(kvm->arch.gmap, mem->userspace_addr,
		mem->guest_phys_addr, mem->memory_size);
	if (rc)
		pr_warn("failed to commit memory region\n");
	return;
}