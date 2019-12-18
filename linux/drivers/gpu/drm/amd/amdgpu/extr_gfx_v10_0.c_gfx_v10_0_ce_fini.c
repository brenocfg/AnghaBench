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
struct TYPE_3__ {int /*<<< orphan*/  ce_fw_ptr; int /*<<< orphan*/  ce_fw_gpu_addr; int /*<<< orphan*/  ce_fw_obj; } ;
struct TYPE_4__ {TYPE_1__ ce; } ;
struct amdgpu_device {TYPE_2__ gfx; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 

__attribute__((used)) static void gfx_v10_0_ce_fini(struct amdgpu_device *adev)
{
	amdgpu_bo_free_kernel(&adev->gfx.ce.ce_fw_obj,
			      &adev->gfx.ce.ce_fw_gpu_addr,
			      (void **)&adev->gfx.ce.ce_fw_ptr);
}