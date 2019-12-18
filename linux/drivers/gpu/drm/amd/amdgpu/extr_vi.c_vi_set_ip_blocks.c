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
struct TYPE_2__ {int /*<<< orphan*/ * ops; } ;
struct amdgpu_device {int asic_type; int /*<<< orphan*/  enable_virtual_display; TYPE_1__ virt; } ;

/* Variables and functions */
#define  CHIP_CARRIZO 136 
#define  CHIP_FIJI 135 
#define  CHIP_POLARIS10 134 
#define  CHIP_POLARIS11 133 
#define  CHIP_POLARIS12 132 
#define  CHIP_STONEY 131 
#define  CHIP_TONGA 130 
#define  CHIP_TOPAZ 129 
#define  CHIP_VEGAM 128 
 int EINVAL ; 
 int /*<<< orphan*/  acp_ip_block ; 
 int /*<<< orphan*/  amdgpu_device_has_dc_support (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_device_ip_block_add (struct amdgpu_device*,int /*<<< orphan*/ *) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  cz_ih_ip_block ; 
 int /*<<< orphan*/  dce_v10_0_ip_block ; 
 int /*<<< orphan*/  dce_v10_1_ip_block ; 
 int /*<<< orphan*/  dce_v11_0_ip_block ; 
 int /*<<< orphan*/  dce_v11_2_ip_block ; 
 int /*<<< orphan*/  dce_virtual_ip_block ; 
 int /*<<< orphan*/  dm_ip_block ; 
 int /*<<< orphan*/  gfx_v8_0_ip_block ; 
 int /*<<< orphan*/  gfx_v8_1_ip_block ; 
 int /*<<< orphan*/  gmc_v7_4_ip_block ; 
 int /*<<< orphan*/  gmc_v8_0_ip_block ; 
 int /*<<< orphan*/  gmc_v8_1_ip_block ; 
 int /*<<< orphan*/  gmc_v8_5_ip_block ; 
 int /*<<< orphan*/  iceland_ih_ip_block ; 
 int /*<<< orphan*/  pp_smu_ip_block ; 
 int /*<<< orphan*/  sdma_v2_4_ip_block ; 
 int /*<<< orphan*/  sdma_v3_0_ip_block ; 
 int /*<<< orphan*/  sdma_v3_1_ip_block ; 
 int /*<<< orphan*/  tonga_ih_ip_block ; 
 int /*<<< orphan*/  uvd_v5_0_ip_block ; 
 int /*<<< orphan*/  uvd_v6_0_ip_block ; 
 int /*<<< orphan*/  uvd_v6_2_ip_block ; 
 int /*<<< orphan*/  uvd_v6_3_ip_block ; 
 int /*<<< orphan*/  vce_v3_0_ip_block ; 
 int /*<<< orphan*/  vce_v3_1_ip_block ; 
 int /*<<< orphan*/  vce_v3_4_ip_block ; 
 int /*<<< orphan*/  vi_common_ip_block ; 
 int /*<<< orphan*/  vi_detect_hw_virtualization (struct amdgpu_device*) ; 
 int /*<<< orphan*/  xgpu_vi_virt_ops ; 

int vi_set_ip_blocks(struct amdgpu_device *adev)
{
	/* in early init stage, vbios code won't work */
	vi_detect_hw_virtualization(adev);

	if (amdgpu_sriov_vf(adev))
		adev->virt.ops = &xgpu_vi_virt_ops;

	switch (adev->asic_type) {
	case CHIP_TOPAZ:
		/* topaz has no DCE, UVD, VCE */
		amdgpu_device_ip_block_add(adev, &vi_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v7_4_ip_block);
		amdgpu_device_ip_block_add(adev, &iceland_ih_ip_block);
		amdgpu_device_ip_block_add(adev, &gfx_v8_0_ip_block);
		amdgpu_device_ip_block_add(adev, &sdma_v2_4_ip_block);
		amdgpu_device_ip_block_add(adev, &pp_smu_ip_block);
		if (adev->enable_virtual_display)
			amdgpu_device_ip_block_add(adev, &dce_virtual_ip_block);
		break;
	case CHIP_FIJI:
		amdgpu_device_ip_block_add(adev, &vi_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v8_5_ip_block);
		amdgpu_device_ip_block_add(adev, &tonga_ih_ip_block);
		amdgpu_device_ip_block_add(adev, &gfx_v8_0_ip_block);
		amdgpu_device_ip_block_add(adev, &sdma_v3_0_ip_block);
		amdgpu_device_ip_block_add(adev, &pp_smu_ip_block);
		if (adev->enable_virtual_display || amdgpu_sriov_vf(adev))
			amdgpu_device_ip_block_add(adev, &dce_virtual_ip_block);
#if defined(CONFIG_DRM_AMD_DC)
		else if (amdgpu_device_has_dc_support(adev))
			amdgpu_device_ip_block_add(adev, &dm_ip_block);
#endif
		else
			amdgpu_device_ip_block_add(adev, &dce_v10_1_ip_block);
		if (!amdgpu_sriov_vf(adev)) {
			amdgpu_device_ip_block_add(adev, &uvd_v6_0_ip_block);
			amdgpu_device_ip_block_add(adev, &vce_v3_0_ip_block);
		}
		break;
	case CHIP_TONGA:
		amdgpu_device_ip_block_add(adev, &vi_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v8_0_ip_block);
		amdgpu_device_ip_block_add(adev, &tonga_ih_ip_block);
		amdgpu_device_ip_block_add(adev, &gfx_v8_0_ip_block);
		amdgpu_device_ip_block_add(adev, &sdma_v3_0_ip_block);
		amdgpu_device_ip_block_add(adev, &pp_smu_ip_block);
		if (adev->enable_virtual_display || amdgpu_sriov_vf(adev))
			amdgpu_device_ip_block_add(adev, &dce_virtual_ip_block);
#if defined(CONFIG_DRM_AMD_DC)
		else if (amdgpu_device_has_dc_support(adev))
			amdgpu_device_ip_block_add(adev, &dm_ip_block);
#endif
		else
			amdgpu_device_ip_block_add(adev, &dce_v10_0_ip_block);
		if (!amdgpu_sriov_vf(adev)) {
			amdgpu_device_ip_block_add(adev, &uvd_v5_0_ip_block);
			amdgpu_device_ip_block_add(adev, &vce_v3_0_ip_block);
		}
		break;
	case CHIP_POLARIS10:
	case CHIP_POLARIS11:
	case CHIP_POLARIS12:
	case CHIP_VEGAM:
		amdgpu_device_ip_block_add(adev, &vi_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v8_1_ip_block);
		amdgpu_device_ip_block_add(adev, &tonga_ih_ip_block);
		amdgpu_device_ip_block_add(adev, &gfx_v8_0_ip_block);
		amdgpu_device_ip_block_add(adev, &sdma_v3_1_ip_block);
		amdgpu_device_ip_block_add(adev, &pp_smu_ip_block);
		if (adev->enable_virtual_display)
			amdgpu_device_ip_block_add(adev, &dce_virtual_ip_block);
#if defined(CONFIG_DRM_AMD_DC)
		else if (amdgpu_device_has_dc_support(adev))
			amdgpu_device_ip_block_add(adev, &dm_ip_block);
#endif
		else
			amdgpu_device_ip_block_add(adev, &dce_v11_2_ip_block);
		amdgpu_device_ip_block_add(adev, &uvd_v6_3_ip_block);
		amdgpu_device_ip_block_add(adev, &vce_v3_4_ip_block);
		break;
	case CHIP_CARRIZO:
		amdgpu_device_ip_block_add(adev, &vi_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v8_0_ip_block);
		amdgpu_device_ip_block_add(adev, &cz_ih_ip_block);
		amdgpu_device_ip_block_add(adev, &gfx_v8_0_ip_block);
		amdgpu_device_ip_block_add(adev, &sdma_v3_0_ip_block);
		amdgpu_device_ip_block_add(adev, &pp_smu_ip_block);
		if (adev->enable_virtual_display)
			amdgpu_device_ip_block_add(adev, &dce_virtual_ip_block);
#if defined(CONFIG_DRM_AMD_DC)
		else if (amdgpu_device_has_dc_support(adev))
			amdgpu_device_ip_block_add(adev, &dm_ip_block);
#endif
		else
			amdgpu_device_ip_block_add(adev, &dce_v11_0_ip_block);
		amdgpu_device_ip_block_add(adev, &uvd_v6_0_ip_block);
		amdgpu_device_ip_block_add(adev, &vce_v3_1_ip_block);
#if defined(CONFIG_DRM_AMD_ACP)
		amdgpu_device_ip_block_add(adev, &acp_ip_block);
#endif
		break;
	case CHIP_STONEY:
		amdgpu_device_ip_block_add(adev, &vi_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v8_0_ip_block);
		amdgpu_device_ip_block_add(adev, &cz_ih_ip_block);
		amdgpu_device_ip_block_add(adev, &gfx_v8_1_ip_block);
		amdgpu_device_ip_block_add(adev, &sdma_v3_0_ip_block);
		amdgpu_device_ip_block_add(adev, &pp_smu_ip_block);
		if (adev->enable_virtual_display)
			amdgpu_device_ip_block_add(adev, &dce_virtual_ip_block);
#if defined(CONFIG_DRM_AMD_DC)
		else if (amdgpu_device_has_dc_support(adev))
			amdgpu_device_ip_block_add(adev, &dm_ip_block);
#endif
		else
			amdgpu_device_ip_block_add(adev, &dce_v11_0_ip_block);
		amdgpu_device_ip_block_add(adev, &uvd_v6_2_ip_block);
		amdgpu_device_ip_block_add(adev, &vce_v3_4_ip_block);
#if defined(CONFIG_DRM_AMD_ACP)
		amdgpu_device_ip_block_add(adev, &acp_ip_block);
#endif
		break;
	default:
		/* FIXME: not supported yet */
		return -EINVAL;
	}

	return 0;
}