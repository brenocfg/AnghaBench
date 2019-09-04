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
struct kvm_mmu_memory_cache {int dummy; } ;
struct TYPE_2__ {struct kvm_mmu_memory_cache mmu_pte_list_desc_cache; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int mmu_memory_cache_free_objects (struct kvm_mmu_memory_cache*) ; 

__attribute__((used)) static bool rmap_can_add(struct kvm_vcpu *vcpu)
{
	struct kvm_mmu_memory_cache *cache;

	cache = &vcpu->arch.mmu_pte_list_desc_cache;
	return mmu_memory_cache_free_objects(cache);
}