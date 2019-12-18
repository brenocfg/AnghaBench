#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  load_type; } ;
struct TYPE_10__ {int /*<<< orphan*/ * ops; } ;
struct TYPE_8__ {int supported; } ;
struct TYPE_9__ {TYPE_1__ xgmi; } ;
struct amdgpu_device {int asic_type; int flags; int /*<<< orphan*/  enable_virtual_display; TYPE_4__ firmware; TYPE_3__ virt; TYPE_5__* nbio_funcs; int /*<<< orphan*/  rev_id; int /*<<< orphan*/ * df_funcs; TYPE_2__ gmc; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* detect_hw_virt ) (struct amdgpu_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_FW_LOAD_PSP ; 
 int AMD_IS_APU ; 
#define  CHIP_ARCTURUS 133 
#define  CHIP_RAVEN 132 
#define  CHIP_RENOIR 131 
#define  CHIP_VEGA10 130 
#define  CHIP_VEGA12 129 
#define  CHIP_VEGA20 128 
 int EINVAL ; 
 int /*<<< orphan*/  amdgpu_device_has_dc_support (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_device_ip_block_add (struct amdgpu_device*,int /*<<< orphan*/ *) ; 
 scalar_t__ amdgpu_sriov_vf (struct amdgpu_device*) ; 
 int /*<<< orphan*/  arct_reg_base_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  dce_virtual_ip_block ; 
 int /*<<< orphan*/  df_v1_7_funcs ; 
 int /*<<< orphan*/  df_v3_6_funcs ; 
 int /*<<< orphan*/  dm_ip_block ; 
 int /*<<< orphan*/  gfx_v9_0_ip_block ; 
 int /*<<< orphan*/  gmc_v9_0_ip_block ; 
 int /*<<< orphan*/  is_support_sw_smu (struct amdgpu_device*) ; 
 int /*<<< orphan*/  likely (int) ; 
 TYPE_5__ nbio_v6_1_funcs ; 
 TYPE_5__ nbio_v7_0_funcs ; 
 TYPE_5__ nbio_v7_4_funcs ; 
 int /*<<< orphan*/  pp_smu_ip_block ; 
 int /*<<< orphan*/  psp_v10_0_ip_block ; 
 int /*<<< orphan*/  psp_v11_0_ip_block ; 
 int /*<<< orphan*/  psp_v12_0_ip_block ; 
 int /*<<< orphan*/  psp_v3_1_ip_block ; 
 int /*<<< orphan*/  sdma_v4_0_ip_block ; 
 int /*<<< orphan*/  smu_v11_0_ip_block ; 
 int /*<<< orphan*/  smu_v12_0_ip_block ; 
 int /*<<< orphan*/  soc15_get_rev_id (struct amdgpu_device*) ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_device*) ; 
 int /*<<< orphan*/  uvd_v7_0_ip_block ; 
 int /*<<< orphan*/  vce_v4_0_ip_block ; 
 int /*<<< orphan*/  vcn_v1_0_ip_block ; 
 int /*<<< orphan*/  vcn_v2_0_ip_block ; 
 int /*<<< orphan*/  vcn_v2_5_ip_block ; 
 int /*<<< orphan*/  vega10_common_ip_block ; 
 int /*<<< orphan*/  vega10_ih_ip_block ; 
 int /*<<< orphan*/  vega10_reg_base_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  vega20_reg_base_init (struct amdgpu_device*) ; 
 int /*<<< orphan*/  xgpu_ai_virt_ops ; 

int soc15_set_ip_blocks(struct amdgpu_device *adev)
{
	/* Set IP register base before any HW register access */
	switch (adev->asic_type) {
	case CHIP_VEGA10:
	case CHIP_VEGA12:
	case CHIP_RAVEN:
	case CHIP_RENOIR:
		vega10_reg_base_init(adev);
		break;
	case CHIP_VEGA20:
		vega20_reg_base_init(adev);
		break;
	case CHIP_ARCTURUS:
		arct_reg_base_init(adev);
		break;
	default:
		return -EINVAL;
	}

	if (adev->asic_type == CHIP_VEGA20 || adev->asic_type == CHIP_ARCTURUS)
		adev->gmc.xgmi.supported = true;

	if (adev->flags & AMD_IS_APU)
		adev->nbio_funcs = &nbio_v7_0_funcs;
	else if (adev->asic_type == CHIP_VEGA20 ||
		adev->asic_type == CHIP_ARCTURUS)
		adev->nbio_funcs = &nbio_v7_4_funcs;
	else
		adev->nbio_funcs = &nbio_v6_1_funcs;

	if (adev->asic_type == CHIP_VEGA20 || adev->asic_type == CHIP_ARCTURUS)
		adev->df_funcs = &df_v3_6_funcs;
	else
		adev->df_funcs = &df_v1_7_funcs;

	adev->rev_id = soc15_get_rev_id(adev);
	adev->nbio_funcs->detect_hw_virt(adev);

	if (amdgpu_sriov_vf(adev))
		adev->virt.ops = &xgpu_ai_virt_ops;

	switch (adev->asic_type) {
	case CHIP_VEGA10:
	case CHIP_VEGA12:
	case CHIP_VEGA20:
		amdgpu_device_ip_block_add(adev, &vega10_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v9_0_ip_block);

		/* For Vega10 SR-IOV, PSP need to be initialized before IH */
		if (amdgpu_sriov_vf(adev)) {
			if (likely(adev->firmware.load_type == AMDGPU_FW_LOAD_PSP)) {
				if (adev->asic_type == CHIP_VEGA20)
					amdgpu_device_ip_block_add(adev, &psp_v11_0_ip_block);
				else
					amdgpu_device_ip_block_add(adev, &psp_v3_1_ip_block);
			}
			amdgpu_device_ip_block_add(adev, &vega10_ih_ip_block);
		} else {
			amdgpu_device_ip_block_add(adev, &vega10_ih_ip_block);
			if (likely(adev->firmware.load_type == AMDGPU_FW_LOAD_PSP)) {
				if (adev->asic_type == CHIP_VEGA20)
					amdgpu_device_ip_block_add(adev, &psp_v11_0_ip_block);
				else
					amdgpu_device_ip_block_add(adev, &psp_v3_1_ip_block);
			}
		}
		amdgpu_device_ip_block_add(adev, &gfx_v9_0_ip_block);
		amdgpu_device_ip_block_add(adev, &sdma_v4_0_ip_block);
		if (!amdgpu_sriov_vf(adev)) {
			if (is_support_sw_smu(adev))
				amdgpu_device_ip_block_add(adev, &smu_v11_0_ip_block);
			else
				amdgpu_device_ip_block_add(adev, &pp_smu_ip_block);
		}
		if (adev->enable_virtual_display || amdgpu_sriov_vf(adev))
			amdgpu_device_ip_block_add(adev, &dce_virtual_ip_block);
#if defined(CONFIG_DRM_AMD_DC)
		else if (amdgpu_device_has_dc_support(adev))
			amdgpu_device_ip_block_add(adev, &dm_ip_block);
#endif
		if (!(adev->asic_type == CHIP_VEGA20 && amdgpu_sriov_vf(adev))) {
			amdgpu_device_ip_block_add(adev, &uvd_v7_0_ip_block);
			amdgpu_device_ip_block_add(adev, &vce_v4_0_ip_block);
		}
		break;
	case CHIP_RAVEN:
		amdgpu_device_ip_block_add(adev, &vega10_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v9_0_ip_block);
		amdgpu_device_ip_block_add(adev, &vega10_ih_ip_block);
		if (likely(adev->firmware.load_type == AMDGPU_FW_LOAD_PSP))
			amdgpu_device_ip_block_add(adev, &psp_v10_0_ip_block);
		amdgpu_device_ip_block_add(adev, &gfx_v9_0_ip_block);
		amdgpu_device_ip_block_add(adev, &sdma_v4_0_ip_block);
		amdgpu_device_ip_block_add(adev, &pp_smu_ip_block);
		if (adev->enable_virtual_display || amdgpu_sriov_vf(adev))
			amdgpu_device_ip_block_add(adev, &dce_virtual_ip_block);
#if defined(CONFIG_DRM_AMD_DC)
		else if (amdgpu_device_has_dc_support(adev))
			amdgpu_device_ip_block_add(adev, &dm_ip_block);
#endif
		amdgpu_device_ip_block_add(adev, &vcn_v1_0_ip_block);
		break;
	case CHIP_ARCTURUS:
		amdgpu_device_ip_block_add(adev, &vega10_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v9_0_ip_block);
		amdgpu_device_ip_block_add(adev, &vega10_ih_ip_block);
		if (adev->enable_virtual_display || amdgpu_sriov_vf(adev))
			amdgpu_device_ip_block_add(adev, &dce_virtual_ip_block);
		amdgpu_device_ip_block_add(adev, &gfx_v9_0_ip_block);
		amdgpu_device_ip_block_add(adev, &sdma_v4_0_ip_block);
		amdgpu_device_ip_block_add(adev, &smu_v11_0_ip_block);
		amdgpu_device_ip_block_add(adev, &vcn_v2_5_ip_block);
		break;
	case CHIP_RENOIR:
		amdgpu_device_ip_block_add(adev, &vega10_common_ip_block);
		amdgpu_device_ip_block_add(adev, &gmc_v9_0_ip_block);
		amdgpu_device_ip_block_add(adev, &vega10_ih_ip_block);
		if (likely(adev->firmware.load_type == AMDGPU_FW_LOAD_PSP))
			amdgpu_device_ip_block_add(adev, &psp_v12_0_ip_block);
		if (is_support_sw_smu(adev))
			amdgpu_device_ip_block_add(adev, &smu_v12_0_ip_block);
		amdgpu_device_ip_block_add(adev, &gfx_v9_0_ip_block);
		amdgpu_device_ip_block_add(adev, &sdma_v4_0_ip_block);
		if (adev->enable_virtual_display || amdgpu_sriov_vf(adev))
			amdgpu_device_ip_block_add(adev, &dce_virtual_ip_block);
#if defined(CONFIG_DRM_AMD_DC)
                else if (amdgpu_device_has_dc_support(adev))
                        amdgpu_device_ip_block_add(adev, &dm_ip_block);
#endif
		amdgpu_device_ip_block_add(adev, &vcn_v2_0_ip_block);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}