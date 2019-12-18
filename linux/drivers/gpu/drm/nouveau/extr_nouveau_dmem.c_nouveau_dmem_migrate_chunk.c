#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nouveau_fence {int dummy; } ;
struct nouveau_drm {TYPE_3__* dev; TYPE_2__* dmem; } ;
struct migrate_vma {unsigned long start; unsigned long end; scalar_t__* dst; int /*<<< orphan*/ * src; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  chan; } ;
struct TYPE_5__ {TYPE_1__ migrate; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  migrate_vma_finalize (struct migrate_vma*) ; 
 int /*<<< orphan*/  migrate_vma_pages (struct migrate_vma*) ; 
 int /*<<< orphan*/  nouveau_dmem_fence_done (struct nouveau_fence**) ; 
 scalar_t__ nouveau_dmem_migrate_copy_one (struct nouveau_drm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_fence_new (int /*<<< orphan*/ ,int,struct nouveau_fence**) ; 

__attribute__((used)) static void nouveau_dmem_migrate_chunk(struct nouveau_drm *drm,
		struct migrate_vma *args, dma_addr_t *dma_addrs)
{
	struct nouveau_fence *fence;
	unsigned long addr = args->start, nr_dma = 0, i;

	for (i = 0; addr < args->end; i++) {
		args->dst[i] = nouveau_dmem_migrate_copy_one(drm, args->src[i],
				dma_addrs + nr_dma);
		if (args->dst[i])
			nr_dma++;
		addr += PAGE_SIZE;
	}

	nouveau_fence_new(drm->dmem->migrate.chan, false, &fence);
	migrate_vma_pages(args);
	nouveau_dmem_fence_done(&fence);

	while (nr_dma--) {
		dma_unmap_page(drm->dev->dev, dma_addrs[nr_dma], PAGE_SIZE,
				DMA_BIDIRECTIONAL);
	}
	/*
	 * FIXME optimization: update GPU page table to point to newly migrated
	 * memory.
	 */
	migrate_vma_finalize(args);
}