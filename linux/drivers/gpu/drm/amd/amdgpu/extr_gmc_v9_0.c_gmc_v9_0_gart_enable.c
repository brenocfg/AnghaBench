#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int ready; int /*<<< orphan*/ * bo; } ;
struct TYPE_5__ {int vram_start; int gart_size; } ;
struct amdgpu_device {int asic_type; int num_vmhubs; TYPE_3__ gart; TYPE_2__ gmc; TYPE_1__* nbio_funcs; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* hdp_flush ) (struct amdgpu_device*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ AMDGPU_VM_FAULT_STOP_ALWAYS ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int CHIP_ARCTURUS ; 
#define  CHIP_RAVEN 128 
 int /*<<< orphan*/  DRM_INFO (char*,unsigned int,unsigned long long) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FLUSH_INVALIDATE_CACHE ; 
 int /*<<< orphan*/  HDP ; 
 int /*<<< orphan*/  HDP_MISC_CNTL ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_FIELD15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ amdgpu_bo_gpu_offset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_device_program_register_sequence (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int amdgpu_gart_table_vram_pin (struct amdgpu_device*) ; 
 scalar_t__ amdgpu_vm_fault_stop ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int gfxhub_v1_0_gart_enable (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gfxhub_v1_0_set_fault_enable_default (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  gmc_v9_0_flush_gpu_tlb (struct amdgpu_device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  golden_settings_vega10_hdp ; 
 int /*<<< orphan*/  mmHDP_HOST_PATH_CNTL ; 
 int /*<<< orphan*/  mmHDP_NONSURFACE_BASE ; 
 int /*<<< orphan*/  mmHDP_NONSURFACE_BASE_HI ; 
 int mmhub_v1_0_gart_enable (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmhub_v1_0_set_fault_enable_default (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  mmhub_v1_0_update_power_gating (struct amdgpu_device*,int) ; 
 int mmhub_v9_4_gart_enable (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmhub_v9_4_set_fault_enable_default (struct amdgpu_device*,int) ; 
 int /*<<< orphan*/  stub1 (struct amdgpu_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gmc_v9_0_gart_enable(struct amdgpu_device *adev)
{
	int r, i;
	bool value;
	u32 tmp;

	amdgpu_device_program_register_sequence(adev,
						golden_settings_vega10_hdp,
						ARRAY_SIZE(golden_settings_vega10_hdp));

	if (adev->gart.bo == NULL) {
		dev_err(adev->dev, "No VRAM object for PCIE GART.\n");
		return -EINVAL;
	}
	r = amdgpu_gart_table_vram_pin(adev);
	if (r)
		return r;

	switch (adev->asic_type) {
	case CHIP_RAVEN:
		/* TODO for renoir */
		mmhub_v1_0_update_power_gating(adev, true);
		break;
	default:
		break;
	}

	r = gfxhub_v1_0_gart_enable(adev);
	if (r)
		return r;

	if (adev->asic_type == CHIP_ARCTURUS)
		r = mmhub_v9_4_gart_enable(adev);
	else
		r = mmhub_v1_0_gart_enable(adev);
	if (r)
		return r;

	WREG32_FIELD15(HDP, 0, HDP_MISC_CNTL, FLUSH_INVALIDATE_CACHE, 1);

	tmp = RREG32_SOC15(HDP, 0, mmHDP_HOST_PATH_CNTL);
	WREG32_SOC15(HDP, 0, mmHDP_HOST_PATH_CNTL, tmp);

	WREG32_SOC15(HDP, 0, mmHDP_NONSURFACE_BASE, (adev->gmc.vram_start >> 8));
	WREG32_SOC15(HDP, 0, mmHDP_NONSURFACE_BASE_HI, (adev->gmc.vram_start >> 40));

	/* After HDP is initialized, flush HDP.*/
	adev->nbio_funcs->hdp_flush(adev, NULL);

	if (amdgpu_vm_fault_stop == AMDGPU_VM_FAULT_STOP_ALWAYS)
		value = false;
	else
		value = true;

	gfxhub_v1_0_set_fault_enable_default(adev, value);
	if (adev->asic_type == CHIP_ARCTURUS)
		mmhub_v9_4_set_fault_enable_default(adev, value);
	else
		mmhub_v1_0_set_fault_enable_default(adev, value);

	for (i = 0; i < adev->num_vmhubs; ++i)
		gmc_v9_0_flush_gpu_tlb(adev, 0, i, 0);

	DRM_INFO("PCIE GART of %uM enabled (table at 0x%016llX).\n",
		 (unsigned)(adev->gmc.gart_size >> 20),
		 (unsigned long long)amdgpu_bo_gpu_offset(adev->gart.bo));
	adev->gart.ready = true;
	return 0;
}