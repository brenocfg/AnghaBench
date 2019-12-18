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
struct TYPE_3__ {int /*<<< orphan*/  load_type; } ;
struct amdgpu_device {int asic_type; TYPE_1__ firmware; int /*<<< orphan*/  enable_virtual_display; int /*<<< orphan*/  enable_mes; TYPE_2__* nbio_funcs; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* detect_hw_virt ) (struct amdgpu_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_FW_LOAD_DIRECT ; 
 int /*<<< orphan*/  AMDGPU_FW_LOAD_PSP ; 
#define  CHIP_NAVI10 130 
#define  CHIP_NAVI12 129 
#define  CHIP_NAVI14 128 
 int EINVAL ; 
 int /*<<< orphan*/  amdgpu_device_has_dc_support (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_device_ip_block_add (struct amdgpu_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  dce_virtual_ip_block ; 
 int /*<<< orphan*/  dm_ip_block ; 
 int /*<<< orphan*/  gfx_v10_0_ip_block ; 
 int /*<<< orphan*/  gmc_v10_0_ip_block ; 
 int /*<<< orphan*/  is_support_sw_smu (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mes_v10_1_ip_block ; 
 int /*<<< orphan*/  navi10_ih_ip_block ; 
 TYPE_2__ nbio_v2_3_funcs ; 
 int /*<<< orphan*/  nv_common_ip_block ; 
 int nv_reg_base_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  psp_v11_0_ip_block ; 
 int /*<<< orphan*/  sdma_v5_0_ip_block ; 
 int /*<<< orphan*/  smu_v11_0_ip_block ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_device*) ; 
 int /*<<< orphan*/  vcn_v2_0_ip_block ; 

int nv_set_ip_blocks(struct amdgpu_device *adev)
{
	int r;

	/* Set IP register base before any HW register access */
	r = nv_reg_base_init(adev);
	if (r)
		return r;

	adev->nbio_funcs = &nbio_v2_3_funcs;

	adev->nbio_funcs->detect_hw_virt(adev);

	switch (adev->asic_type) {
	case CHIP_NAVI10:
	case CHIP_NAVI14:
		amdgpu_device_ip_block_add(adev, &nv_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v10_0_ip_block);
		amdgpu_device_ip_block_add(adev, &navi10_ih_ip_block);
		amdgpu_device_ip_block_add(adev, &psp_v11_0_ip_block);
		if (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP &&
		    is_support_sw_smu(adev))
			amdgpu_device_ip_block_add(adev, &smu_v11_0_ip_block);
		if (adev->enable_virtual_display || amdgpu_sriov_vf(adev))
			amdgpu_device_ip_block_add(adev, &dce_virtual_ip_block);
#if defined(CONFIG_DRM_AMD_DC)
		else if (amdgpu_device_has_dc_support(adev))
			amdgpu_device_ip_block_add(adev, &dm_ip_block);
#endif
		amdgpu_device_ip_block_add(adev, &gfx_v10_0_ip_block);
		amdgpu_device_ip_block_add(adev, &sdma_v5_0_ip_block);
		if (adev->firmware.load_type == AMDGPU_FW_LOAD_DIRECT &&
		    is_support_sw_smu(adev))
			amdgpu_device_ip_block_add(adev, &smu_v11_0_ip_block);
		amdgpu_device_ip_block_add(adev, &vcn_v2_0_ip_block);
		if (adev->enable_mes)
			amdgpu_device_ip_block_add(adev, &mes_v10_1_ip_block);
		break;
	case CHIP_NAVI12:
		amdgpu_device_ip_block_add(adev, &nv_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v10_0_ip_block);
		amdgpu_device_ip_block_add(adev, &navi10_ih_ip_block);
		amdgpu_device_ip_block_add(adev, &psp_v11_0_ip_block);
		if (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP &&
		    is_support_sw_smu(adev))
			amdgpu_device_ip_block_add(adev, &smu_v11_0_ip_block);
		if (adev->enable_virtual_display || amdgpu_sriov_vf(adev))
			amdgpu_device_ip_block_add(adev, &dce_virtual_ip_block);
#if defined(CONFIG_DRM_AMD_DC)
		else if (amdgpu_device_has_dc_support(adev))
			amdgpu_device_ip_block_add(adev, &dm_ip_block);
#endif
		amdgpu_device_ip_block_add(adev, &gfx_v10_0_ip_block);
		amdgpu_device_ip_block_add(adev, &sdma_v5_0_ip_block);
		if (adev->firmware.load_type == AMDGPU_FW_LOAD_DIRECT &&
		    is_support_sw_smu(adev))
			amdgpu_device_ip_block_add(adev, &smu_v11_0_ip_block);
		amdgpu_device_ip_block_add(adev, &vcn_v2_0_ip_block);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}