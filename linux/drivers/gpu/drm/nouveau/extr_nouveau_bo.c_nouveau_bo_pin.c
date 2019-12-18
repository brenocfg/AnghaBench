#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_10__ {int mem_type; int /*<<< orphan*/  size; } ;
struct ttm_buffer_object {TYPE_5__ mem; int /*<<< orphan*/  bdev; } ;
struct TYPE_9__ {int /*<<< orphan*/  gart_available; int /*<<< orphan*/  vram_available; } ;
struct TYPE_6__ {scalar_t__ family; } ;
struct TYPE_7__ {TYPE_1__ info; } ;
struct TYPE_8__ {TYPE_2__ device; } ;
struct nouveau_drm {TYPE_4__ gem; TYPE_3__ client; } ;
struct nouveau_bo {int contig; scalar_t__ pin_refcnt; struct ttm_buffer_object bo; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ NV_DEVICE_INFO_V0_TESLA ; 
 int /*<<< orphan*/  NV_ERROR (struct nouveau_drm*,char*,struct ttm_buffer_object*,int,int) ; 
 int TTM_PL_FLAG_TT ; 
 int TTM_PL_FLAG_VRAM ; 
#define  TTM_PL_TT 129 
#define  TTM_PL_VRAM 128 
 struct nouveau_drm* nouveau_bdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nouveau_bo_placement_set (struct nouveau_bo*,int,int /*<<< orphan*/ ) ; 
 int nouveau_bo_validate (struct nouveau_bo*,int,int) ; 
 int ttm_bo_reserve (struct ttm_buffer_object*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_unreserve (struct ttm_buffer_object*) ; 

int
nouveau_bo_pin(struct nouveau_bo *nvbo, uint32_t memtype, bool contig)
{
	struct nouveau_drm *drm = nouveau_bdev(nvbo->bo.bdev);
	struct ttm_buffer_object *bo = &nvbo->bo;
	bool force = false, evict = false;
	int ret;

	ret = ttm_bo_reserve(bo, false, false, NULL);
	if (ret)
		return ret;

	if (drm->client.device.info.family >= NV_DEVICE_INFO_V0_TESLA &&
	    memtype == TTM_PL_FLAG_VRAM && contig) {
		if (!nvbo->contig) {
			nvbo->contig = true;
			force = true;
			evict = true;
		}
	}

	if (nvbo->pin_refcnt) {
		if (!(memtype & (1 << bo->mem.mem_type)) || evict) {
			NV_ERROR(drm, "bo %p pinned elsewhere: "
				      "0x%08x vs 0x%08x\n", bo,
				 1 << bo->mem.mem_type, memtype);
			ret = -EBUSY;
		}
		nvbo->pin_refcnt++;
		goto out;
	}

	if (evict) {
		nouveau_bo_placement_set(nvbo, TTM_PL_FLAG_TT, 0);
		ret = nouveau_bo_validate(nvbo, false, false);
		if (ret)
			goto out;
	}

	nvbo->pin_refcnt++;
	nouveau_bo_placement_set(nvbo, memtype, 0);

	/* drop pin_refcnt temporarily, so we don't trip the assertion
	 * in nouveau_bo_move() that makes sure we're not trying to
	 * move a pinned buffer
	 */
	nvbo->pin_refcnt--;
	ret = nouveau_bo_validate(nvbo, false, false);
	if (ret)
		goto out;
	nvbo->pin_refcnt++;

	switch (bo->mem.mem_type) {
	case TTM_PL_VRAM:
		drm->gem.vram_available -= bo->mem.size;
		break;
	case TTM_PL_TT:
		drm->gem.gart_available -= bo->mem.size;
		break;
	default:
		break;
	}

out:
	if (force && ret)
		nvbo->contig = false;
	ttm_bo_unreserve(bo);
	return ret;
}