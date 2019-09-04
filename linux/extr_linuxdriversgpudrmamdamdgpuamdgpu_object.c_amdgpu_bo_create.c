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
typedef  int u64 ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_bo_param {int flags; int /*<<< orphan*/  resv; int /*<<< orphan*/  byte_align; int /*<<< orphan*/  size; } ;
struct TYPE_2__ {int /*<<< orphan*/  resv; } ;
struct amdgpu_bo {TYPE_1__ tbo; } ;

/* Variables and functions */
 int AMDGPU_GEM_CREATE_SHADOW ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int amdgpu_bo_create_shadow (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct amdgpu_bo*) ; 
 int amdgpu_bo_do_create (struct amdgpu_device*,struct amdgpu_bo_param*,struct amdgpu_bo**) ; 
 scalar_t__ amdgpu_bo_need_backup (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_bo_unref (struct amdgpu_bo**) ; 
 int /*<<< orphan*/  reservation_object_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reservation_object_unlock (int /*<<< orphan*/ ) ; 

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

	if ((flags & AMDGPU_GEM_CREATE_SHADOW) && amdgpu_bo_need_backup(adev)) {
		if (!bp->resv)
			WARN_ON(reservation_object_lock((*bo_ptr)->tbo.resv,
							NULL));

		r = amdgpu_bo_create_shadow(adev, bp->size, bp->byte_align, (*bo_ptr));

		if (!bp->resv)
			reservation_object_unlock((*bo_ptr)->tbo.resv);

		if (r)
			amdgpu_bo_unref(bo_ptr);
	}

	return r;
}