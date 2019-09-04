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
struct kvm_userspace_memory_region {int dummy; } ;
struct kvm_memory_slot {int dummy; } ;
struct kvm {int dummy; } ;

/* Variables and functions */

int kvmppc_core_prepare_memory_region(struct kvm *kvm,
				      struct kvm_memory_slot *memslot,
				      const struct kvm_userspace_memory_region *mem)
{
	return 0;
}