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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOC15_REG_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOC15_WAIT_ON_RREG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  UVD ; 
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
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SOC15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmUVD_LMI_STATUS ; 
 int /*<<< orphan*/  mmUVD_SOFT_RESET ; 
 int /*<<< orphan*/  mmUVD_STATUS ; 
 int /*<<< orphan*/  mmUVD_VCPU_CNTL ; 
 int /*<<< orphan*/  vcn_1_0_enable_static_power_gating (struct amdgpu_device*) ; 
 int /*<<< orphan*/  vcn_v1_0_enable_clock_gating (struct amdgpu_device*) ; 

__attribute__((used)) static int vcn_v1_0_stop_spg_mode(struct amdgpu_device *adev)
{
	int ret_code, tmp;

	SOC15_WAIT_ON_RREG(UVD, 0, mmUVD_STATUS, UVD_STATUS__IDLE, 0x7, ret_code);

	tmp = UVD_LMI_STATUS__VCPU_LMI_WRITE_CLEAN_MASK |
		UVD_LMI_STATUS__READ_CLEAN_MASK |
		UVD_LMI_STATUS__WRITE_CLEAN_MASK |
		UVD_LMI_STATUS__WRITE_CLEAN_RAW_MASK;
	SOC15_WAIT_ON_RREG(UVD, 0, mmUVD_LMI_STATUS, tmp, tmp, ret_code);

	/* put VCPU into reset */
	WREG32_P(SOC15_REG_OFFSET(UVD, 0, mmUVD_SOFT_RESET),
		UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK,
		~UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK);

	tmp = UVD_LMI_STATUS__UMC_READ_CLEAN_RAW_MASK |
		UVD_LMI_STATUS__UMC_WRITE_CLEAN_RAW_MASK;
	SOC15_WAIT_ON_RREG(UVD, 0, mmUVD_LMI_STATUS, tmp, tmp, ret_code);

	/* disable VCPU clock */
	WREG32_P(SOC15_REG_OFFSET(UVD, 0, mmUVD_VCPU_CNTL), 0,
		~UVD_VCPU_CNTL__CLK_EN_MASK);

	/* reset LMI UMC/LMI */
	WREG32_P(SOC15_REG_OFFSET(UVD, 0, mmUVD_SOFT_RESET),
		UVD_SOFT_RESET__LMI_UMC_SOFT_RESET_MASK,
		~UVD_SOFT_RESET__LMI_UMC_SOFT_RESET_MASK);

	WREG32_P(SOC15_REG_OFFSET(UVD, 0, mmUVD_SOFT_RESET),
		UVD_SOFT_RESET__LMI_SOFT_RESET_MASK,
		~UVD_SOFT_RESET__LMI_SOFT_RESET_MASK);

	WREG32_SOC15(UVD, 0, mmUVD_STATUS, 0);

	vcn_v1_0_enable_clock_gating(adev);
	vcn_1_0_enable_static_power_gating(adev);
	return 0;
}