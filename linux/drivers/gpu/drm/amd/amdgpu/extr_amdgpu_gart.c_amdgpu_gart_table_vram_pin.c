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
struct TYPE_2__ {int /*<<< orphan*/  bo; int /*<<< orphan*/  ptr; } ;
struct amdgpu_device {TYPE_1__ gart; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 int amdgpu_bo_kmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int amdgpu_bo_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int amdgpu_bo_reserve (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  amdgpu_bo_unpin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_bo_unreserve (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int amdgpu_gart_table_vram_pin(struct amdgpu_device *adev)
{
	int r;

	r = amdgpu_bo_reserve(adev->gart.bo, false);
	if (unlikely(r != 0))
		return r;
	r = amdgpu_bo_pin(adev->gart.bo, AMDGPU_GEM_DOMAIN_VRAM);
	if (r) {
		amdgpu_bo_unreserve(adev->gart.bo);
		return r;
	}
	r = amdgpu_bo_kmap(adev->gart.bo, &adev->gart.ptr);
	if (r)
		amdgpu_bo_unpin(adev->gart.bo);
	amdgpu_bo_unreserve(adev->gart.bo);
	return r;
}