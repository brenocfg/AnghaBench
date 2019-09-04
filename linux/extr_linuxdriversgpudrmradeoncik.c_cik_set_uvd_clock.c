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
struct radeon_device {int dummy; } ;
struct atom_clock_dividers {int post_divider; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPUTE_GPUCLK_INPUT_FLAG_DEFAULT_GPUCLK ; 
 int DCLK_DIR_CNTL_EN ; 
 int DCLK_DIVIDER_MASK ; 
 int DCLK_STATUS ; 
 int ETIMEDOUT ; 
 int RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int radeon_atom_get_clock_dividers (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct atom_clock_dividers*) ; 

__attribute__((used)) static int cik_set_uvd_clock(struct radeon_device *rdev, u32 clock,
			     u32 cntl_reg, u32 status_reg)
{
	int r, i;
	struct atom_clock_dividers dividers;
	uint32_t tmp;

	r = radeon_atom_get_clock_dividers(rdev, COMPUTE_GPUCLK_INPUT_FLAG_DEFAULT_GPUCLK,
					   clock, false, &dividers);
	if (r)
		return r;

	tmp = RREG32_SMC(cntl_reg);
	tmp &= ~(DCLK_DIR_CNTL_EN|DCLK_DIVIDER_MASK);
	tmp |= dividers.post_divider;
	WREG32_SMC(cntl_reg, tmp);

	for (i = 0; i < 100; i++) {
		if (RREG32_SMC(status_reg) & DCLK_STATUS)
			break;
		mdelay(10);
	}
	if (i == 100)
		return -ETIMEDOUT;

	return 0;
}