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
struct pte_list_desc {int dummy; } ;
struct kvm_mmu_page {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SLAB_ACCOUNT ; 
 void* kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_mmu_reset_all_pte_masks () ; 
 int /*<<< orphan*/  kvm_total_used_mmu_pages ; 
 int /*<<< orphan*/  mmu_destroy_caches () ; 
 void* mmu_page_header_cache ; 
 int /*<<< orphan*/  mmu_shrinker ; 
 scalar_t__ percpu_counter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* pte_list_desc_cache ; 
 int register_shrinker (int /*<<< orphan*/ *) ; 

int kvm_mmu_module_init(void)
{
	int ret = -ENOMEM;

	kvm_mmu_reset_all_pte_masks();

	pte_list_desc_cache = kmem_cache_create("pte_list_desc",
					    sizeof(struct pte_list_desc),
					    0, SLAB_ACCOUNT, NULL);
	if (!pte_list_desc_cache)
		goto out;

	mmu_page_header_cache = kmem_cache_create("kvm_mmu_page_header",
						  sizeof(struct kvm_mmu_page),
						  0, SLAB_ACCOUNT, NULL);
	if (!mmu_page_header_cache)
		goto out;

	if (percpu_counter_init(&kvm_total_used_mmu_pages, 0, GFP_KERNEL))
		goto out;

	ret = register_shrinker(&mmu_shrinker);
	if (ret)
		goto out;

	return 0;

out:
	mmu_destroy_caches();
	return ret;
}