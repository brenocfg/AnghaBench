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
struct sg_table {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct TYPE_2__ {struct drm_device* dev; } ;
struct etnaviv_gem_object {int flags; struct sg_table* sgt; TYPE_1__ base; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int ETNA_BO_CACHE_MASK ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void etnaviv_gem_scatterlist_unmap(struct etnaviv_gem_object *etnaviv_obj)
{
	struct drm_device *dev = etnaviv_obj->base.dev;
	struct sg_table *sgt = etnaviv_obj->sgt;

	/*
	 * For non-cached buffers, ensure the new pages are clean
	 * because display controller, GPU, etc. are not coherent:
	 *
	 * WARNING: The DMA API does not support concurrent CPU
	 * and device access to the memory area.  With BIDIRECTIONAL,
	 * we will clean the cache lines which overlap the region,
	 * and invalidate all cache lines (partially) contained in
	 * the region.
	 *
	 * If you have dirty data in the overlapping cache lines,
	 * that will corrupt the GPU-written data.  If you have
	 * written into the remainder of the region, this can
	 * discard those writes.
	 */
	if (etnaviv_obj->flags & ETNA_BO_CACHE_MASK)
		dma_unmap_sg(dev->dev, sgt->sgl, sgt->nents, DMA_BIDIRECTIONAL);
}