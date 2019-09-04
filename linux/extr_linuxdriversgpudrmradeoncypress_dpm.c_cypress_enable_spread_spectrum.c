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
struct rv7xx_power_info {scalar_t__ mclk_ss; scalar_t__ sclk_ss; } ;
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_SPLL_SPREAD_SPECTRUM ; 
 int /*<<< orphan*/  DYN_SPREAD_SPECTRUM_EN ; 
 int /*<<< orphan*/  GENERAL_PWRMGT ; 
 int /*<<< orphan*/  MPLL_CNTL_MODE ; 
 int /*<<< orphan*/  SSEN ; 
 int /*<<< orphan*/  SS_DSMODE_EN ; 
 int /*<<< orphan*/  SS_SSEN ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 

void cypress_enable_spread_spectrum(struct radeon_device *rdev,
				    bool enable)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);

	if (enable) {
		if (pi->sclk_ss)
			WREG32_P(GENERAL_PWRMGT, DYN_SPREAD_SPECTRUM_EN, ~DYN_SPREAD_SPECTRUM_EN);

		if (pi->mclk_ss)
			WREG32_P(MPLL_CNTL_MODE, SS_SSEN, ~SS_SSEN);
	} else {
		WREG32_P(CG_SPLL_SPREAD_SPECTRUM, 0, ~SSEN);
		WREG32_P(GENERAL_PWRMGT, 0, ~DYN_SPREAD_SPECTRUM_EN);
		WREG32_P(MPLL_CNTL_MODE, 0, ~SS_SSEN);
		WREG32_P(MPLL_CNTL_MODE, 0, ~SS_DSMODE_EN);
	}
}