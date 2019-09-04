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
typedef  int /*<<< orphan*/  uint64_t ;
struct ttm_buffer_object {int /*<<< orphan*/  mem; int /*<<< orphan*/  ttm; int /*<<< orphan*/  bdev; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 struct amdgpu_device* amdgpu_ttm_adev (int /*<<< orphan*/ ) ; 
 int amdgpu_ttm_gart_bind (struct amdgpu_device*,struct ttm_buffer_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ttm_tt_pte_flags (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int amdgpu_ttm_recover_gart(struct ttm_buffer_object *tbo)
{
	struct amdgpu_device *adev = amdgpu_ttm_adev(tbo->bdev);
	uint64_t flags;
	int r;

	if (!tbo->ttm)
		return 0;

	flags = amdgpu_ttm_tt_pte_flags(adev, tbo->ttm, &tbo->mem);
	r = amdgpu_ttm_gart_bind(adev, tbo, flags);

	return r;
}