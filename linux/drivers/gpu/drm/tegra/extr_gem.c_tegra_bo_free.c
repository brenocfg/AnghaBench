#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  size; } ;
struct tegra_bo {int /*<<< orphan*/  paddr; scalar_t__ vaddr; TYPE_3__ gem; TYPE_1__* sgt; scalar_t__ pages; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  dma_free_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_put_pages (TYPE_3__*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  sg_free_table (TYPE_1__*) ; 

__attribute__((used)) static void tegra_bo_free(struct drm_device *drm, struct tegra_bo *bo)
{
	if (bo->pages) {
		dma_unmap_sg(drm->dev, bo->sgt->sgl, bo->sgt->nents,
			     DMA_FROM_DEVICE);
		drm_gem_put_pages(&bo->gem, bo->pages, true, true);
		sg_free_table(bo->sgt);
		kfree(bo->sgt);
	} else if (bo->vaddr) {
		dma_free_wc(drm->dev, bo->gem.size, bo->vaddr, bo->paddr);
	}
}