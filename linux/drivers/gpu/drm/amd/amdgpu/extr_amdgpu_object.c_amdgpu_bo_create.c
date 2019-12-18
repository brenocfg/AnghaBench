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
typedef  int u64 ;
struct amdgpu_device {int flags; } ;
struct amdgpu_bo_param {int flags; int /*<<< orphan*/  resv; int /*<<< orphan*/  size; } ;
struct TYPE_3__ {int /*<<< orphan*/  resv; } ;
struct TYPE_4__ {TYPE_1__ base; } ;
struct amdgpu_bo {TYPE_2__ tbo; } ;

/* Variables and functions */
 int AMDGPU_GEM_CREATE_SHADOW ; 
 int AMD_IS_APU ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int amdgpu_bo_create_shadow (struct amdgpu_device*,int /*<<< orphan*/ ,struct amdgpu_bo*) ; 
 int amdgpu_bo_do_create (struct amdgpu_device*,struct amdgpu_bo_param*,struct amdgpu_bo**) ; 
 int /*<<< orphan*/  amdgpu_bo_unref (struct amdgpu_bo**) ; 
 int /*<<< orphan*/  dma_resv_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_resv_unlock (int /*<<< orphan*/ ) ; 

int amdgpu_bo_create(struct amdgpu_device *adev,
		     struct amdgpu_bo_param *bp,
		     struct amdgpu_bo **bo_ptr)
{
	u64 flags = bp->flags;
	int r;

	bp->flags = bp->flags & ~AMDGPU_GEM_CREATE_SHADOW;
	r = amdgpu_bo_do_create(adev, bp, bo_ptr);
	if (r)
		return r;

	if ((flags & AMDGPU_GEM_CREATE_SHADOW) && !(adev->flags & AMD_IS_APU)) {
		if (!bp->resv)
			WARN_ON(dma_resv_lock((*bo_ptr)->tbo.base.resv,
							NULL));

		r = amdgpu_bo_create_shadow(adev, bp->size, *bo_ptr);

		if (!bp->resv)
			dma_resv_unlock((*bo_ptr)->tbo.base.resv);

		if (r)
			amdgpu_bo_unref(bo_ptr);
	}

	return r;
}