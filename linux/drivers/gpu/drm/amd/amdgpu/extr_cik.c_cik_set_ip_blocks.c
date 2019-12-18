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
struct amdgpu_device {int asic_type; int /*<<< orphan*/  enable_virtual_display; } ;

/* Variables and functions */
#define  CHIP_BONAIRE 132 
#define  CHIP_HAWAII 131 
#define  CHIP_KABINI 130 
#define  CHIP_KAVERI 129 
#define  CHIP_MULLINS 128 
 int EINVAL ; 
 int /*<<< orphan*/  amdgpu_device_has_dc_support (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_device_ip_block_add (struct amdgpu_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cik_common_ip_block ; 
 int /*<<< orphan*/  cik_detect_hw_virtualization (struct amdgpu_device*) ; 
 int /*<<< orphan*/  cik_ih_ip_block ; 
 int /*<<< orphan*/  cik_sdma_ip_block ; 
 int /*<<< orphan*/  dce_v8_1_ip_block ; 
 int /*<<< orphan*/  dce_v8_2_ip_block ; 
 int /*<<< orphan*/  dce_v8_3_ip_block ; 
 int /*<<< orphan*/  dce_v8_5_ip_block ; 
 int /*<<< orphan*/  dce_virtual_ip_block ; 
 int /*<<< orphan*/  dm_ip_block ; 
 int /*<<< orphan*/  gfx_v7_1_ip_block ; 
 int /*<<< orphan*/  gfx_v7_2_ip_block ; 
 int /*<<< orphan*/  gfx_v7_3_ip_block ; 
 int /*<<< orphan*/  gmc_v7_0_ip_block ; 
 int /*<<< orphan*/  kv_smu_ip_block ; 
 int /*<<< orphan*/  pp_smu_ip_block ; 
 int /*<<< orphan*/  uvd_v4_2_ip_block ; 
 int /*<<< orphan*/  vce_v2_0_ip_block ; 

int cik_set_ip_blocks(struct amdgpu_device *adev)
{
	cik_detect_hw_virtualization(adev);

	switch (adev->asic_type) {
	case CHIP_BONAIRE:
		amdgpu_device_ip_block_add(adev, &cik_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v7_0_ip_block);
		amdgpu_device_ip_block_add(adev, &cik_ih_ip_block);
		amdgpu_device_ip_block_add(adev, &gfx_v7_2_ip_block);
		amdgpu_device_ip_block_add(adev, &cik_sdma_ip_block);
		amdgpu_device_ip_block_add(adev, &pp_smu_ip_block);
		if (adev->enable_virtual_display)
			amdgpu_device_ip_block_add(adev, &dce_virtual_ip_block);
#if defined(CONFIG_DRM_AMD_DC)
		else if (amdgpu_device_has_dc_support(adev))
			amdgpu_device_ip_block_add(adev, &dm_ip_block);
#endif
		else
			amdgpu_device_ip_block_add(adev, &dce_v8_2_ip_block);
		amdgpu_device_ip_block_add(adev, &uvd_v4_2_ip_block);
		amdgpu_device_ip_block_add(adev, &vce_v2_0_ip_block);
		break;
	case CHIP_HAWAII:
		amdgpu_device_ip_block_add(adev, &cik_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v7_0_ip_block);
		amdgpu_device_ip_block_add(adev, &cik_ih_ip_block);
		amdgpu_device_ip_block_add(adev, &gfx_v7_3_ip_block);
		amdgpu_device_ip_block_add(adev, &cik_sdma_ip_block);
		amdgpu_device_ip_block_add(adev, &pp_smu_ip_block);
		if (adev->enable_virtual_display)
			amdgpu_device_ip_block_add(adev, &dce_virtual_ip_block);
#if defined(CONFIG_DRM_AMD_DC)
		else if (amdgpu_device_has_dc_support(adev))
			amdgpu_device_ip_block_add(adev, &dm_ip_block);
#endif
		else
			amdgpu_device_ip_block_add(adev, &dce_v8_5_ip_block);
		amdgpu_device_ip_block_add(adev, &uvd_v4_2_ip_block);
		amdgpu_device_ip_block_add(adev, &vce_v2_0_ip_block);
		break;
	case CHIP_KAVERI:
		amdgpu_device_ip_block_add(adev, &cik_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v7_0_ip_block);
		amdgpu_device_ip_block_add(adev, &cik_ih_ip_block);
		amdgpu_device_ip_block_add(adev, &gfx_v7_1_ip_block);
		amdgpu_device_ip_block_add(adev, &cik_sdma_ip_block);
		amdgpu_device_ip_block_add(adev, &kv_smu_ip_block);
		if (adev->enable_virtual_display)
			amdgpu_device_ip_block_add(adev, &dce_virtual_ip_block);
#if defined(CONFIG_DRM_AMD_DC)
		else if (amdgpu_device_has_dc_support(adev))
			amdgpu_device_ip_block_add(adev, &dm_ip_block);
#endif
		else
			amdgpu_device_ip_block_add(adev, &dce_v8_1_ip_block);

		amdgpu_device_ip_block_add(adev, &uvd_v4_2_ip_block);
		amdgpu_device_ip_block_add(adev, &vce_v2_0_ip_block);
		break;
	case CHIP_KABINI:
	case CHIP_MULLINS:
		amdgpu_device_ip_block_add(adev, &cik_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v7_0_ip_block);
		amdgpu_device_ip_block_add(adev, &cik_ih_ip_block);
		amdgpu_device_ip_block_add(adev, &gfx_v7_2_ip_block);
		amdgpu_device_ip_block_add(adev, &cik_sdma_ip_block);
		amdgpu_device_ip_block_add(adev, &kv_smu_ip_block);
		if (adev->enable_virtual_display)
			amdgpu_device_ip_block_add(adev, &dce_virtual_ip_block);
#if defined(CONFIG_DRM_AMD_DC)
		else if (amdgpu_device_has_dc_support(adev))
			amdgpu_device_ip_block_add(adev, &dm_ip_block);
#endif
		else
			amdgpu_device_ip_block_add(adev, &dce_v8_3_ip_block);
		amdgpu_device_ip_block_add(adev, &uvd_v4_2_ip_block);
		amdgpu_device_ip_block_add(adev, &vce_v2_0_ip_block);
		break;
	default:
		/* FIXME: not supported yet */
		return -EINVAL;
	}
	return 0;
}