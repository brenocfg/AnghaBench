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
typedef  scalar_t__ u32 ;
struct etnaviv_iommu {scalar_t__ version; int need_flush; int /*<<< orphan*/  lock; int /*<<< orphan*/  domain; } ;
struct etnaviv_gpu {struct etnaviv_iommu* mmu; scalar_t__ memory_base; } ;
struct drm_mm_node {scalar_t__ start; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 scalar_t__ ETNAVIV_IOMMU_V1 ; 
 int /*<<< orphan*/  ETNAVIV_PROT_READ ; 
 int /*<<< orphan*/  drm_mm_remove_node (struct drm_mm_node*) ; 
 int etnaviv_domain_map (int /*<<< orphan*/ ,scalar_t__,scalar_t__,size_t,int /*<<< orphan*/ ) ; 
 int etnaviv_iommu_find_iova (struct etnaviv_iommu*,struct drm_mm_node*,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int etnaviv_iommu_get_suballoc_va(struct etnaviv_gpu *gpu, dma_addr_t paddr,
				  struct drm_mm_node *vram_node, size_t size,
				  u32 *iova)
{
	struct etnaviv_iommu *mmu = gpu->mmu;

	if (mmu->version == ETNAVIV_IOMMU_V1) {
		*iova = paddr - gpu->memory_base;
		return 0;
	} else {
		int ret;

		mutex_lock(&mmu->lock);
		ret = etnaviv_iommu_find_iova(mmu, vram_node, size);
		if (ret < 0) {
			mutex_unlock(&mmu->lock);
			return ret;
		}
		ret = etnaviv_domain_map(mmu->domain, vram_node->start, paddr,
					 size, ETNAVIV_PROT_READ);
		if (ret < 0) {
			drm_mm_remove_node(vram_node);
			mutex_unlock(&mmu->lock);
			return ret;
		}
		gpu->mmu->need_flush = true;
		mutex_unlock(&mmu->lock);

		*iova = (u32)vram_node->start;
		return 0;
	}
}