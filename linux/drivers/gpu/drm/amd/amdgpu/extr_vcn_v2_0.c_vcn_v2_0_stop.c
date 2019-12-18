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
typedef  int uint32_t ;
struct TYPE_2__ {scalar_t__ dpm_enabled; } ;
struct amdgpu_device {int pg_flags; TYPE_1__ pm; } ;

/* Variables and functions */
 int AMD_PG_SUPPORT_VCN_DPG ; 
 int RREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC15_WAIT_ON_RREG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  UVD ; 
 int UVD_LMI_CTRL2__STALL_ARB_UMC_MASK ; 
 int UVD_LMI_STATUS__READ_CLEAN_MASK ; 
 int UVD_LMI_STATUS__UMC_READ_CLEAN_RAW_MASK ; 
 int UVD_LMI_STATUS__UMC_WRITE_CLEAN_RAW_MASK ; 
 int UVD_LMI_STATUS__VCPU_LMI_WRITE_CLEAN_MASK ; 
 int UVD_LMI_STATUS__WRITE_CLEAN_MASK ; 
 int UVD_LMI_STATUS__WRITE_CLEAN_RAW_MASK ; 
 int /*<<< orphan*/  UVD_SOFT_RESET__LMI_SOFT_RESET_MASK ; 
 int /*<<< orphan*/  UVD_SOFT_RESET__LMI_UMC_SOFT_RESET_MASK ; 
 int /*<<< orphan*/  UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK ; 
 int UVD_STATUS__IDLE ; 
 int /*<<< orphan*/  UVD_VCPU_CNTL__CLK_EN_MASK ; 
 int /*<<< orphan*/  VCN ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  amdgpu_dpm_enable_uvd (struct amdgpu_device*,int) ; 
 int jpeg_v2_0_stop (struct amdgpu_device*) ; 
 int /*<<< orphan*/  mmUVD_LMI_CTRL2 ; 
 int /*<<< orphan*/  mmUVD_LMI_STATUS ; 
 int /*<<< orphan*/  mmUVD_SOFT_RESET ; 
 int /*<<< orphan*/  mmUVD_STATUS ; 
 int /*<<< orphan*/  mmUVD_VCPU_CNTL ; 
 int /*<<< orphan*/  vcn_v2_0_enable_clock_gating (struct amdgpu_device*) ; 
 int /*<<< orphan*/  vcn_v2_0_enable_static_power_gating (struct amdgpu_device*) ; 
 int vcn_v2_0_stop_dpg_mode (struct amdgpu_device*) ; 

__attribute__((used)) static int vcn_v2_0_stop(struct amdgpu_device *adev)
{
	uint32_t tmp;
	int r;

	r = jpeg_v2_0_stop(adev);
	if (r)
		return r;

	if (adev->pg_flags & AMD_PG_SUPPORT_VCN_DPG) {
		r = vcn_v2_0_stop_dpg_mode(adev);
		if (r)
			return r;
		goto power_off;
	}

	/* wait for uvd idle */
	SOC15_WAIT_ON_RREG(VCN, 0, mmUVD_STATUS, UVD_STATUS__IDLE, 0x7, r);
	if (r)
		return r;

	tmp = UVD_LMI_STATUS__VCPU_LMI_WRITE_CLEAN_MASK |
		UVD_LMI_STATUS__READ_CLEAN_MASK |
		UVD_LMI_STATUS__WRITE_CLEAN_MASK |
		UVD_LMI_STATUS__WRITE_CLEAN_RAW_MASK;
	SOC15_WAIT_ON_RREG(VCN, 0, mmUVD_LMI_STATUS, tmp, tmp, r);
	if (r)
		return r;

	/* stall UMC channel */
	tmp = RREG32_SOC15(VCN, 0, mmUVD_LMI_CTRL2);
	tmp |= UVD_LMI_CTRL2__STALL_ARB_UMC_MASK;
	WREG32_SOC15(VCN, 0, mmUVD_LMI_CTRL2, tmp);

	tmp = UVD_LMI_STATUS__UMC_READ_CLEAN_RAW_MASK|
		UVD_LMI_STATUS__UMC_WRITE_CLEAN_RAW_MASK;
	SOC15_WAIT_ON_RREG(VCN, 0, mmUVD_LMI_STATUS, tmp, tmp, r);
	if (r)
		return r;

	/* disable VCPU clock */
	WREG32_P(SOC15_REG_OFFSET(UVD, 0, mmUVD_VCPU_CNTL), 0,
		~(UVD_VCPU_CNTL__CLK_EN_MASK));

	/* reset LMI UMC */
	WREG32_P(SOC15_REG_OFFSET(UVD, 0, mmUVD_SOFT_RESET),
		UVD_SOFT_RESET__LMI_UMC_SOFT_RESET_MASK,
		~UVD_SOFT_RESET__LMI_UMC_SOFT_RESET_MASK);

	/* reset LMI */
	WREG32_P(SOC15_REG_OFFSET(UVD, 0, mmUVD_SOFT_RESET),
		UVD_SOFT_RESET__LMI_SOFT_RESET_MASK,
		~UVD_SOFT_RESET__LMI_SOFT_RESET_MASK);

	/* reset VCPU */
	WREG32_P(SOC15_REG_OFFSET(UVD, 0, mmUVD_SOFT_RESET),
		UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK,
		~UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK);

	/* clear status */
	WREG32_SOC15(VCN, 0, mmUVD_STATUS, 0);

	vcn_v2_0_enable_clock_gating(adev);
	vcn_v2_0_enable_static_power_gating(adev);

power_off:
	if (adev->pm.dpm_enabled)
		amdgpu_dpm_enable_uvd(adev, false);

	return 0;
}