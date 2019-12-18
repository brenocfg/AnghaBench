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
struct amdgpu_device {int /*<<< orphan*/  shadow_list_lock; int /*<<< orphan*/  shadow_list; } ;
struct amdgpu_bo_param {unsigned long size; int flags; int /*<<< orphan*/  resv; int /*<<< orphan*/  type; int /*<<< orphan*/  domain; } ;
struct TYPE_4__ {int /*<<< orphan*/  resv; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
struct amdgpu_bo {TYPE_3__* shadow; TYPE_2__ tbo; } ;
typedef  int /*<<< orphan*/  bp ;
struct TYPE_6__ {int /*<<< orphan*/  shadow_list; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int AMDGPU_GEM_CREATE_CPU_GTT_USWC ; 
 int AMDGPU_GEM_CREATE_SHADOW ; 
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_GTT ; 
 int amdgpu_bo_do_create (struct amdgpu_device*,struct amdgpu_bo_param*,TYPE_3__**) ; 
 int /*<<< orphan*/  amdgpu_bo_ref (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct amdgpu_bo_param*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_type_kernel ; 

__attribute__((used)) static int amdgpu_bo_create_shadow(struct amdgpu_device *adev,
				   unsigned long size,
				   struct amdgpu_bo *bo)
{
	struct amdgpu_bo_param bp;
	int r;

	if (bo->shadow)
		return 0;

	memset(&bp, 0, sizeof(bp));
	bp.size = size;
	bp.domain = AMDGPU_GEM_DOMAIN_GTT;
	bp.flags = AMDGPU_GEM_CREATE_CPU_GTT_USWC |
		AMDGPU_GEM_CREATE_SHADOW;
	bp.type = ttm_bo_type_kernel;
	bp.resv = bo->tbo.base.resv;

	r = amdgpu_bo_do_create(adev, &bp, &bo->shadow);
	if (!r) {
		bo->shadow->parent = amdgpu_bo_ref(bo);
		mutex_lock(&adev->shadow_list_lock);
		list_add_tail(&bo->shadow->shadow_list, &adev->shadow_list);
		mutex_unlock(&adev->shadow_list_lock);
	}

	return r;
}