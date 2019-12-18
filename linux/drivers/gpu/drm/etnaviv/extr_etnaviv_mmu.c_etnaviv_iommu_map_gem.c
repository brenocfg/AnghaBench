#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct sg_table {int nents; int /*<<< orphan*/  sgl; } ;
struct drm_mm_node {int start; } ;
struct etnaviv_vram_mapping {int iova; int /*<<< orphan*/  mmu_node; struct drm_mm_node vram_node; } ;
struct etnaviv_iommu_context {int /*<<< orphan*/  lock; int /*<<< orphan*/  flush_seq; int /*<<< orphan*/  mappings; TYPE_1__* global; } ;
struct TYPE_4__ {int /*<<< orphan*/  size; } ;
struct etnaviv_gem_object {int flags; TYPE_2__ base; int /*<<< orphan*/  lock; struct sg_table* sgt; } ;
struct TYPE_3__ {scalar_t__ version; } ;

/* Variables and functions */
 scalar_t__ ETNAVIV_IOMMU_V1 ; 
 int ETNAVIV_PROT_READ ; 
 int ETNAVIV_PROT_WRITE ; 
 int ETNA_BO_FORCE_MMU ; 
 int /*<<< orphan*/  drm_mm_remove_node (struct drm_mm_node*) ; 
 int etnaviv_iommu_find_iova (struct etnaviv_iommu_context*,struct drm_mm_node*,int /*<<< orphan*/ ) ; 
 int etnaviv_iommu_insert_exact (struct etnaviv_iommu_context*,struct drm_mm_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int etnaviv_iommu_map (struct etnaviv_iommu_context*,int,struct sg_table*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sg_dma_address (int /*<<< orphan*/ ) ; 
 int sg_dma_len (int /*<<< orphan*/ ) ; 

int etnaviv_iommu_map_gem(struct etnaviv_iommu_context *context,
	struct etnaviv_gem_object *etnaviv_obj, u32 memory_base,
	struct etnaviv_vram_mapping *mapping, u64 va)
{
	struct sg_table *sgt = etnaviv_obj->sgt;
	struct drm_mm_node *node;
	int ret;

	lockdep_assert_held(&etnaviv_obj->lock);

	mutex_lock(&context->lock);

	/* v1 MMU can optimize single entry (contiguous) scatterlists */
	if (context->global->version == ETNAVIV_IOMMU_V1 &&
	    sgt->nents == 1 && !(etnaviv_obj->flags & ETNA_BO_FORCE_MMU)) {
		u32 iova;

		iova = sg_dma_address(sgt->sgl) - memory_base;
		if (iova < 0x80000000 - sg_dma_len(sgt->sgl)) {
			mapping->iova = iova;
			list_add_tail(&mapping->mmu_node, &context->mappings);
			ret = 0;
			goto unlock;
		}
	}

	node = &mapping->vram_node;

	if (va)
		ret = etnaviv_iommu_insert_exact(context, node,
						 etnaviv_obj->base.size, va);
	else
		ret = etnaviv_iommu_find_iova(context, node,
					      etnaviv_obj->base.size);
	if (ret < 0)
		goto unlock;

	mapping->iova = node->start;
	ret = etnaviv_iommu_map(context, node->start, sgt, etnaviv_obj->base.size,
				ETNAVIV_PROT_READ | ETNAVIV_PROT_WRITE);

	if (ret < 0) {
		drm_mm_remove_node(node);
		goto unlock;
	}

	list_add_tail(&mapping->mmu_node, &context->mappings);
	context->flush_seq++;
unlock:
	mutex_unlock(&context->lock);

	return ret;
}