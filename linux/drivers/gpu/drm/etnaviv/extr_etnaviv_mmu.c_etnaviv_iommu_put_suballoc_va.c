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
struct drm_mm_node {int /*<<< orphan*/  size; int /*<<< orphan*/  start; } ;
struct etnaviv_vram_mapping {scalar_t__ use; struct drm_mm_node vram_node; } ;
struct etnaviv_iommu_context {int /*<<< orphan*/  lock; TYPE_1__* global; } ;
struct TYPE_2__ {scalar_t__ version; } ;

/* Variables and functions */
 scalar_t__ ETNAVIV_IOMMU_V1 ; 
 int /*<<< orphan*/  drm_mm_remove_node (struct drm_mm_node*) ; 
 int /*<<< orphan*/  etnaviv_context_unmap (struct etnaviv_iommu_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void etnaviv_iommu_put_suballoc_va(struct etnaviv_iommu_context *context,
		  struct etnaviv_vram_mapping *mapping)
{
	struct drm_mm_node *node = &mapping->vram_node;

	mutex_lock(&context->lock);
	mapping->use--;

	if (mapping->use > 0 || context->global->version == ETNAVIV_IOMMU_V1) {
		mutex_unlock(&context->lock);
		return;
	}

	etnaviv_context_unmap(context, node->start, node->size);
	drm_mm_remove_node(node);
	mutex_unlock(&context->lock);
}