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
typedef  scalar_t__ uint64_t ;
struct gfx_firmware_header_v1_0 {int /*<<< orphan*/  jt_size; } ;
struct amdgpu_firmware_info {int ucode_size; TYPE_1__* fw; } ;
struct TYPE_4__ {scalar_t__ load_type; int max_ucodes; scalar_t__ fw_buf_ptr; scalar_t__ fw_buf_mc; struct amdgpu_firmware_info* ucode; } ;
struct amdgpu_device {TYPE_2__ firmware; scalar_t__ in_suspend; scalar_t__ in_gpu_reset; } ;
struct TYPE_3__ {scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ ALIGN (int,int /*<<< orphan*/ ) ; 
 scalar_t__ AMDGPU_FW_LOAD_PSP ; 
 int AMDGPU_UCODE_ID_CP_MEC1 ; 
 void* AMDGPU_UCODE_ID_MAXIMUM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_ucode_init_single_fw (struct amdgpu_device*,struct amdgpu_firmware_info*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  amdgpu_ucode_patch_jt (struct amdgpu_firmware_info*,scalar_t__,scalar_t__) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

int amdgpu_ucode_init_bo(struct amdgpu_device *adev)
{
	uint64_t fw_offset = 0;
	int i;
	struct amdgpu_firmware_info *ucode = NULL;

 /* for baremetal, the ucode is allocated in gtt, so don't need to fill the bo when reset/suspend */
	if (!amdgpu_sriov_vf(adev) && (adev->in_gpu_reset || adev->in_suspend))
		return 0;
	/*
	 * if SMU loaded firmware, it needn't add SMC, UVD, and VCE
	 * ucode info here
	 */
	if (adev->firmware.load_type != AMDGPU_FW_LOAD_PSP) {
		if (amdgpu_sriov_vf(adev))
			adev->firmware.max_ucodes = AMDGPU_UCODE_ID_MAXIMUM - 3;
		else
			adev->firmware.max_ucodes = AMDGPU_UCODE_ID_MAXIMUM - 4;
	} else {
		adev->firmware.max_ucodes = AMDGPU_UCODE_ID_MAXIMUM;
	}

	for (i = 0; i < adev->firmware.max_ucodes; i++) {
		ucode = &adev->firmware.ucode[i];
		if (ucode->fw) {
			amdgpu_ucode_init_single_fw(adev, ucode, adev->firmware.fw_buf_mc + fw_offset,
						    adev->firmware.fw_buf_ptr + fw_offset);
			if (i == AMDGPU_UCODE_ID_CP_MEC1 &&
			    adev->firmware.load_type != AMDGPU_FW_LOAD_PSP) {
				const struct gfx_firmware_header_v1_0 *cp_hdr;
				cp_hdr = (const struct gfx_firmware_header_v1_0 *)ucode->fw->data;
				amdgpu_ucode_patch_jt(ucode,  adev->firmware.fw_buf_mc + fw_offset,
						    adev->firmware.fw_buf_ptr + fw_offset);
				fw_offset += ALIGN(le32_to_cpu(cp_hdr->jt_size) << 2, PAGE_SIZE);
			}
			fw_offset += ALIGN(ucode->ucode_size, PAGE_SIZE);
		}
	}
	return 0;
}