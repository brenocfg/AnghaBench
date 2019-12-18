#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct rv7xx_power_info {scalar_t__ mem_gddr5; scalar_t__ mclk_ss; } ;
struct TYPE_7__ {int reference_freq; } ;
struct TYPE_8__ {TYPE_2__ mpll; } ;
struct radeon_device {TYPE_3__ clock; } ;
struct radeon_atom_ss {int rate; int percentage; } ;
struct TYPE_6__ {int mpll_ad_func_cntl; int mpll_ad_func_cntl_2; int mpll_dq_func_cntl; int mpll_dq_func_cntl_2; int mclk_pwrmgt_cntl; int dll_cntl; int mpll_ss1; int mpll_ss2; } ;
struct ni_power_info {TYPE_1__ clock_registers; } ;
struct atom_clock_dividers {int post_div; int whole_fb_div; int frac_fb_div; int /*<<< orphan*/  ref_div; scalar_t__ vco_mode; } ;
struct TYPE_9__ {void* vMPLL_SS2; void* vMPLL_SS; void* vDLL_CNTL; void* vMCLK_PWRMGT_CNTL; void* vMPLL_DQ_FUNC_CNTL_2; void* vMPLL_DQ_FUNC_CNTL; void* vMPLL_AD_FUNC_CNTL_2; void* vMPLL_AD_FUNC_CNTL; void* mclk_value; } ;
typedef  TYPE_4__ NISLANDS_SMC_MCLK_VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_INTERNAL_MEMORY_SS ; 
 int CLKF (int) ; 
 int CLKFRAC (int) ; 
 int CLKFRAC_MASK ; 
 int CLKF_MASK ; 
 int CLKR (int /*<<< orphan*/ ) ; 
 int CLKR_MASK ; 
 int CLKS (int) ; 
 int CLKS_MASK ; 
 int CLKV (int) ; 
 int CLKV_MASK ; 
 int /*<<< orphan*/  COMPUTE_MEMORY_PLL_PARAM ; 
 int DLL_SPEED (int) ; 
 int DLL_SPEED_MASK ; 
 int IBIAS (int) ; 
 int IBIAS_MASK ; 
 int /*<<< orphan*/  MC_SEQ_MISC7 ; 
 int MRDCKA0_PDNB ; 
 int MRDCKA1_PDNB ; 
 int MRDCKB0_PDNB ; 
 int MRDCKB1_PDNB ; 
 int MRDCKC0_PDNB ; 
 int MRDCKC1_PDNB ; 
 int MRDCKD0_PDNB ; 
 int MRDCKD1_PDNB ; 
 int PDNB ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int VCO_MODE ; 
 int YCLK_POST_DIV (int) ; 
 int YCLK_POST_DIV_MASK ; 
 void* cpu_to_be32 (int) ; 
 int cypress_map_clkf_to_ibias (struct radeon_device*,int) ; 
 struct ni_power_info* ni_get_pi (struct radeon_device*) ; 
 int radeon_atom_get_clock_dividers (struct radeon_device*,int /*<<< orphan*/ ,int,int,struct atom_clock_dividers*) ; 
 scalar_t__ radeon_atombios_get_asic_ss_info (struct radeon_device*,struct radeon_atom_ss*,int /*<<< orphan*/ ,int) ; 
 int rv740_get_decoded_reference_divider (int /*<<< orphan*/ ) ; 
 int rv740_get_dll_speed (scalar_t__,int) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 

