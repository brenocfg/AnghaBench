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
struct radeon_device {scalar_t__ family; } ;

/* Variables and functions */
 scalar_t__ CHIP_RV250 ; 
 scalar_t__ CHIP_RV280 ; 
 int RREG32_PLL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_00000D_SCLK_CNTL ; 
 int S_00000D_FORCE_CP (int) ; 
 int S_00000D_FORCE_DISP1 (int) ; 
 int S_00000D_FORCE_DISP2 (int) ; 
 int S_00000D_FORCE_VIP (int) ; 
 int /*<<< orphan*/  WREG32_PLL (int /*<<< orphan*/ ,int) ; 
 int radeon_dynclks ; 
 int /*<<< orphan*/  radeon_legacy_set_clock_gating (struct radeon_device*,int) ; 

__attribute__((used)) static void r100_clock_startup(struct radeon_device *rdev)
{
	u32 tmp;

	if (radeon_dynclks != -1 && radeon_dynclks)
		radeon_legacy_set_clock_gating(rdev, 1);
	/* We need to force on some of the block */
	tmp = RREG32_PLL(R_00000D_SCLK_CNTL);
	tmp |= S_00000D_FORCE_CP(1) | S_00000D_FORCE_VIP(1);
	if ((rdev->family == CHIP_RV250) || (rdev->family == CHIP_RV280))
		tmp |= S_00000D_FORCE_DISP1(1) | S_00000D_FORCE_DISP2(1);
	WREG32_PLL(R_00000D_SCLK_CNTL, tmp);
}