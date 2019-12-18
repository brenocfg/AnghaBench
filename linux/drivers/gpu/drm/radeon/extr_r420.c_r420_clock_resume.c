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
 scalar_t__ CHIP_R420 ; 
 int RREG32_PLL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_00000D_SCLK_CNTL ; 
 int S_00000D_FORCE_CP (int) ; 
 int S_00000D_FORCE_PX (int) ; 
 int S_00000D_FORCE_TX (int) ; 
 int S_00000D_FORCE_VIP (int) ; 
 int /*<<< orphan*/  WREG32_PLL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_atom_set_clock_gating (struct radeon_device*,int) ; 
 int radeon_dynclks ; 

__attribute__((used)) static void r420_clock_resume(struct radeon_device *rdev)
{
	u32 sclk_cntl;

	if (radeon_dynclks != -1 && radeon_dynclks)
		radeon_atom_set_clock_gating(rdev, 1);
	sclk_cntl = RREG32_PLL(R_00000D_SCLK_CNTL);
	sclk_cntl |= S_00000D_FORCE_CP(1) | S_00000D_FORCE_VIP(1);
	if (rdev->family == CHIP_R420)
		sclk_cntl |= S_00000D_FORCE_PX(1) | S_00000D_FORCE_TX(1);
	WREG32_PLL(R_00000D_SCLK_CNTL, sclk_cntl);
}