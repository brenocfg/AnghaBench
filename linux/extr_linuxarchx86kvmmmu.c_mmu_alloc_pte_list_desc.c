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
struct pte_list_desc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mmu_pte_list_desc_cache; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 struct pte_list_desc* mmu_memory_cache_alloc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct pte_list_desc *mmu_alloc_pte_list_desc(struct kvm_vcpu *vcpu)
{
	return mmu_memory_cache_alloc(&vcpu->arch.mmu_pte_list_desc_cache);
}