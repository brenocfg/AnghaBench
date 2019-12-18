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
struct amdgpu_device {int /*<<< orphan*/  gart_pin_size; int /*<<< orphan*/  visible_pin_size; int /*<<< orphan*/  vram_pin_size; } ;
struct TYPE_4__ {scalar_t__ mem_type; } ;
struct TYPE_3__ {TYPE_2__ mem; int /*<<< orphan*/  bdev; } ;
struct amdgpu_bo {TYPE_1__ tbo; } ;

/* Variables and functions */
 scalar_t__ TTM_PL_TT ; 
 scalar_t__ TTM_PL_VRAM ; 
 int /*<<< orphan*/  amdgpu_bo_size (struct amdgpu_bo*) ; 
 struct amdgpu_device* amdgpu_ttm_adev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_vram_mgr_bo_visible_size (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  atomic64_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void amdgpu_bo_subtract_pin_size(struct amdgpu_bo *bo)
{
	struct amdgpu_device *adev = amdgpu_ttm_adev(bo->tbo.bdev);

	if (bo->tbo.mem.mem_type == TTM_PL_VRAM) {
		atomic64_sub(amdgpu_bo_size(bo), &adev->vram_pin_size);
		atomic64_sub(amdgpu_vram_mgr_bo_visible_size(bo),
			     &adev->visible_pin_size);
	} else if (bo->tbo.mem.mem_type == TTM_PL_TT) {
		atomic64_sub(amdgpu_bo_size(bo), &adev->gart_pin_size);
	}
}