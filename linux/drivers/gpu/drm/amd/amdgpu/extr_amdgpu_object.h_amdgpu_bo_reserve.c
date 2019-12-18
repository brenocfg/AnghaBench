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
struct amdgpu_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;
struct amdgpu_bo {TYPE_1__ tbo; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int __ttm_bo_reserve (TYPE_1__*,int,int,int /*<<< orphan*/ *) ; 
 struct amdgpu_device* amdgpu_ttm_adev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,struct amdgpu_bo*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int amdgpu_bo_reserve(struct amdgpu_bo *bo, bool no_intr)
{
	struct amdgpu_device *adev = amdgpu_ttm_adev(bo->tbo.bdev);
	int r;

	r = __ttm_bo_reserve(&bo->tbo, !no_intr, false, NULL);
	if (unlikely(r != 0)) {
		if (r != -ERESTARTSYS)
			dev_err(adev->dev, "%p reserve failed\n", bo);
		return r;
	}
	return 0;
}