#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* mpll_ss2; void* mpll_ss1; void* mpll_func_cntl_2; void* mpll_func_cntl_1; void* mpll_func_cntl; void* mpll_dq_func_cntl; void* mpll_ad_func_cntl; void* mclk_pwrmgt_cntl; void* dll_cntl; void* cg_spll_spread_spectrum_2; void* cg_spll_spread_spectrum; void* cg_spll_func_cntl_4; void* cg_spll_func_cntl_3; void* cg_spll_func_cntl_2; void* cg_spll_func_cntl; } ;
struct ci_power_info {TYPE_1__ clock_registers; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 void* RREG32 (int /*<<< orphan*/ ) ; 
 void* RREG32_SMC (int /*<<< orphan*/ ) ; 
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 
 int /*<<< orphan*/  ixCG_SPLL_FUNC_CNTL ; 
 int /*<<< orphan*/  ixCG_SPLL_FUNC_CNTL_2 ; 
 int /*<<< orphan*/  ixCG_SPLL_FUNC_CNTL_3 ; 
 int /*<<< orphan*/  ixCG_SPLL_FUNC_CNTL_4 ; 
 int /*<<< orphan*/  ixCG_SPLL_SPREAD_SPECTRUM ; 
 int /*<<< orphan*/  ixCG_SPLL_SPREAD_SPECTRUM_2 ; 
 int /*<<< orphan*/  mmDLL_CNTL ; 
 int /*<<< orphan*/  mmMCLK_PWRMGT_CNTL ; 
 int /*<<< orphan*/  mmMPLL_AD_FUNC_CNTL ; 
 int /*<<< orphan*/  mmMPLL_DQ_FUNC_CNTL ; 
 int /*<<< orphan*/  mmMPLL_FUNC_CNTL ; 
 int /*<<< orphan*/  mmMPLL_FUNC_CNTL_1 ; 
 int /*<<< orphan*/  mmMPLL_FUNC_CNTL_2 ; 
 int /*<<< orphan*/  mmMPLL_SS1 ; 
 int /*<<< orphan*/  mmMPLL_SS2 ; 

__attribute__((used)) static void ci_read_clock_registers(struct amdgpu_device *adev)
{
	struct ci_power_info *pi = ci_get_pi(adev);

	pi->clock_registers.cg_spll_func_cntl =
		RREG32_SMC(ixCG_SPLL_FUNC_CNTL);
	pi->clock_registers.cg_spll_func_cntl_2 =
		RREG32_SMC(ixCG_SPLL_FUNC_CNTL_2);
	pi->clock_registers.cg_spll_func_cntl_3 =
		RREG32_SMC(ixCG_SPLL_FUNC_CNTL_3);
	pi->clock_registers.cg_spll_func_cntl_4 =
		RREG32_SMC(ixCG_SPLL_FUNC_CNTL_4);
	pi->clock_registers.cg_spll_spread_spectrum =
		RREG32_SMC(ixCG_SPLL_SPREAD_SPECTRUM);
	pi->clock_registers.cg_spll_spread_spectrum_2 =
		RREG32_SMC(ixCG_SPLL_SPREAD_SPECTRUM_2);
	pi->clock_registers.dll_cntl = RREG32(mmDLL_CNTL);
	pi->clock_registers.mclk_pwrmgt_cntl = RREG32(mmMCLK_PWRMGT_CNTL);
	pi->clock_registers.mpll_ad_func_cntl = RREG32(mmMPLL_AD_FUNC_CNTL);
	pi->clock_registers.mpll_dq_func_cntl = RREG32(mmMPLL_DQ_FUNC_CNTL);
	pi->clock_registers.mpll_func_cntl = RREG32(mmMPLL_FUNC_CNTL);
	pi->clock_registers.mpll_func_cntl_1 = RREG32(mmMPLL_FUNC_CNTL_1);
	pi->clock_registers.mpll_func_cntl_2 = RREG32(mmMPLL_FUNC_CNTL_2);
	pi->clock_registers.mpll_ss1 = RREG32(mmMPLL_SS1);
	pi->clock_registers.mpll_ss2 = RREG32(mmMPLL_SS2);
}