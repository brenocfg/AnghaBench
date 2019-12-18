#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sg_table {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct TYPE_5__ {struct sg_table* pages; } ;
struct TYPE_7__ {int size; TYPE_4__* dev; } ;
struct drm_i915_gem_object {TYPE_1__ mm; TYPE_3__ base; } ;
struct TYPE_8__ {TYPE_2__* pdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_ATTR_NO_WARN ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int I915_SHRINK_BOUND ; 
 int I915_SHRINK_UNBOUND ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 scalar_t__ dma_map_sg_attrs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ i915_gem_shrink (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  to_i915 (TYPE_4__*) ; 

int i915_gem_gtt_prepare_pages(struct drm_i915_gem_object *obj,
			       struct sg_table *pages)
{
	do {
		if (dma_map_sg_attrs(&obj->base.dev->pdev->dev,
				     pages->sgl, pages->nents,
				     PCI_DMA_BIDIRECTIONAL,
				     DMA_ATTR_NO_WARN))
			return 0;

		/*
		 * If the DMA remap fails, one cause can be that we have
		 * too many objects pinned in a small remapping table,
		 * such as swiotlb. Incrementally purge all other objects and
		 * try again - if there are no more pages to remove from
		 * the DMA remapper, i915_gem_shrink will return 0.
		 */
		GEM_BUG_ON(obj->mm.pages == pages);
	} while (i915_gem_shrink(to_i915(obj->base.dev),
				 obj->base.size >> PAGE_SHIFT, NULL,
				 I915_SHRINK_BOUND |
				 I915_SHRINK_UNBOUND));

	return -ENOSPC;
}