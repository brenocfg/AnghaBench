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
struct psp_context {int /*<<< orphan*/  fence_buf_mc_addr; int /*<<< orphan*/  cmd; struct amdgpu_device* adev; } ;
struct amdgpu_firmware_info {scalar_t__ ucode_id; int /*<<< orphan*/  fw; } ;
struct TYPE_2__ {int max_ucodes; struct amdgpu_firmware_info* ucode; } ;
struct amdgpu_device {TYPE_1__ firmware; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_UCODE_ID_RLC_G ; 
 scalar_t__ AMDGPU_UCODE_ID_SDMA0 ; 
 scalar_t__ AMDGPU_UCODE_ID_SDMA1 ; 
 scalar_t__ AMDGPU_UCODE_ID_SMC ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int psp_cmd_submit_buf (struct psp_context*,struct amdgpu_firmware_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int psp_prep_cmd_buf (struct amdgpu_firmware_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ psp_smu_reload_quirk (struct psp_context*) ; 

__attribute__((used)) static int psp_np_fw_load(struct psp_context *psp)
{
	int i, ret;
	struct amdgpu_firmware_info *ucode;
	struct amdgpu_device* adev = psp->adev;

	for (i = 0; i < adev->firmware.max_ucodes; i++) {
		ucode = &adev->firmware.ucode[i];
		if (!ucode->fw)
			continue;

		if (ucode->ucode_id == AMDGPU_UCODE_ID_SMC &&
		    psp_smu_reload_quirk(psp))
			continue;
		if (amdgpu_sriov_vf(adev) &&
		   (ucode->ucode_id == AMDGPU_UCODE_ID_SDMA0
		    || ucode->ucode_id == AMDGPU_UCODE_ID_SDMA1
		    || ucode->ucode_id == AMDGPU_UCODE_ID_RLC_G))
			/*skip ucode loading in SRIOV VF */
			continue;

		ret = psp_prep_cmd_buf(ucode, psp->cmd);
		if (ret)
			return ret;

		ret = psp_cmd_submit_buf(psp, ucode, psp->cmd,
					 psp->fence_buf_mc_addr, i + 3);
		if (ret)
			return ret;

#if 0
		/* check if firmware loaded sucessfully */
		if (!amdgpu_psp_check_fw_loading_status(adev, i))
			return -EINVAL;
#endif
	}

	return 0;
}