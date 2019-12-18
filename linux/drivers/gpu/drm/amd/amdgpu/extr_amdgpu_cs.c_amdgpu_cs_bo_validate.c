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
typedef  scalar_t__ uint32_t ;
struct ttm_operation_ctx {int interruptible; int no_wait_gpu; scalar_t__ bytes_moved; int /*<<< orphan*/  flags; int /*<<< orphan*/  resv; } ;
struct amdgpu_device {int /*<<< orphan*/  gmc; } ;
struct amdgpu_cs_parser {scalar_t__ bytes_moved; scalar_t__ bytes_moved_threshold; scalar_t__ bytes_moved_vis; scalar_t__ bytes_moved_vis_threshold; } ;
struct TYPE_3__ {int /*<<< orphan*/  resv; } ;
struct TYPE_4__ {TYPE_1__ base; int /*<<< orphan*/  bdev; } ;
struct amdgpu_bo {int flags; scalar_t__ preferred_domains; scalar_t__ allowed_domains; int /*<<< orphan*/  placement; TYPE_2__ tbo; scalar_t__ pin_count; } ;

/* Variables and functions */
 int AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED ; 
 int ENOMEM ; 
 scalar_t__ amdgpu_bo_in_cpu_visible_vram (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_bo_placement_from_domain (struct amdgpu_bo*,scalar_t__) ; 
 int /*<<< orphan*/  amdgpu_gmc_vram_full_visible (int /*<<< orphan*/ *) ; 
 struct amdgpu_device* amdgpu_ttm_adev (int /*<<< orphan*/ ) ; 
 int ttm_bo_validate (TYPE_2__*,int /*<<< orphan*/ *,struct ttm_operation_ctx*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int amdgpu_cs_bo_validate(struct amdgpu_cs_parser *p,
				 struct amdgpu_bo *bo)
{
	struct amdgpu_device *adev = amdgpu_ttm_adev(bo->tbo.bdev);
	struct ttm_operation_ctx ctx = {
		.interruptible = true,
		.no_wait_gpu = false,
		.resv = bo->tbo.base.resv,
		.flags = 0
	};
	uint32_t domain;
	int r;

	if (bo->pin_count)
		return 0;

	/* Don't move this buffer if we have depleted our allowance
	 * to move it. Don't move anything if the threshold is zero.
	 */
	if (p->bytes_moved < p->bytes_moved_threshold) {
		if (!amdgpu_gmc_vram_full_visible(&adev->gmc) &&
		    (bo->flags & AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED)) {
			/* And don't move a CPU_ACCESS_REQUIRED BO to limited
			 * visible VRAM if we've depleted our allowance to do
			 * that.
			 */
			if (p->bytes_moved_vis < p->bytes_moved_vis_threshold)
				domain = bo->preferred_domains;
			else
				domain = bo->allowed_domains;
		} else {
			domain = bo->preferred_domains;
		}
	} else {
		domain = bo->allowed_domains;
	}

retry:
	amdgpu_bo_placement_from_domain(bo, domain);
	r = ttm_bo_validate(&bo->tbo, &bo->placement, &ctx);

	p->bytes_moved += ctx.bytes_moved;
	if (!amdgpu_gmc_vram_full_visible(&adev->gmc) &&
	    amdgpu_bo_in_cpu_visible_vram(bo))
		p->bytes_moved_vis += ctx.bytes_moved;

	if (unlikely(r == -ENOMEM) && domain != bo->allowed_domains) {
		domain = bo->allowed_domains;
		goto retry;
	}

	return r;
}