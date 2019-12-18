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
typedef  int /*<<< orphan*/  u32 ;
struct radeon_device {int dummy; } ;
struct atom_clock_dividers {int /*<<< orphan*/  post_div; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_ECLK_CNTL ; 
 int /*<<< orphan*/  CG_ECLK_STATUS ; 
 int /*<<< orphan*/  COMPUTE_ENGINE_PLL_PARAM ; 
 int ECLK_DIR_CNTL_EN ; 
 int ECLK_DIVIDER_MASK ; 
 int ECLK_STATUS ; 
 int ETIMEDOUT ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int radeon_atom_get_clock_dividers (struct radeon_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct atom_clock_dividers*) ; 

int tn_set_vce_clocks(struct radeon_device *rdev, u32 evclk, u32 ecclk)
{
	struct atom_clock_dividers dividers;
	int r, i;

	r = radeon_atom_get_clock_dividers(rdev, COMPUTE_ENGINE_PLL_PARAM,
					   ecclk, false, &dividers);
	if (r)
		return r;

	for (i = 0; i < 100; i++) {
		if (RREG32(CG_ECLK_STATUS) & ECLK_STATUS)
			break;
		mdelay(10);
	}
	if (i == 100)
		return -ETIMEDOUT;

	WREG32_P(CG_ECLK_CNTL, dividers.post_div, ~(ECLK_DIR_CNTL_EN|ECLK_DIVIDER_MASK));

	for (i = 0; i < 100; i++) {
		if (RREG32(CG_ECLK_STATUS) & ECLK_STATUS)
			break;
		mdelay(10);
	}
	if (i == 100)
		return -ETIMEDOUT;

	return 0;
}