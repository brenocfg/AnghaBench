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
typedef  int u32 ;
struct atom_clock_dividers {int post_divider; } ;
struct amdgpu_device {int flags; } ;

/* Variables and functions */
 int AMD_IS_APU ; 
 int CG_ECLK_CNTL__ECLK_DIR_CNTL_EN_MASK ; 
 int CG_ECLK_CNTL__ECLK_DIVIDER_MASK ; 
 int CG_ECLK_STATUS__ECLK_STATUS_MASK ; 
 int /*<<< orphan*/  COMPUTE_GPUCLK_INPUT_FLAG_DEFAULT_GPUCLK ; 
 int ETIMEDOUT ; 
 int RREG32_SMC (int) ; 
 int /*<<< orphan*/  WREG32_SMC (int,int) ; 
 int amdgpu_atombios_get_clock_dividers (struct amdgpu_device*,int /*<<< orphan*/ ,int,int,struct atom_clock_dividers*) ; 
 int ixCG_ECLK_CNTL ; 
 int ixCG_ECLK_STATUS ; 
 int ixGNB_CLK3_DFS_CNTL ; 
 int ixGNB_CLK3_STATUS ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int vi_set_vce_clocks(struct amdgpu_device *adev, u32 evclk, u32 ecclk)
{
	int r, i;
	struct atom_clock_dividers dividers;
	u32 tmp;
	u32 reg_ctrl;
	u32 reg_status;
	u32 status_mask;
	u32 reg_mask;

	if (adev->flags & AMD_IS_APU) {
		reg_ctrl = ixGNB_CLK3_DFS_CNTL;
		reg_status = ixGNB_CLK3_STATUS;
		status_mask = 0x00010000;
		reg_mask = CG_ECLK_CNTL__ECLK_DIVIDER_MASK;
	} else {
		reg_ctrl = ixCG_ECLK_CNTL;
		reg_status = ixCG_ECLK_STATUS;
		status_mask = CG_ECLK_STATUS__ECLK_STATUS_MASK;
		reg_mask = CG_ECLK_CNTL__ECLK_DIR_CNTL_EN_MASK | CG_ECLK_CNTL__ECLK_DIVIDER_MASK;
	}

	r = amdgpu_atombios_get_clock_dividers(adev,
					       COMPUTE_GPUCLK_INPUT_FLAG_DEFAULT_GPUCLK,
					       ecclk, false, &dividers);
	if (r)
		return r;

	for (i = 0; i < 100; i++) {
		if (RREG32_SMC(reg_status) & status_mask)
			break;
		mdelay(10);
	}

	if (i == 100)
		return -ETIMEDOUT;

	tmp = RREG32_SMC(reg_ctrl);
	tmp &= ~reg_mask;
	tmp |= dividers.post_divider;
	WREG32_SMC(reg_ctrl, tmp);

	for (i = 0; i < 100; i++) {
		if (RREG32_SMC(reg_status) & status_mask)
			break;
		mdelay(10);
	}

	if (i == 100)
		return -ETIMEDOUT;

	return 0;
}