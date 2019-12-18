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
struct TYPE_3__ {int /*<<< orphan*/  cp_table_ptr; int /*<<< orphan*/  cp_table_gpu_addr; scalar_t__ cp_table_obj; int /*<<< orphan*/  cs_ptr; int /*<<< orphan*/  clear_state_gpu_addr; scalar_t__ clear_state_obj; int /*<<< orphan*/  sr_ptr; int /*<<< orphan*/  save_restore_gpu_addr; scalar_t__ save_restore_obj; } ;
struct TYPE_4__ {TYPE_1__ rlc; } ;
struct amdgpu_device {TYPE_2__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_free_kernel (scalar_t__*,int /*<<< orphan*/ *,void**) ; 

void amdgpu_gfx_rlc_fini(struct amdgpu_device *adev)
{
	/* save restore block */
	if (adev->gfx.rlc.save_restore_obj) {
		amdgpu_bo_free_kernel(&adev->gfx.rlc.save_restore_obj,
				      &adev->gfx.rlc.save_restore_gpu_addr,
				      (void **)&adev->gfx.rlc.sr_ptr);
	}

	/* clear state block */
	amdgpu_bo_free_kernel(&adev->gfx.rlc.clear_state_obj,
			      &adev->gfx.rlc.clear_state_gpu_addr,
			      (void **)&adev->gfx.rlc.cs_ptr);

	/* jump table block */
	amdgpu_bo_free_kernel(&adev->gfx.rlc.cp_table_obj,
			      &adev->gfx.rlc.cp_table_gpu_addr,
			      (void **)&adev->gfx.rlc.cp_table_ptr);
}