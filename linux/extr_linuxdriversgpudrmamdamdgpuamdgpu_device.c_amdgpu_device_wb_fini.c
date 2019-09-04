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
struct TYPE_2__ {int /*<<< orphan*/ * wb_obj; int /*<<< orphan*/  wb; int /*<<< orphan*/  gpu_addr; } ;
struct amdgpu_device {TYPE_1__ wb; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_free_kernel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,void**) ; 

__attribute__((used)) static void amdgpu_device_wb_fini(struct amdgpu_device *adev)
{
	if (adev->wb.wb_obj) {
		amdgpu_bo_free_kernel(&adev->wb.wb_obj,
				      &adev->wb.gpu_addr,
				      (void **)&adev->wb.wb);
		adev->wb.wb_obj = NULL;
	}
}