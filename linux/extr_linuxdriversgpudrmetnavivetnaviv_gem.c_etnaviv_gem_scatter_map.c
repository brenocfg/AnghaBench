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
 int /*<<< orphan*/  dma_map_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void etnaviv_gem_scatter_map(struct etnaviv_gem_object *etnaviv_obj)
{
	struct drm_device *dev = etnaviv_obj->base.dev;
	struct sg_table *sgt = etnaviv_obj->sgt;

	/*
	 * For non-cached buffers, ensure the new pages are clean
	 * because display controller, GPU, etc. are not coherent.
	 */
	if (etnaviv_obj->flags & ETNA_BO_CACHE_MASK)
		dma_map_sg(dev->dev, sgt->sgl, sgt->nents, DMA_BIDIRECTIONAL);
}