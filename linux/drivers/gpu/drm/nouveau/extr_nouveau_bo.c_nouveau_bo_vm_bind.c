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
typedef  int u64 ;
struct ttm_mem_reg {int start; scalar_t__ mem_type; int /*<<< orphan*/  size; } ;
struct ttm_buffer_object {int /*<<< orphan*/  bdev; } ;
struct nouveau_drm_tile {int dummy; } ;
struct TYPE_4__ {scalar_t__ family; } ;
struct TYPE_5__ {TYPE_1__ info; } ;
struct TYPE_6__ {TYPE_2__ device; } ;
struct nouveau_drm {TYPE_3__ client; struct drm_device* dev; } ;
struct nouveau_bo {int /*<<< orphan*/  zeta; int /*<<< orphan*/  mode; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ NV_DEVICE_INFO_V0_CELSIUS ; 
 int PAGE_SHIFT ; 
 scalar_t__ TTM_PL_VRAM ; 
 struct nouveau_drm* nouveau_bdev (int /*<<< orphan*/ ) ; 
 struct nouveau_bo* nouveau_bo (struct ttm_buffer_object*) ; 
 struct nouveau_drm_tile* nv10_bo_set_tiling (struct drm_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nouveau_bo_vm_bind(struct ttm_buffer_object *bo, struct ttm_mem_reg *new_reg,
		   struct nouveau_drm_tile **new_tile)
{
	struct nouveau_drm *drm = nouveau_bdev(bo->bdev);
	struct drm_device *dev = drm->dev;
	struct nouveau_bo *nvbo = nouveau_bo(bo);
	u64 offset = new_reg->start << PAGE_SHIFT;

	*new_tile = NULL;
	if (new_reg->mem_type != TTM_PL_VRAM)
		return 0;

	if (drm->client.device.info.family >= NV_DEVICE_INFO_V0_CELSIUS) {
		*new_tile = nv10_bo_set_tiling(dev, offset, new_reg->size,
					       nvbo->mode, nvbo->zeta);
	}

	return 0;
}