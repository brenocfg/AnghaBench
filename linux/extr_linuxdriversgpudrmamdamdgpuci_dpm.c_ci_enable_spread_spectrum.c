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
struct ci_power_info {scalar_t__ caps_sclk_ss_support; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_SPLL_SPREAD_SPECTRUM__SSEN_MASK ; 
 int /*<<< orphan*/  GENERAL_PWRMGT__DYN_SPREAD_SPECTRUM_EN_MASK ; 
 int /*<<< orphan*/  RREG32_SMC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32_SMC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ixCG_SPLL_SPREAD_SPECTRUM ; 
 int /*<<< orphan*/  ixGENERAL_PWRMGT ; 

__attribute__((used)) static void ci_enable_spread_spectrum(struct amdgpu_device *adev, bool enable)
{
	struct ci_power_info *pi = ci_get_pi(adev);
	u32 tmp;

	if (enable) {
		if (pi->caps_sclk_ss_support) {
			tmp = RREG32_SMC(ixGENERAL_PWRMGT);
			tmp |= GENERAL_PWRMGT__DYN_SPREAD_SPECTRUM_EN_MASK;
			WREG32_SMC(ixGENERAL_PWRMGT, tmp);
		}
	} else {
		tmp = RREG32_SMC(ixCG_SPLL_SPREAD_SPECTRUM);
		tmp &= ~CG_SPLL_SPREAD_SPECTRUM__SSEN_MASK;
		WREG32_SMC(ixCG_SPLL_SPREAD_SPECTRUM, tmp);

		tmp = RREG32_SMC(ixGENERAL_PWRMGT);
		tmp &= ~GENERAL_PWRMGT__DYN_SPREAD_SPECTRUM_EN_MASK;
		WREG32_SMC(ixGENERAL_PWRMGT, tmp);
	}
}