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
typedef  int /*<<< orphan*/  uint32_t ;
struct ttm_operation_ctx {int member_0; int member_1; } ;
struct TYPE_2__ {int /*<<< orphan*/  ttm; } ;
struct amdgpu_bo {int /*<<< orphan*/  placement; TYPE_1__ tbo; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_FENCE_OWNER_KFD ; 
 int EINVAL ; 
 scalar_t__ WARN (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  amdgpu_bo_placement_from_domain (struct amdgpu_bo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_bo_sync_wait (struct amdgpu_bo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  amdgpu_ttm_tt_get_usermm (int /*<<< orphan*/ ) ; 
 int ttm_bo_validate (TYPE_1__*,int /*<<< orphan*/ *,struct ttm_operation_ctx*) ; 

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
	if (wait)
		amdgpu_bo_sync_wait(bo, AMDGPU_FENCE_OWNER_KFD, false);

validate_fail:
	return ret;
}