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
struct si_power_info {TYPE_1__ clock_registers; } ;
struct rv7xx_power_info {scalar_t__ mclk_ss; } ;
struct atom_mpll_param {int /*<<< orphan*/  dll_speed; int /*<<< orphan*/  post_div; int /*<<< orphan*/  yclk_sel; int /*<<< orphan*/  vco_mode; int /*<<< orphan*/  clkfrac; int /*<<< orphan*/  clkf; int /*<<< orphan*/  bwcntl; } ;
struct TYPE_10__ {scalar_t__ vram_type; } ;
struct TYPE_8__ {int reference_freq; } ;
struct TYPE_9__ {TYPE_2__ mpll; } ;
struct amdgpu_device {TYPE_4__ gmc; TYPE_3__ clock; } ;
struct amdgpu_atom_ss {int rate; int percentage; } ;
struct TYPE_11__ {void* vMPLL_SS2; void* vMPLL_SS; void* vDLL_CNTL; void* vMCLK_PWRMGT_CNTL; void* vMPLL_DQ_FUNC_CNTL; void* vMPLL_AD_FUNC_CNTL; void* vMPLL_FUNC_CNTL_2; void* vMPLL_FUNC_CNTL_1; void* vMPLL_FUNC_CNTL; void* mclk_value; } ;
typedef  TYPE_5__ SISLANDS_SMC_MCLK_VALUE ;

/* Variables and functions */
 scalar_t__ AMDGPU_VRAM_TYPE_GDDR5 ; 
 int /*<<< orphan*/  ASIC_INTERNAL_MEMORY_SS ; 
 int BWCTRL (int /*<<< orphan*/ ) ; 
 int BWCTRL_MASK ; 
 int CLKF (int /*<<< orphan*/ ) ; 
 int CLKFRAC (int /*<<< orphan*/ ) ; 
 int CLKFRAC_MASK ; 
 int CLKF_MASK ; 
 int CLKS (int) ; 
 int CLKS_MASK ; 
 int CLKV (int) ; 
 int CLKV_MASK ; 
 int DLL_SPEED (int /*<<< orphan*/ ) ; 
 int DLL_SPEED_MASK ; 
 int MRDCK0_PDNB ; 
 int MRDCK1_PDNB ; 
 int VCO_MODE (int /*<<< orphan*/ ) ; 
 int VCO_MODE_MASK ; 
 int YCLK_POST_DIV (int /*<<< orphan*/ ) ; 
 int YCLK_POST_DIV_MASK ; 
 int YCLK_SEL (int /*<<< orphan*/ ) ; 
 int YCLK_SEL_MASK ; 
 scalar_t__ amdgpu_atombios_get_asic_ss_info (struct amdgpu_device*,struct amdgpu_atom_ss*,int /*<<< orphan*/ ,int) ; 
 int amdgpu_atombios_get_memory_pll_dividers (struct amdgpu_device*,int,int,struct atom_mpll_param*) ; 
 void* cpu_to_be32 (int) ; 
 struct rv7xx_power_info* rv770_get_pi (struct amdgpu_device*) ; 
 struct si_power_info* si_get_pi (struct amdgpu_device*) ; 

