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
struct kvm_userspace_memory_region {int userspace_addr; int memory_size; scalar_t__ guest_phys_addr; } ;
struct kvm_memory_slot {int dummy; } ;
struct TYPE_2__ {scalar_t__ mem_limit; } ;
struct kvm {TYPE_1__ arch; } ;
typedef  enum kvm_mr_change { ____Placeholder_kvm_mr_change } kvm_mr_change ;

/* Variables and functions */
 int EINVAL ; 

int kvm_arch_prepare_memory_region(struct kvm *kvm,
				   struct kvm_memory_slot *memslot,
				   const struct kvm_userspace_memory_region *mem,
				   enum kvm_mr_change change)
{
	/* A few sanity checks. We can have memory slots which have to be
	   located/ended at a segment boundary (1MB). The memory in userland is
	   ok to be fragmented into various different vmas. It is okay to mmap()
	   and munmap() stuff in this slot after doing this call at any time */

	if (mem->userspace_addr & 0xffffful)
		return -EINVAL;

	if (mem->memory_size & 0xffffful)
		return -EINVAL;

	if (mem->guest_phys_addr + mem->memory_size > kvm->arch.mem_limit)
		return -EINVAL;

	return 0;
}