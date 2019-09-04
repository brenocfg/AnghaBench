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
struct amdgpu_firmware_info {int /*<<< orphan*/ * kaddr; scalar_t__ mc_addr; scalar_t__ fw; } ;
struct TYPE_2__ {int max_ucodes; int /*<<< orphan*/  fw_buf_ptr; int /*<<< orphan*/  fw_buf_mc; int /*<<< orphan*/  fw_buf; struct amdgpu_firmware_info* ucode; int /*<<< orphan*/  fw_size; } ;
struct amdgpu_device {TYPE_1__ firmware; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int amdgpu_ucode_fini_bo(struct amdgpu_device *adev)
{
	int i;
	struct amdgpu_firmware_info *ucode = NULL;

	if (!adev->firmware.fw_size)
		return 0;

	for (i = 0; i < adev->firmware.max_ucodes; i++) {
		ucode = &adev->firmware.ucode[i];
		if (ucode->fw) {
			ucode->mc_addr = 0;
			ucode->kaddr = NULL;
		}
	}

	amdgpu_bo_free_kernel(&adev->firmware.fw_buf,
				&adev->firmware.fw_buf_mc,
				&adev->firmware.fw_buf_ptr);

	return 0;
}