__attribute__((used)) static int si_populate_mclk_value(struct amdgpu_device *adev,
				  u32 engine_clock,
				  u32 memory_clock,
				  SISLANDS_SMC_MCLK_VALUE *mclk,
				  bool strobe_mode,
				  bool dll_state_on)
{
	struct rv7xx_power_info *pi = rv770_get_pi(adev);
	struct si_power_info *si_pi = si_get_pi(adev);
	u32  dll_cntl = si_pi->clock_registers.dll_cntl;
	u32  mclk_pwrmgt_cntl = si_pi->clock_registers.mclk_pwrmgt_cntl;
	u32  mpll_ad_func_cntl = si_pi->clock_registers.mpll_ad_func_cntl;
	u32  mpll_dq_func_cntl = si_pi->clock_registers.mpll_dq_func_cntl;
	u32  mpll_func_cntl = si_pi->clock_registers.mpll_func_cntl;
	u32  mpll_func_cntl_1 = si_pi->clock_registers.mpll_func_cntl_1;
	u32  mpll_func_cntl_2 = si_pi->clock_registers.mpll_func_cntl_2;
	u32  mpll_ss1 = si_pi->clock_registers.mpll_ss1;
	u32  mpll_ss2 = si_pi->clock_registers.mpll_ss2;
	struct atom_mpll_param mpll_param;
	int ret;

	ret = amdgpu_atombios_get_memory_pll_dividers(adev, memory_clock, strobe_mode, &mpll_param);
	if (ret)
		return ret;

	mpll_func_cntl &= ~BWCTRL_MASK;
	mpll_func_cntl |= BWCTRL(mpll_param.bwcntl);

	mpll_func_cntl_1 &= ~(CLKF_MASK | CLKFRAC_MASK | VCO_MODE_MASK);
	mpll_func_cntl_1 |= CLKF(mpll_param.clkf) |
		CLKFRAC(mpll_param.clkfrac) | VCO_MODE(mpll_param.vco_mode);

	mpll_ad_func_cntl &= ~YCLK_POST_DIV_MASK;
	mpll_ad_func_cntl |= YCLK_POST_DIV(mpll_param.post_div);

	if (adev->gmc.vram_type == AMDGPU_VRAM_TYPE_GDDR5) {
		mpll_dq_func_cntl &= ~(YCLK_SEL_MASK | YCLK_POST_DIV_MASK);
		mpll_dq_func_cntl |= YCLK_SEL(mpll_param.yclk_sel) |
			YCLK_POST_DIV(mpll_param.post_div);
	}

	if (pi->mclk_ss) {
		struct amdgpu_atom_ss ss;
		u32 freq_nom;
		u32 tmp;
		u32 reference_clock = adev->clock.mpll.reference_freq;

		if (adev->gmc.vram_type == AMDGPU_VRAM_TYPE_GDDR5)
			freq_nom = memory_clock * 4;
		else
			freq_nom = memory_clock * 2;

		tmp = freq_nom / reference_clock;
		tmp = tmp * tmp;
		if (amdgpu_atombios_get_asic_ss_info(adev, &ss,
		                                     ASIC_INTERNAL_MEMORY_SS, freq_nom)) {
			u32 clks = reference_clock * 5 / ss.rate;
			u32 clkv = (u32)((((131 * ss.percentage * ss.rate) / 100) * tmp) / freq_nom);

		        mpll_ss1 &= ~CLKV_MASK;
		        mpll_ss1 |= CLKV(clkv);

		        mpll_ss2 &= ~CLKS_MASK;
		        mpll_ss2 |= CLKS(clks);
		}
	}

	mclk_pwrmgt_cntl &= ~DLL_SPEED_MASK;
	mclk_pwrmgt_cntl |= DLL_SPEED(mpll_param.dll_speed);

	if (dll_state_on)
		mclk_pwrmgt_cntl |= MRDCK0_PDNB | MRDCK1_PDNB;
	else
		mclk_pwrmgt_cntl &= ~(MRDCK0_PDNB | MRDCK1_PDNB);

	mclk->mclk_value = cpu_to_be32(memory_clock);
	mclk->vMPLL_FUNC_CNTL = cpu_to_be32(mpll_func_cntl);
	mclk->vMPLL_FUNC_CNTL_1 = cpu_to_be32(mpll_func_cntl_1);
	mclk->vMPLL_FUNC_CNTL_2 = cpu_to_be32(mpll_func_cntl_2);
	mclk->vMPLL_AD_FUNC_CNTL = cpu_to_be32(mpll_ad_func_cntl);
	mclk->vMPLL_DQ_FUNC_CNTL = cpu_to_be32(mpll_dq_func_cntl);
	mclk->vMCLK_PWRMGT_CNTL = cpu_to_be32(mclk_pwrmgt_cntl);
	mclk->vDLL_CNTL = cpu_to_be32(dll_cntl);
	mclk->vMPLL_SS = cpu_to_be32(mpll_ss1);
	mclk->vMPLL_SS2 = cpu_to_be32(mpll_ss2);

	return 0;
}