__attribute__((used)) static int ni_populate_mclk_value(struct radeon_device *rdev,
				  u32 engine_clock,
				  u32 memory_clock,
				  NISLANDS_SMC_MCLK_VALUE *mclk,
				  bool strobe_mode,
				  bool dll_state_on)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	struct ni_power_info *ni_pi = ni_get_pi(rdev);
	u32 mpll_ad_func_cntl = ni_pi->clock_registers.mpll_ad_func_cntl;
	u32 mpll_ad_func_cntl_2 = ni_pi->clock_registers.mpll_ad_func_cntl_2;
	u32 mpll_dq_func_cntl = ni_pi->clock_registers.mpll_dq_func_cntl;
	u32 mpll_dq_func_cntl_2 = ni_pi->clock_registers.mpll_dq_func_cntl_2;
	u32 mclk_pwrmgt_cntl = ni_pi->clock_registers.mclk_pwrmgt_cntl;
	u32 dll_cntl = ni_pi->clock_registers.dll_cntl;
	u32 mpll_ss1 = ni_pi->clock_registers.mpll_ss1;
	u32 mpll_ss2 = ni_pi->clock_registers.mpll_ss2;
	struct atom_clock_dividers dividers;
	u32 ibias;
	u32 dll_speed;
	int ret;
	u32 mc_seq_misc7;

	ret = radeon_atom_get_clock_dividers(rdev, COMPUTE_MEMORY_PLL_PARAM,
					     memory_clock, strobe_mode, &dividers);
	if (ret)
		return ret;

	if (!strobe_mode) {
		mc_seq_misc7 = RREG32(MC_SEQ_MISC7);

		if (mc_seq_misc7 & 0x8000000)
			dividers.post_div = 1;
	}

	ibias = cypress_map_clkf_to_ibias(rdev, dividers.whole_fb_div);

	mpll_ad_func_cntl &= ~(CLKR_MASK |
			       YCLK_POST_DIV_MASK |
			       CLKF_MASK |
			       CLKFRAC_MASK |
			       IBIAS_MASK);
	mpll_ad_func_cntl |= CLKR(dividers.ref_div);
	mpll_ad_func_cntl |= YCLK_POST_DIV(dividers.post_div);
	mpll_ad_func_cntl |= CLKF(dividers.whole_fb_div);
	mpll_ad_func_cntl |= CLKFRAC(dividers.frac_fb_div);
	mpll_ad_func_cntl |= IBIAS(ibias);

	if (dividers.vco_mode)
		mpll_ad_func_cntl_2 |= VCO_MODE;
	else
		mpll_ad_func_cntl_2 &= ~VCO_MODE;

	if (pi->mem_gddr5) {
		mpll_dq_func_cntl &= ~(CLKR_MASK |
				       YCLK_POST_DIV_MASK |
				       CLKF_MASK |
				       CLKFRAC_MASK |
				       IBIAS_MASK);
		mpll_dq_func_cntl |= CLKR(dividers.ref_div);
		mpll_dq_func_cntl |= YCLK_POST_DIV(dividers.post_div);
		mpll_dq_func_cntl |= CLKF(dividers.whole_fb_div);
		mpll_dq_func_cntl |= CLKFRAC(dividers.frac_fb_div);
		mpll_dq_func_cntl |= IBIAS(ibias);

		if (strobe_mode)
			mpll_dq_func_cntl &= ~PDNB;
		else
			mpll_dq_func_cntl |= PDNB;

		if (dividers.vco_mode)
			mpll_dq_func_cntl_2 |= VCO_MODE;
		else
			mpll_dq_func_cntl_2 &= ~VCO_MODE;
	}

	if (pi->mclk_ss) {
		struct radeon_atom_ss ss;
		u32 vco_freq = memory_clock * dividers.post_div;

		if (radeon_atombios_get_asic_ss_info(rdev, &ss,
						     ASIC_INTERNAL_MEMORY_SS, vco_freq)) {
			u32 reference_clock = rdev->clock.mpll.reference_freq;
			u32 decoded_ref = rv740_get_decoded_reference_divider(dividers.ref_div);
			u32 clk_s = reference_clock * 5 / (decoded_ref * ss.rate);
			u32 clk_v = ss.percentage *
				(0x4000 * dividers.whole_fb_div + 0x800 * dividers.frac_fb_div) / (clk_s * 625);

			mpll_ss1 &= ~CLKV_MASK;
			mpll_ss1 |= CLKV(clk_v);

			mpll_ss2 &= ~CLKS_MASK;
			mpll_ss2 |= CLKS(clk_s);
		}
	}

	dll_speed = rv740_get_dll_speed(pi->mem_gddr5,
					memory_clock);

	mclk_pwrmgt_cntl &= ~DLL_SPEED_MASK;
	mclk_pwrmgt_cntl |= DLL_SPEED(dll_speed);
	if (dll_state_on)
		mclk_pwrmgt_cntl |= (MRDCKA0_PDNB |
				     MRDCKA1_PDNB |
				     MRDCKB0_PDNB |
				     MRDCKB1_PDNB |
				     MRDCKC0_PDNB |
				     MRDCKC1_PDNB |
				     MRDCKD0_PDNB |
				     MRDCKD1_PDNB);
	else
		mclk_pwrmgt_cntl &= ~(MRDCKA0_PDNB |
				      MRDCKA1_PDNB |
				      MRDCKB0_PDNB |
				      MRDCKB1_PDNB |
				      MRDCKC0_PDNB |
				      MRDCKC1_PDNB |
				      MRDCKD0_PDNB |
				      MRDCKD1_PDNB);


	mclk->mclk_value = cpu_to_be32(memory_clock);
	mclk->vMPLL_AD_FUNC_CNTL = cpu_to_be32(mpll_ad_func_cntl);
	mclk->vMPLL_AD_FUNC_CNTL_2 = cpu_to_be32(mpll_ad_func_cntl_2);
	mclk->vMPLL_DQ_FUNC_CNTL = cpu_to_be32(mpll_dq_func_cntl);
	mclk->vMPLL_DQ_FUNC_CNTL_2 = cpu_to_be32(mpll_dq_func_cntl_2);
	mclk->vMCLK_PWRMGT_CNTL = cpu_to_be32(mclk_pwrmgt_cntl);
	mclk->vDLL_CNTL = cpu_to_be32(dll_cntl);
	mclk->vMPLL_SS = cpu_to_be32(mpll_ss1);
	mclk->vMPLL_SS2 = cpu_to_be32(mpll_ss2);

	return 0;
}