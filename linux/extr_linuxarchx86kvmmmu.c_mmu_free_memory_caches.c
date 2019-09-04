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
struct TYPE_2__ {int /*<<< orphan*/  mmu_page_header_cache; int /*<<< orphan*/  mmu_page_cache; int /*<<< orphan*/  mmu_pte_list_desc_cache; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmu_free_memory_cache (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_free_memory_cache_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmu_page_header_cache ; 
 int /*<<< orphan*/  pte_list_desc_cache ; 

__attribute__((used)) static void mmu_free_memory_caches(struct kvm_vcpu *vcpu)
{
	mmu_free_memory_cache(&vcpu->arch.mmu_pte_list_desc_cache,
				pte_list_desc_cache);
	mmu_free_memory_cache_page(&vcpu->arch.mmu_page_cache);
	mmu_free_memory_cache(&vcpu->arch.mmu_page_header_cache,
				mmu_page_header_cache);
}