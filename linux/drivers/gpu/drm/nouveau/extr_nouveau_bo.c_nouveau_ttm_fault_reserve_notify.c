#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_12__ {scalar_t__ mem_type; scalar_t__ start; scalar_t__ num_pages; } ;
struct ttm_buffer_object {TYPE_4__ mem; int /*<<< orphan*/  bdev; } ;
struct nvkm_device {TYPE_1__* func; } ;
struct TYPE_10__ {scalar_t__ family; } ;
struct TYPE_16__ {TYPE_2__ info; } ;
struct TYPE_11__ {TYPE_8__ device; } ;
struct nouveau_drm {TYPE_3__ client; } ;
struct TYPE_14__ {int num_placement; int num_busy_placement; } ;
struct nouveau_bo {TYPE_7__* busy_placements; TYPE_6__ placement; TYPE_5__* placements; int /*<<< orphan*/  kind; } ;
struct TYPE_15__ {scalar_t__ lpfn; scalar_t__ fpfn; } ;
struct TYPE_13__ {scalar_t__ lpfn; scalar_t__ fpfn; } ;
struct TYPE_9__ {scalar_t__ (* resource_size ) (struct nvkm_device*,int) ;} ;

/* Variables and functions */
 scalar_t__ NV_DEVICE_INFO_V0_TESLA ; 
 scalar_t__ PAGE_SHIFT ; 
 int /*<<< orphan*/  TTM_PL_FLAG_VRAM ; 
 scalar_t__ TTM_PL_SYSTEM ; 
 int /*<<< orphan*/  TTM_PL_TT ; 
 scalar_t__ TTM_PL_VRAM ; 
 struct nouveau_drm* nouveau_bdev (int /*<<< orphan*/ ) ; 
 struct nouveau_bo* nouveau_bo (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  nouveau_bo_placement_set (struct nouveau_bo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nouveau_bo_validate (struct nouveau_bo*,int,int) ; 
 struct nvkm_device* nvxx_device (TYPE_8__*) ; 
 scalar_t__ stub1 (struct nvkm_device*,int) ; 

__attribute__((used)) static int
nouveau_ttm_fault_reserve_notify(struct ttm_buffer_object *bo)
{
	struct nouveau_drm *drm = nouveau_bdev(bo->bdev);
	struct nouveau_bo *nvbo = nouveau_bo(bo);
	struct nvkm_device *device = nvxx_device(&drm->client.device);
	u32 mappable = device->func->resource_size(device, 1) >> PAGE_SHIFT;
	int i, ret;

	/* as long as the bo isn't in vram, and isn't tiled, we've got
	 * nothing to do here.
	 */
	if (bo->mem.mem_type != TTM_PL_VRAM) {
		if (drm->client.device.info.family < NV_DEVICE_INFO_V0_TESLA ||
		    !nvbo->kind)
			return 0;

		if (bo->mem.mem_type == TTM_PL_SYSTEM) {
			nouveau_bo_placement_set(nvbo, TTM_PL_TT, 0);

			ret = nouveau_bo_validate(nvbo, false, false);
			if (ret)
				return ret;
		}
		return 0;
	}

	/* make sure bo is in mappable vram */
	if (drm->client.device.info.family >= NV_DEVICE_INFO_V0_TESLA ||
	    bo->mem.start + bo->mem.num_pages < mappable)
		return 0;

	for (i = 0; i < nvbo->placement.num_placement; ++i) {
		nvbo->placements[i].fpfn = 0;
		nvbo->placements[i].lpfn = mappable;
	}

	for (i = 0; i < nvbo->placement.num_busy_placement; ++i) {
		nvbo->busy_placements[i].fpfn = 0;
		nvbo->busy_placements[i].lpfn = mappable;
	}

	nouveau_bo_placement_set(nvbo, TTM_PL_FLAG_VRAM, 0);
	return nouveau_bo_validate(nvbo, false, false);
}