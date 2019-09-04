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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DYN_GFX_CLK_OFF_EN ; 
 int /*<<< orphan*/  GB_TILING_CONFIG ; 
 int /*<<< orphan*/  GFX_CLK_FORCE_ON ; 
 int /*<<< orphan*/  RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCLK_PWRMGT_CNTL ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rv770_gfx_clock_gating_enable(struct radeon_device *rdev,
					  bool enable)
{
	if (enable)
		WREG32_P(SCLK_PWRMGT_CNTL, DYN_GFX_CLK_OFF_EN, ~DYN_GFX_CLK_OFF_EN);
	else {
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~DYN_GFX_CLK_OFF_EN);
		WREG32_P(SCLK_PWRMGT_CNTL, GFX_CLK_FORCE_ON, ~GFX_CLK_FORCE_ON);
		WREG32_P(SCLK_PWRMGT_CNTL, 0, ~GFX_CLK_FORCE_ON);
		RREG32(GB_TILING_CONFIG);
	}
}