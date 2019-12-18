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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int CG_ECLK_CNTL__ECLK_DIR_CNTL_EN_MASK ; 
 int CG_ECLK_CNTL__ECLK_DIVIDER_MASK ; 
 int CG_ECLK_STATUS__ECLK_STATUS_MASK ; 
 int /*<<< orphan*/  COMPUTE_GPUCLK_INPUT_FLAG_DEFAULT_GPUCLK ; 
 int ETIMEDOUT ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 
 int amdgpu_atombios_get_clock_dividers (struct amdgpu_device*,int /*<<< orphan*/ ,int,int,struct atom_clock_dividers*) ; 
 int /*<<< orphan*/  ixCG_ECLK_CNTL ; 
 int /*<<< orphan*/  ixCG_ECLK_STATUS ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int cik_set_vce_clocks(struct amdgpu_device *adev, u32 evclk, u32 ecclk)
{
	int r, i;
	struct atom_clock_dividers dividers;
	u32 tmp;

	r = amdgpu_atombios_get_clock_dividers(adev,
					       COMPUTE_GPUCLK_INPUT_FLAG_DEFAULT_GPUCLK,
					       ecclk, false, &dividers);
	if (r)
		return r;

	for (i = 0; i < 100; i++) {
		if (RREG32_SMC(ixCG_ECLK_STATUS) & CG_ECLK_STATUS__ECLK_STATUS_MASK)
			break;
		mdelay(10);
	}
	if (i == 100)
		return -ETIMEDOUT;

	tmp = RREG32_SMC(ixCG_ECLK_CNTL);
	tmp &= ~(CG_ECLK_CNTL__ECLK_DIR_CNTL_EN_MASK |
		CG_ECLK_CNTL__ECLK_DIVIDER_MASK);
	tmp |= dividers.post_divider;
	WREG32_SMC(ixCG_ECLK_CNTL, tmp);

	for (i = 0; i < 100; i++) {
		if (RREG32_SMC(ixCG_ECLK_STATUS) & CG_ECLK_STATUS__ECLK_STATUS_MASK)
			break;
		mdelay(10);
	}
	if (i == 100)
		return -ETIMEDOUT;

	return 0;
}