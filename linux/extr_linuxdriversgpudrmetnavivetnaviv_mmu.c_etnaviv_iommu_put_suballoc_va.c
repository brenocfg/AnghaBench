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
typedef  int /*<<< orphan*/  u32 ;
struct etnaviv_iommu {scalar_t__ version; int /*<<< orphan*/  lock; int /*<<< orphan*/  domain; } ;
struct etnaviv_gpu {struct etnaviv_iommu* mmu; } ;
struct drm_mm_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ ETNAVIV_IOMMU_V2 ; 
 int /*<<< orphan*/  drm_mm_remove_node (struct drm_mm_node*) ; 
 int /*<<< orphan*/  etnaviv_domain_unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void etnaviv_iommu_put_suballoc_va(struct etnaviv_gpu *gpu,
				   struct drm_mm_node *vram_node, size_t size,
				   u32 iova)
{
	struct etnaviv_iommu *mmu = gpu->mmu;

	if (mmu->version == ETNAVIV_IOMMU_V2) {
		mutex_lock(&mmu->lock);
		etnaviv_domain_unmap(mmu->domain, iova, size);
		drm_mm_remove_node(vram_node);
		mutex_unlock(&mmu->lock);
	}
}