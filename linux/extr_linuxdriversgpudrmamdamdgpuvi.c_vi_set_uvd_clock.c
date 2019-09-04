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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
struct atom_clock_dividers {int post_divider; } ;
struct amdgpu_device {int flags; } ;

/* Variables and functions */
 int AMD_IS_APU ; 
 int CG_DCLK_CNTL__DCLK_DIR_CNTL_EN_MASK ; 
 int CG_DCLK_CNTL__DCLK_DIVIDER_MASK ; 
 int CG_DCLK_STATUS__DCLK_STATUS_MASK ; 
 int /*<<< orphan*/  COMPUTE_GPUCLK_INPUT_FLAG_DEFAULT_GPUCLK ; 
 int ETIMEDOUT ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 
 int amdgpu_atombios_get_clock_dividers (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct atom_clock_dividers*) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int vi_set_uvd_clock(struct amdgpu_device *adev, u32 clock,
			u32 cntl_reg, u32 status_reg)
{
	int r, i;
	struct atom_clock_dividers dividers;
	uint32_t tmp;

	r = amdgpu_atombios_get_clock_dividers(adev,
					       COMPUTE_GPUCLK_INPUT_FLAG_DEFAULT_GPUCLK,
					       clock, false, &dividers);
	if (r)
		return r;

	tmp = RREG32_SMC(cntl_reg);

	if (adev->flags & AMD_IS_APU)
		tmp &= ~CG_DCLK_CNTL__DCLK_DIVIDER_MASK;
	else
		tmp &= ~(CG_DCLK_CNTL__DCLK_DIR_CNTL_EN_MASK |
				CG_DCLK_CNTL__DCLK_DIVIDER_MASK);
	tmp |= dividers.post_divider;
	WREG32_SMC(cntl_reg, tmp);

	for (i = 0; i < 100; i++) {
		tmp = RREG32_SMC(status_reg);
		if (adev->flags & AMD_IS_APU) {
			if (tmp & 0x10000)
				break;
		} else {
			if (tmp & CG_DCLK_STATUS__DCLK_STATUS_MASK)
				break;
		}
		mdelay(10);
	}
	if (i == 100)
		return -ETIMEDOUT;
	return 0;
}