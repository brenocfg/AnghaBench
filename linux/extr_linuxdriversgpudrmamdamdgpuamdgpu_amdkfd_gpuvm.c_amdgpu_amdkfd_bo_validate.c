#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct ttm_operation_ctx {int member_0; int member_1; } ;
struct TYPE_3__ {int /*<<< orphan*/  ttm; } ;
struct amdgpu_bo {TYPE_1__ tbo; int /*<<< orphan*/  placement; } ;
struct amdgpu_amdkfd_fence {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  amdgpu_amdkfd_add_eviction_fence (struct amdgpu_bo*,struct amdgpu_amdkfd_fence**,unsigned int) ; 
 int amdgpu_amdkfd_remove_eviction_fence (struct amdgpu_bo*,int /*<<< orphan*/ *,struct amdgpu_amdkfd_fence***,unsigned int*) ; 
 int /*<<< orphan*/  amdgpu_bo_placement_from_domain (struct amdgpu_bo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ttm_tt_get_usermm (int /*<<< orphan*/ ) ; 
 int ttm_bo_validate (TYPE_1__*,int /*<<< orphan*/ *,struct ttm_operation_ctx*) ; 
 int /*<<< orphan*/  ttm_bo_wait (TYPE_1__*,int,int) ; 

__attribute__((used)) static int amdgpu_amdkfd_bo_validate(struct amdgpu_bo *bo, uint32_t domain,
				     bool wait)
{
	struct ttm_operation_ctx ctx = { false, false };
	int ret;

	if (WARN(amdgpu_ttm_tt_get_usermm(bo->tbo.ttm),
		 "Called with userptr BO"))
		return -EINVAL;

	amdgpu_bo_placement_from_domain(bo, domain);

	ret = ttm_bo_validate(&bo->tbo, &bo->placement, &ctx);
	if (ret)
		goto validate_fail;
	if (wait) {
		struct amdgpu_amdkfd_fence **ef_list;
		unsigned int ef_count;

		ret = amdgpu_amdkfd_remove_eviction_fence(bo, NULL, &ef_list,
							  &ef_count);
		if (ret)
			goto validate_fail;

		ttm_bo_wait(&bo->tbo, false, false);
		amdgpu_amdkfd_add_eviction_fence(bo, ef_list, ef_count);
	}

validate_fail:
	return ret;
}