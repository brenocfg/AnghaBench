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
struct TYPE_2__ {int /*<<< orphan*/ * ptr; int /*<<< orphan*/ * bo; } ;
struct amdgpu_device {TYPE_1__ gart; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_kunmap (int /*<<< orphan*/ *) ; 
 int amdgpu_bo_reserve (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  amdgpu_bo_unpin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 

void amdgpu_gart_table_vram_unpin(struct amdgpu_device *adev)
{
	int r;

	if (adev->gart.bo == NULL) {
		return;
	}
	r = amdgpu_bo_reserve(adev->gart.bo, true);
	if (likely(r == 0)) {
		amdgpu_bo_kunmap(adev->gart.bo);
		amdgpu_bo_unpin(adev->gart.bo);
		amdgpu_bo_unreserve(adev->gart.bo);
		adev->gart.ptr = NULL;
	}
}