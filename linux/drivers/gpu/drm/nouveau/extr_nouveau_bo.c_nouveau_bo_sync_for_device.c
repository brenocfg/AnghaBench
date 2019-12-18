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
struct TYPE_6__ {int num_pages; } ;
struct ttm_dma_tt {int /*<<< orphan*/ * dma_address; TYPE_3__ ttm; } ;
struct nouveau_drm {TYPE_1__* dev; } ;
struct TYPE_5__ {scalar_t__ ttm; int /*<<< orphan*/  bdev; } ;
struct nouveau_bo {scalar_t__ force_coherent; TYPE_2__ bo; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nouveau_drm* nouveau_bdev (int /*<<< orphan*/ ) ; 

void
nouveau_bo_sync_for_device(struct nouveau_bo *nvbo)
{
	struct nouveau_drm *drm = nouveau_bdev(nvbo->bo.bdev);
	struct ttm_dma_tt *ttm_dma = (struct ttm_dma_tt *)nvbo->bo.ttm;
	int i;

	if (!ttm_dma)
		return;

	/* Don't waste time looping if the object is coherent */
	if (nvbo->force_coherent)
		return;

	for (i = 0; i < ttm_dma->ttm.num_pages; i++)
		dma_sync_single_for_device(drm->dev->dev,
					   ttm_dma->dma_address[i],
					   PAGE_SIZE, DMA_TO_DEVICE);
}