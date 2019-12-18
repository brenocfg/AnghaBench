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
struct TYPE_2__ {int /*<<< orphan*/  resv; } ;
struct ttm_buffer_object {TYPE_1__ base; int /*<<< orphan*/  bdev; } ;
struct nouveau_drm_tile {int dummy; } ;
struct nouveau_drm {struct drm_device* dev; } ;
struct drm_device {int dummy; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 struct dma_fence* dma_resv_get_excl (int /*<<< orphan*/ ) ; 
 struct nouveau_drm* nouveau_bdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv10_bo_put_tile_region (struct drm_device*,struct nouveau_drm_tile*,struct dma_fence*) ; 

__attribute__((used)) static void
nouveau_bo_vm_cleanup(struct ttm_buffer_object *bo,
		      struct nouveau_drm_tile *new_tile,
		      struct nouveau_drm_tile **old_tile)
{
	struct nouveau_drm *drm = nouveau_bdev(bo->bdev);
	struct drm_device *dev = drm->dev;
	struct dma_fence *fence = dma_resv_get_excl(bo->base.resv);

	nv10_bo_put_tile_region(dev, *old_tile, fence);
	*old_tile = new_tile;
}