#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {int dll_cntl; int mclk_pwrmgt_cntl; int mpll_ad_func_cntl; int mpll_dq_func_cntl; int mpll_func_cntl; int mpll_func_cntl_1; int mpll_func_cntl_2; int mpll_ss1; int mpll_ss2; } ;
struct ci_power_info {scalar_t__ caps_mclk_ss_support; TYPE_1__ clock_registers; } ;
struct atom_mpll_param {int bwcntl; int clkf; int clkfrac; int vco_mode; int post_div; int yclk_sel; int qdr; int dll_speed; } ;
struct TYPE_9__ {int reference_freq; } ;
struct TYPE_10__ {TYPE_3__ mpll; } ;
struct TYPE_8__ {scalar_t__ vram_type; } ;
struct amdgpu_device {TYPE_4__ clock; TYPE_2__ gmc; } ;
struct amdgpu_atom_ss {int rate; int percentage; } ;
struct TYPE_11__ {int MclkFrequency; int MpllFuncCntl; int MpllFuncCntl_1; int MpllFuncCntl_2; int MpllAdFuncCntl; int MpllDqFuncCntl; int MclkPwrmgtCntl; int DllCntl; int MpllSs1; int MpllSs2; } ;
typedef  TYPE_5__ SMU7_Discrete_MemoryLevel ;

/* Variables and functions */
 scalar_t__ AMDGPU_VRAM_TYPE_GDDR5 ; 
 int /*<<< orphan*/  ASIC_INTERNAL_MEMORY_SS ; 
 int MCLK_PWRMGT_CNTL__DLL_SPEED_MASK ; 
 int MCLK_PWRMGT_CNTL__DLL_SPEED__SHIFT ; 
 int MCLK_PWRMGT_CNTL__MRDCK0_PDNB_MASK ; 
 int MCLK_PWRMGT_CNTL__MRDCK1_PDNB_MASK ; 
 int MPLL_AD_FUNC_CNTL__YCLK_POST_DIV_MASK ; 
 int MPLL_AD_FUNC_CNTL__YCLK_POST_DIV__SHIFT ; 
 int MPLL_DQ_FUNC_CNTL__YCLK_SEL_MASK ; 
 int MPLL_DQ_FUNC_CNTL__YCLK_SEL__SHIFT ; 
 int MPLL_FUNC_CNTL_1__CLKFRAC_MASK ; 
 int MPLL_FUNC_CNTL_1__CLKFRAC__SHIFT ; 
 int MPLL_FUNC_CNTL_1__CLKF_MASK ; 
 int MPLL_FUNC_CNTL_1__CLKF__SHIFT ; 
 int MPLL_FUNC_CNTL_1__VCO_MODE_MASK ; 
 int MPLL_FUNC_CNTL_1__VCO_MODE__SHIFT ; 
 int MPLL_FUNC_CNTL__BWCTRL_MASK ; 
 int MPLL_FUNC_CNTL__BWCTRL__SHIFT ; 
 int MPLL_SS1__CLKV_MASK ; 
 int MPLL_SS1__CLKV__SHIFT ; 
 int MPLL_SS2__CLKS_MASK ; 
 int MPLL_SS2__CLKS__SHIFT ; 
 scalar_t__ amdgpu_atombios_get_asic_ss_info (struct amdgpu_device*,struct amdgpu_atom_ss*,int /*<<< orphan*/ ,int) ; 
 int amdgpu_atombios_get_memory_pll_dividers (struct amdgpu_device*,int,int,struct atom_mpll_param*) ; 
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 

