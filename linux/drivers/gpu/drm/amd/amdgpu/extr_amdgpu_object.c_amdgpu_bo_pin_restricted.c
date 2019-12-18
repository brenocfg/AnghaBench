#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct ttm_operation_ctx {int member_0; int member_1; } ;
struct amdgpu_device {int /*<<< orphan*/  gart_pin_size; int /*<<< orphan*/  visible_pin_size; int /*<<< orphan*/  vram_pin_size; int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {size_t mem_type; } ;
struct TYPE_10__ {TYPE_3__ mem; TYPE_6__* bdev; int /*<<< orphan*/  ttm; } ;
struct TYPE_11__ {int num_placement; } ;
struct amdgpu_bo {int pin_count; int flags; TYPE_4__ tbo; TYPE_5__ placement; TYPE_2__* placements; scalar_t__ prime_shared_count; } ;
struct TYPE_12__ {TYPE_1__* man; } ;
struct TYPE_8__ {unsigned int fpfn; unsigned int lpfn; int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {scalar_t__ gpu_offset; } ;

/* Variables and functions */
 int AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED ; 
 int AMDGPU_GEM_CREATE_NO_CPU_ACCESS ; 
 int AMDGPU_GEM_CREATE_VRAM_CONTIGUOUS ; 
 int AMDGPU_GEM_DOMAIN_GTT ; 
 int AMDGPU_GEM_DOMAIN_VRAM ; 
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ PAGE_SHIFT ; 
 int /*<<< orphan*/  TTM_PL_FLAG_NO_EVICT ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int amdgpu_bo_get_preferred_pin_domain (struct amdgpu_device*,int) ; 
 scalar_t__ amdgpu_bo_gpu_offset (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_bo_placement_from_domain (struct amdgpu_bo*,int) ; 
 int /*<<< orphan*/  amdgpu_bo_size (struct amdgpu_bo*) ; 
 int amdgpu_mem_type_to_domain (size_t) ; 
 struct amdgpu_device* amdgpu_ttm_adev (TYPE_6__*) ; 
 scalar_t__ amdgpu_ttm_tt_get_usermm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_vram_mgr_bo_visible_size (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  atomic64_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,struct amdgpu_bo*) ; 
 int ttm_bo_validate (TYPE_4__*,TYPE_5__*,struct ttm_operation_ctx*) ; 
 scalar_t__ unlikely (int) ; 

int amdgpu_bo_pin_restricted(struct amdgpu_bo *bo, u32 domain,
			     u64 min_offset, u64 max_offset)
{
	struct amdgpu_device *adev = amdgpu_ttm_adev(bo->tbo.bdev);
	struct ttm_operation_ctx ctx = { false, false };
	int r, i;

	if (amdgpu_ttm_tt_get_usermm(bo->tbo.ttm))
		return -EPERM;

	if (WARN_ON_ONCE(min_offset > max_offset))
		return -EINVAL;

	/* A shared bo cannot be migrated to VRAM */
	if (bo->prime_shared_count) {
		if (domain & AMDGPU_GEM_DOMAIN_GTT)
			domain = AMDGPU_GEM_DOMAIN_GTT;
		else
			return -EINVAL;
	}

	/* This assumes only APU display buffers are pinned with (VRAM|GTT).
	 * See function amdgpu_display_supported_domains()
	 */
	domain = amdgpu_bo_get_preferred_pin_domain(adev, domain);

	if (bo->pin_count) {
		uint32_t mem_type = bo->tbo.mem.mem_type;

		if (!(domain & amdgpu_mem_type_to_domain(mem_type)))
			return -EINVAL;

		bo->pin_count++;

		if (max_offset != 0) {
			u64 domain_start = bo->tbo.bdev->man[mem_type].gpu_offset;
			WARN_ON_ONCE(max_offset <
				     (amdgpu_bo_gpu_offset(bo) - domain_start));
		}

		return 0;
	}

	bo->flags |= AMDGPU_GEM_CREATE_VRAM_CONTIGUOUS;
	/* force to pin into visible video ram */
	if (!(bo->flags & AMDGPU_GEM_CREATE_NO_CPU_ACCESS))
		bo->flags |= AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED;
	amdgpu_bo_placement_from_domain(bo, domain);
	for (i = 0; i < bo->placement.num_placement; i++) {
		unsigned fpfn, lpfn;

		fpfn = min_offset >> PAGE_SHIFT;
		lpfn = max_offset >> PAGE_SHIFT;

		if (fpfn > bo->placements[i].fpfn)
			bo->placements[i].fpfn = fpfn;
		if (!bo->placements[i].lpfn ||
		    (lpfn && lpfn < bo->placements[i].lpfn))
			bo->placements[i].lpfn = lpfn;
		bo->placements[i].flags |= TTM_PL_FLAG_NO_EVICT;
	}

	r = ttm_bo_validate(&bo->tbo, &bo->placement, &ctx);
	if (unlikely(r)) {
		dev_err(adev->dev, "%p pin failed\n", bo);
		goto error;
	}

	bo->pin_count = 1;

	domain = amdgpu_mem_type_to_domain(bo->tbo.mem.mem_type);
	if (domain == AMDGPU_GEM_DOMAIN_VRAM) {
		atomic64_add(amdgpu_bo_size(bo), &adev->vram_pin_size);
		atomic64_add(amdgpu_vram_mgr_bo_visible_size(bo),
			     &adev->visible_pin_size);
	} else if (domain == AMDGPU_GEM_DOMAIN_GTT) {
		atomic64_add(amdgpu_bo_size(bo), &adev->gart_pin_size);
	}

error:
	return r;
}