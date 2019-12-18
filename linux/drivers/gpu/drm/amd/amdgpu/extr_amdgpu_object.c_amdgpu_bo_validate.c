#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct ttm_operation_ctx {int member_0; int member_1; } ;
struct amdgpu_bo {scalar_t__ preferred_domains; scalar_t__ allowed_domains; int /*<<< orphan*/  placement; int /*<<< orphan*/  tbo; scalar_t__ pin_count; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  amdgpu_bo_placement_from_domain (struct amdgpu_bo*,scalar_t__) ; 
 int ttm_bo_validate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ttm_operation_ctx*) ; 
 scalar_t__ unlikely (int) ; 

int amdgpu_bo_validate(struct amdgpu_bo *bo)
{
	struct ttm_operation_ctx ctx = { false, false };
	uint32_t domain;
	int r;

	if (bo->pin_count)
		return 0;

	domain = bo->preferred_domains;

retry:
	amdgpu_bo_placement_from_domain(bo, domain);
	r = ttm_bo_validate(&bo->tbo, &bo->placement, &ctx);
	if (unlikely(r == -ENOMEM) && domain != bo->allowed_domains) {
		domain = bo->allowed_domains;
		goto retry;
	}

	return r;
}