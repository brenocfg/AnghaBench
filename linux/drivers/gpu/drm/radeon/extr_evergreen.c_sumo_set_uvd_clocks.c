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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_DCLK_CNTL ; 
 int /*<<< orphan*/  CG_DCLK_STATUS ; 
 int /*<<< orphan*/  CG_SCRATCH1 ; 
 int /*<<< orphan*/  CG_VCLK_CNTL ; 
 int /*<<< orphan*/  CG_VCLK_STATUS ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int sumo_set_uvd_clock (struct radeon_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sumo_set_uvd_clocks(struct radeon_device *rdev, u32 vclk, u32 dclk)
{
	int r = 0;
	u32 cg_scratch = RREG32(CG_SCRATCH1);

	r = sumo_set_uvd_clock(rdev, vclk, CG_VCLK_CNTL, CG_VCLK_STATUS);
	if (r)
		goto done;
	cg_scratch &= 0xffff0000;
	cg_scratch |= vclk / 100; /* Mhz */

	r = sumo_set_uvd_clock(rdev, dclk, CG_DCLK_CNTL, CG_DCLK_STATUS);
	if (r)
		goto done;
	cg_scratch &= 0x0000ffff;
	cg_scratch |= (dclk / 100) << 16; /* Mhz */

done:
	WREG32(CG_SCRATCH1, cg_scratch);

	return r;
}