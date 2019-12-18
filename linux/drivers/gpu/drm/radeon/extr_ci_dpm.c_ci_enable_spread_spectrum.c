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
struct ci_power_info {scalar_t__ caps_sclk_ss_support; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_SPLL_SPREAD_SPECTRUM ; 
 int /*<<< orphan*/  DYN_SPREAD_SPECTRUM_EN ; 
 int /*<<< orphan*/  GENERAL_PWRMGT ; 
 int /*<<< orphan*/  RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSEN ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 

__attribute__((used)) static void ci_enable_spread_spectrum(struct radeon_device *rdev, bool enable)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	u32 tmp;

	if (enable) {
		if (pi->caps_sclk_ss_support) {
			tmp = RREG32_SMC(GENERAL_PWRMGT);
			tmp |= DYN_SPREAD_SPECTRUM_EN;
			WREG32_SMC(GENERAL_PWRMGT, tmp);
		}
	} else {
		tmp = RREG32_SMC(CG_SPLL_SPREAD_SPECTRUM);
		tmp &= ~SSEN;
		WREG32_SMC(CG_SPLL_SPREAD_SPECTRUM, tmp);

		tmp = RREG32_SMC(GENERAL_PWRMGT);
		tmp &= ~DYN_SPREAD_SPECTRUM_EN;
		WREG32_SMC(GENERAL_PWRMGT, tmp);
	}
}