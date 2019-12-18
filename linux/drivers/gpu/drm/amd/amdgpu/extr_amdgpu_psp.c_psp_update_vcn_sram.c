#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct amdgpu_firmware_info {int ucode_size; int /*<<< orphan*/  mc_addr; int /*<<< orphan*/  ucode_id; int /*<<< orphan*/  member_0; } ;
struct amdgpu_device {int /*<<< orphan*/  psp; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_UCODE_ID_VCN0_RAM ; 
 int /*<<< orphan*/  AMDGPU_UCODE_ID_VCN1_RAM ; 
 int psp_execute_np_fw_load (int /*<<< orphan*/ *,struct amdgpu_firmware_info*) ; 

int psp_update_vcn_sram(struct amdgpu_device *adev, int inst_idx,
			uint64_t cmd_gpu_addr, int cmd_size)
{
	struct amdgpu_firmware_info ucode = {0};

	ucode.ucode_id = inst_idx ? AMDGPU_UCODE_ID_VCN1_RAM :
		AMDGPU_UCODE_ID_VCN0_RAM;
	ucode.mc_addr = cmd_gpu_addr;
	ucode.ucode_size = cmd_size;

	return psp_execute_np_fw_load(&adev->psp, &ucode);
}