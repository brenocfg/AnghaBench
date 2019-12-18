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
struct psp_context {scalar_t__ autoload_supported; struct amdgpu_device* adev; } ;
struct amdgpu_firmware_info {size_t ucode_id; int /*<<< orphan*/  fw; } ;
struct TYPE_2__ {int max_ucodes; struct amdgpu_firmware_info* ucode; } ;
struct amdgpu_device {scalar_t__ asic_type; TYPE_1__ firmware; } ;

/* Variables and functions */
 size_t AMDGPU_UCODE_ID_CP_MEC1_JT ; 
 size_t AMDGPU_UCODE_ID_CP_MEC2_JT ; 
 size_t AMDGPU_UCODE_ID_RLC_G ; 
 size_t AMDGPU_UCODE_ID_RLC_RESTORE_LIST_SRM_MEM ; 
 size_t AMDGPU_UCODE_ID_SDMA0 ; 
 size_t AMDGPU_UCODE_ID_SDMA1 ; 
 size_t AMDGPU_UCODE_ID_SDMA2 ; 
 size_t AMDGPU_UCODE_ID_SDMA3 ; 
 size_t AMDGPU_UCODE_ID_SDMA4 ; 
 size_t AMDGPU_UCODE_ID_SDMA5 ; 
 size_t AMDGPU_UCODE_ID_SDMA6 ; 
 size_t AMDGPU_UCODE_ID_SDMA7 ; 
 size_t AMDGPU_UCODE_ID_SMC ; 
 scalar_t__ CHIP_RENOIR ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  amdgpu_psp_check_fw_loading_status (struct amdgpu_device*,int) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int psp_execute_np_fw_load (struct psp_context*,struct amdgpu_firmware_info*) ; 
 int /*<<< orphan*/  psp_print_fw_hdr (struct psp_context*,struct amdgpu_firmware_info*) ; 
 int psp_rlc_autoload (struct psp_context*) ; 
 scalar_t__ psp_smu_reload_quirk (struct psp_context*) ; 

__attribute__((used)) static int psp_np_fw_load(struct psp_context *psp)
{
	int i, ret;
	struct amdgpu_firmware_info *ucode;
	struct amdgpu_device* adev = psp->adev;

	if (psp->autoload_supported) {
		ucode = &adev->firmware.ucode[AMDGPU_UCODE_ID_SMC];
		if (!ucode->fw)
			goto out;

		ret = psp_execute_np_fw_load(psp, ucode);
		if (ret)
			return ret;
	}

out:
	for (i = 0; i < adev->firmware.max_ucodes; i++) {
		ucode = &adev->firmware.ucode[i];
		if (!ucode->fw)
			continue;

		if (ucode->ucode_id == AMDGPU_UCODE_ID_SMC &&
		    (psp_smu_reload_quirk(psp) || psp->autoload_supported))
			continue;

		if (amdgpu_sriov_vf(adev) &&
		   (ucode->ucode_id == AMDGPU_UCODE_ID_SDMA0
		    || ucode->ucode_id == AMDGPU_UCODE_ID_SDMA1
		    || ucode->ucode_id == AMDGPU_UCODE_ID_SDMA2
		    || ucode->ucode_id == AMDGPU_UCODE_ID_SDMA3
		    || ucode->ucode_id == AMDGPU_UCODE_ID_SDMA4
		    || ucode->ucode_id == AMDGPU_UCODE_ID_SDMA5
		    || ucode->ucode_id == AMDGPU_UCODE_ID_SDMA6
		    || ucode->ucode_id == AMDGPU_UCODE_ID_SDMA7
		    || ucode->ucode_id == AMDGPU_UCODE_ID_RLC_G))
			/*skip ucode loading in SRIOV VF */
			continue;

		if (psp->autoload_supported &&
		    (ucode->ucode_id == AMDGPU_UCODE_ID_CP_MEC1_JT ||
		     ucode->ucode_id == AMDGPU_UCODE_ID_CP_MEC2_JT))
			/* skip mec JT when autoload is enabled */
			continue;
		/* Renoir only needs to load mec jump table one time */
		if (adev->asic_type == CHIP_RENOIR &&
		    ucode->ucode_id == AMDGPU_UCODE_ID_CP_MEC2_JT)
			continue;

		psp_print_fw_hdr(psp, ucode);

		ret = psp_execute_np_fw_load(psp, ucode);
		if (ret)
			return ret;

		/* Start rlc autoload after psp recieved all the gfx firmware */
		if (ucode->ucode_id == AMDGPU_UCODE_ID_RLC_RESTORE_LIST_SRM_MEM) {
			ret = psp_rlc_autoload(psp);
			if (ret) {
				DRM_ERROR("Failed to start rlc autoload\n");
				return ret;
			}
		}
#if 0
		/* check if firmware loaded sucessfully */
		if (!amdgpu_psp_check_fw_loading_status(adev, i))
			return -EINVAL;
#endif
	}

	return 0;
}