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
struct dma_fence {int dummy; } ;
struct amdgpu_ring {int dummy; } ;
struct amdgpu_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  mem_type; } ;
struct TYPE_4__ {TYPE_1__ mem; } ;
struct amdgpu_bo {int /*<<< orphan*/  shadow; TYPE_2__ tbo; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_GEM_DOMAIN_VRAM ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int amdgpu_bo_reserve (struct amdgpu_bo*,int) ; 
 int amdgpu_bo_restore_from_shadow (struct amdgpu_device*,struct amdgpu_ring*,struct amdgpu_bo*,int /*<<< orphan*/ *,struct dma_fence**,int) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (struct amdgpu_bo*) ; 
 int amdgpu_bo_validate (int /*<<< orphan*/ ) ; 
 scalar_t__ amdgpu_mem_type_to_domain (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amdgpu_device_recover_vram_from_shadow(struct amdgpu_device *adev,
						  struct amdgpu_ring *ring,
						  struct amdgpu_bo *bo,
						  struct dma_fence **fence)
{
	uint32_t domain;
	int r;

	if (!bo->shadow)
		return 0;

	r = amdgpu_bo_reserve(bo, true);
	if (r)
		return r;
	domain = amdgpu_mem_type_to_domain(bo->tbo.mem.mem_type);
	/* if bo has been evicted, then no need to recover */
	if (domain == AMDGPU_GEM_DOMAIN_VRAM) {
		r = amdgpu_bo_validate(bo->shadow);
		if (r) {
			DRM_ERROR("bo validate failed!\n");
			goto err;
		}

		r = amdgpu_bo_restore_from_shadow(adev, ring, bo,
						 NULL, fence, true);
		if (r) {
			DRM_ERROR("recover page table failed!\n");
			goto err;
		}
	}
err:
	amdgpu_bo_unreserve(bo);
	return r;
}