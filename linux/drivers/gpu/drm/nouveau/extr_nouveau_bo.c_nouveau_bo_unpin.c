#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int mem_type; int /*<<< orphan*/  size; int /*<<< orphan*/  placement; } ;
struct ttm_buffer_object {TYPE_2__ mem; int /*<<< orphan*/  bdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  gart_available; int /*<<< orphan*/  vram_available; } ;
struct nouveau_drm {TYPE_1__ gem; } ;
struct nouveau_bo {int pin_refcnt; struct ttm_buffer_object bo; } ;

/* Variables and functions */
#define  TTM_PL_TT 129 
#define  TTM_PL_VRAM 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct nouveau_drm* nouveau_bdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_bo_placement_set (struct nouveau_bo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nouveau_bo_validate (struct nouveau_bo*,int,int) ; 
 int ttm_bo_reserve (struct ttm_buffer_object*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_unreserve (struct ttm_buffer_object*) ; 

int
nouveau_bo_unpin(struct nouveau_bo *nvbo)
{
	struct nouveau_drm *drm = nouveau_bdev(nvbo->bo.bdev);
	struct ttm_buffer_object *bo = &nvbo->bo;
	int ret, ref;

	ret = ttm_bo_reserve(bo, false, false, NULL);
	if (ret)
		return ret;

	ref = --nvbo->pin_refcnt;
	WARN_ON_ONCE(ref < 0);
	if (ref)
		goto out;

	nouveau_bo_placement_set(nvbo, bo->mem.placement, 0);

	ret = nouveau_bo_validate(nvbo, false, false);
	if (ret == 0) {
		switch (bo->mem.mem_type) {
		case TTM_PL_VRAM:
			drm->gem.vram_available += bo->mem.size;
			break;
		case TTM_PL_TT:
			drm->gem.gart_available += bo->mem.size;
			break;
		default:
			break;
		}
	}

out:
	ttm_bo_unreserve(bo);
	return ret;
}