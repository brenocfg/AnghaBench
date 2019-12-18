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
struct TYPE_2__ {scalar_t__ load_type; int /*<<< orphan*/  fw_size; int /*<<< orphan*/  fw_buf_ptr; int /*<<< orphan*/  fw_buf; int /*<<< orphan*/  fw_buf_mc; } ;
struct amdgpu_device {TYPE_1__ firmware; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_FW_LOAD_DIRECT ; 
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_GTT ; 
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  amdgpu_bo_create_kernel (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int amdgpu_ucode_create_bo(struct amdgpu_device *adev)
{
	if (adev->firmware.load_type != AMDGPU_FW_LOAD_DIRECT) {
		amdgpu_bo_create_kernel(adev, adev->firmware.fw_size, PAGE_SIZE,
			amdgpu_sriov_vf(adev) ? AMDGPU_GEM_DOMAIN_VRAM : AMDGPU_GEM_DOMAIN_GTT,
			&adev->firmware.fw_buf,
			&adev->firmware.fw_buf_mc,
			&adev->firmware.fw_buf_ptr);
		if (!adev->firmware.fw_buf) {
			dev_err(adev->dev, "failed to create kernel buffer for firmware.fw_buf\n");
			return -ENOMEM;
		} else if (amdgpu_sriov_vf(adev)) {
			memset(adev->firmware.fw_buf_ptr, 0, adev->firmware.fw_size);
		}
	}
	return 0;
}