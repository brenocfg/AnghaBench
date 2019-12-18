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
struct amdgpu_firmware_info {int /*<<< orphan*/  ucode_size; int /*<<< orphan*/  fw; } ;
struct TYPE_2__ {struct amdgpu_firmware_info* ucode; int /*<<< orphan*/  fw_size; } ;
struct amdgpu_device {int /*<<< orphan*/  psp; TYPE_1__ firmware; } ;
typedef  enum AMDGPU_UCODE_ID { ____Placeholder_AMDGPU_UCODE_ID } AMDGPU_UCODE_ID ;

/* Variables and functions */
 int psp_compare_sram_data (int /*<<< orphan*/ *,struct amdgpu_firmware_info*,int) ; 

__attribute__((used)) static bool psp_check_fw_loading_status(struct amdgpu_device *adev,
					enum AMDGPU_UCODE_ID ucode_type)
{
	struct amdgpu_firmware_info *ucode = NULL;

	if (!adev->firmware.fw_size)
		return false;

	ucode = &adev->firmware.ucode[ucode_type];
	if (!ucode->fw || !ucode->ucode_size)
		return false;

	return psp_compare_sram_data(&adev->psp, ucode, ucode_type);
}