__attribute__((used)) static int ci_calculate_mclk_params(struct amdgpu_device *adev,
				    u32 memory_clock,
				    SMU7_Discrete_MemoryLevel *mclk,
				    bool strobe_mode,
				    bool dll_state_on)
{
	struct ci_power_info *pi = ci_get_pi(adev);
	u32  dll_cntl = pi->clock_registers.dll_cntl;
	u32  mclk_pwrmgt_cntl = pi->clock_registers.mclk_pwrmgt_cntl;
	u32  mpll_ad_func_cntl = pi->clock_registers.mpll_ad_func_cntl;
	u32  mpll_dq_func_cntl = pi->clock_registers.mpll_dq_func_cntl;
	u32  mpll_func_cntl = pi->clock_registers.mpll_func_cntl;
	u32  mpll_func_cntl_1 = pi->clock_registers.mpll_func_cntl_1;
	u32  mpll_func_cntl_2 = pi->clock_registers.mpll_func_cntl_2;
	u32  mpll_ss1 = pi->clock_registers.mpll_ss1;
	u32  mpll_ss2 = pi->clock_registers.mpll_ss2;
	struct atom_mpll_param mpll_param;
	int ret;

	ret = amdgpu_atombios_get_memory_pll_dividers(adev, memory_clock, strobe_mode, &mpll_param);
	if (ret)
		return ret;

	mpll_func_cntl &= ~MPLL_FUNC_CNTL__BWCTRL_MASK;
	mpll_func_cntl |= (mpll_param.bwcntl << MPLL_FUNC_CNTL__BWCTRL__SHIFT);

	mpll_func_cntl_1 &= ~(MPLL_FUNC_CNTL_1__CLKF_MASK | MPLL_FUNC_CNTL_1__CLKFRAC_MASK |
			MPLL_FUNC_CNTL_1__VCO_MODE_MASK);
	mpll_func_cntl_1 |= (mpll_param.clkf) << MPLL_FUNC_CNTL_1__CLKF__SHIFT |
		(mpll_param.clkfrac << MPLL_FUNC_CNTL_1__CLKFRAC__SHIFT) |
		(mpll_param.vco_mode << MPLL_FUNC_CNTL_1__VCO_MODE__SHIFT);

	mpll_ad_func_cntl &= ~MPLL_AD_FUNC_CNTL__YCLK_POST_DIV_MASK;
	mpll_ad_func_cntl |= (mpll_param.post_div << MPLL_AD_FUNC_CNTL__YCLK_POST_DIV__SHIFT);

	if (adev->gmc.vram_type == AMDGPU_VRAM_TYPE_GDDR5) {
		mpll_dq_func_cntl &= ~(MPLL_DQ_FUNC_CNTL__YCLK_SEL_MASK |
				MPLL_AD_FUNC_CNTL__YCLK_POST_DIV_MASK);
		mpll_dq_func_cntl |= (mpll_param.yclk_sel << MPLL_DQ_FUNC_CNTL__YCLK_SEL__SHIFT) |
				(mpll_param.post_div << MPLL_AD_FUNC_CNTL__YCLK_POST_DIV__SHIFT);
	}

	if (pi->caps_mclk_ss_support) {
		struct amdgpu_atom_ss ss;
		u32 freq_nom;
		u32 tmp;
		u32 reference_clock = adev->clock.mpll.reference_freq;

		if (mpll_param.qdr == 1)
			freq_nom = memory_clock * 4 * (1 << mpll_param.post_div);
		else
			freq_nom = memory_clock * 2 * (1 << mpll_param.post_div);

		tmp = (freq_nom / reference_clock);
		tmp = tmp * tmp;
		if (amdgpu_atombios_get_asic_ss_info(adev, &ss,
						     ASIC_INTERNAL_MEMORY_SS, freq_nom)) {
			u32 clks = reference_clock * 5 / ss.rate;
			u32 clkv = (u32)((((131 * ss.percentage * ss.rate) / 100) * tmp) / freq_nom);

			mpll_ss1 &= ~MPLL_SS1__CLKV_MASK;
			mpll_ss1 |= (clkv << MPLL_SS1__CLKV__SHIFT);

			mpll_ss2 &= ~MPLL_SS2__CLKS_MASK;
			mpll_ss2 |= (clks << MPLL_SS2__CLKS__SHIFT);
		}
	}

	mclk_pwrmgt_cntl &= ~MCLK_PWRMGT_CNTL__DLL_SPEED_MASK;
	mclk_pwrmgt_cntl |= (mpll_param.dll_speed << MCLK_PWRMGT_CNTL__DLL_SPEED__SHIFT);

	if (dll_state_on)
		mclk_pwrmgt_cntl |= MCLK_PWRMGT_CNTL__MRDCK0_PDNB_MASK |
			MCLK_PWRMGT_CNTL__MRDCK1_PDNB_MASK;
	else
		mclk_pwrmgt_cntl &= ~(MCLK_PWRMGT_CNTL__MRDCK0_PDNB_MASK |
			MCLK_PWRMGT_CNTL__MRDCK1_PDNB_MASK);

	mclk->MclkFrequency = memory_clock;
	mclk->MpllFuncCntl = mpll_func_cntl;
	mclk->MpllFuncCntl_1 = mpll_func_cntl_1;
	mclk->MpllFuncCntl_2 = mpll_func_cntl_2;
	mclk->MpllAdFuncCntl = mpll_ad_func_cntl;
	mclk->MpllDqFuncCntl = mpll_dq_func_cntl;
	mclk->MclkPwrmgtCntl = mclk_pwrmgt_cntl;
	mclk->DllCntl = dll_cntl;
	mclk->MpllSs1 = mpll_ss1;
	mclk->MpllSs2 = mpll_ss2;

	return 0;
}