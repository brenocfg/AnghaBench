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
struct TYPE_2__ {scalar_t__ load_type; int /*<<< orphan*/  fw_buf_ptr; int /*<<< orphan*/  fw_buf_mc; int /*<<< orphan*/  fw_buf; } ;
struct amdgpu_device {TYPE_1__ firmware; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_FW_LOAD_DIRECT ; 
 int /*<<< orphan*/  amdgpu_bo_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void amdgpu_ucode_free_bo(struct amdgpu_device *adev)
{
	if (adev->firmware.load_type != AMDGPU_FW_LOAD_DIRECT)
		amdgpu_bo_free_kernel(&adev->firmware.fw_buf,
		&adev->firmware.fw_buf_mc,
		&adev->firmware.fw_buf_ptr);
}