#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_8__ {int mpll_ad_func_cntl; int mpll_ad_func_cntl_2; int mpll_dq_func_cntl; int mpll_dq_func_cntl_2; int mclk_pwrmgt_cntl; int dll_cntl; } ;
struct TYPE_9__ {TYPE_1__ rv770; } ;
struct rv7xx_power_info {scalar_t__ mem_gddr5; TYPE_2__ clk_regs; } ;
struct TYPE_10__ {int reference_freq; } ;
struct TYPE_11__ {TYPE_3__ mpll; } ;
struct radeon_device {TYPE_4__ clock; } ;
struct atom_clock_dividers {int ref_div; scalar_t__ vco_mode; int /*<<< orphan*/  post_div; } ;
struct TYPE_12__ {void* vDLL_CNTL; void* vMCLK_PWRMGT_CNTL; void* vMPLL_DQ_FUNC_CNTL_2; void* vMPLL_DQ_FUNC_CNTL; void* vMPLL_AD_FUNC_CNTL_2; void* vMPLL_AD_FUNC_CNTL; void* mclk_value; } ;
struct TYPE_13__ {TYPE_5__ mclk770; } ;
typedef  TYPE_6__ RV7XX_SMC_MCLK_VALUE ;

/* Variables and functions */
 int CLKF (int) ; 
 int CLKFRAC (int) ; 
 int CLKFRAC_MASK ; 
 int CLKF_MASK ; 
 int CLKR (int) ; 
 int CLKR_MASK ; 
 int /*<<< orphan*/  COMPUTE_MEMORY_PLL_PARAM ; 
 int EINVAL ; 
 int IBIAS (int) ; 
 int IBIAS_MASK ; 
 int VCO_MODE ; 
 int YCLK_POST_DIV (int) ; 
 int YCLK_POST_DIV_MASK ; 
 void* cpu_to_be32 (int) ; 
 int radeon_atom_get_clock_dividers (struct radeon_device*,int /*<<< orphan*/ ,int,int,struct atom_clock_dividers*) ; 
 int /*<<< orphan*/  rv770_calculate_fractional_mpll_feedback_divider (int,int,scalar_t__,struct atom_clock_dividers*,int*,int*) ; 
 int rv770_encode_yclk_post_div (int /*<<< orphan*/ ,int*) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 
 int rv770_map_clkf_to_ibias (struct radeon_device*,int) ; 

__attribute__((used)) static int rv770_populate_mclk_value(struct radeon_device *rdev,
				     u32 engine_clock, u32 memory_clock,
				     RV7XX_SMC_MCLK_VALUE *mclk)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	u8 encoded_reference_dividers[] = { 0, 16, 17, 20, 21 };
	u32 mpll_ad_func_cntl =
		pi->clk_regs.rv770.mpll_ad_func_cntl;
	u32 mpll_ad_func_cntl_2 =
		pi->clk_regs.rv770.mpll_ad_func_cntl_2;
	u32 mpll_dq_func_cntl =
		pi->clk_regs.rv770.mpll_dq_func_cntl;
	u32 mpll_dq_func_cntl_2 =
		pi->clk_regs.rv770.mpll_dq_func_cntl_2;
	u32 mclk_pwrmgt_cntl =
		pi->clk_regs.rv770.mclk_pwrmgt_cntl;
	u32 dll_cntl = pi->clk_regs.rv770.dll_cntl;
	struct atom_clock_dividers dividers;
	u32 reference_clock = rdev->clock.mpll.reference_freq;
	u32 clkf, clkfrac;
	u32 postdiv_yclk;
	u32 ibias;
	int ret;

	ret = radeon_atom_get_clock_dividers(rdev, COMPUTE_MEMORY_PLL_PARAM,
					     memory_clock, false, &dividers);
	if (ret)
		return ret;

	if ((dividers.ref_div < 1) || (dividers.ref_div > 5))
		return -EINVAL;

	rv770_calculate_fractional_mpll_feedback_divider(memory_clock, reference_clock,
							 pi->mem_gddr5,
							 &dividers, &clkf, &clkfrac);

	ret = rv770_encode_yclk_post_div(dividers.post_div, &postdiv_yclk);
	if (ret)
		return ret;

	ibias = rv770_map_clkf_to_ibias(rdev, clkf);

	mpll_ad_func_cntl &= ~(CLKR_MASK |
			       YCLK_POST_DIV_MASK |
			       CLKF_MASK |
			       CLKFRAC_MASK |
			       IBIAS_MASK);
	mpll_ad_func_cntl |= CLKR(encoded_reference_dividers[dividers.ref_div - 1]);
	mpll_ad_func_cntl |= YCLK_POST_DIV(postdiv_yclk);
	mpll_ad_func_cntl |= CLKF(clkf);
	mpll_ad_func_cntl |= CLKFRAC(clkfrac);
	mpll_ad_func_cntl |= IBIAS(ibias);

	if (dividers.vco_mode)
		mpll_ad_func_cntl_2 |= VCO_MODE;
	else
		mpll_ad_func_cntl_2 &= ~VCO_MODE;

	if (pi->mem_gddr5) {
		rv770_calculate_fractional_mpll_feedback_divider(memory_clock,
								 reference_clock,
								 pi->mem_gddr5,
								 &dividers, &clkf, &clkfrac);

		ibias = rv770_map_clkf_to_ibias(rdev, clkf);

		ret = rv770_encode_yclk_post_div(dividers.post_div, &postdiv_yclk);
		if (ret)
			return ret;

		mpll_dq_func_cntl &= ~(CLKR_MASK |
				       YCLK_POST_DIV_MASK |
				       CLKF_MASK |
				       CLKFRAC_MASK |
				       IBIAS_MASK);
		mpll_dq_func_cntl |= CLKR(encoded_reference_dividers[dividers.ref_div - 1]);
		mpll_dq_func_cntl |= YCLK_POST_DIV(postdiv_yclk);
		mpll_dq_func_cntl |= CLKF(clkf);
		mpll_dq_func_cntl |= CLKFRAC(clkfrac);
		mpll_dq_func_cntl |= IBIAS(ibias);

		if (dividers.vco_mode)
			mpll_dq_func_cntl_2 |= VCO_MODE;
		else
			mpll_dq_func_cntl_2 &= ~VCO_MODE;
	}

	mclk->mclk770.mclk_value = cpu_to_be32(memory_clock);
	mclk->mclk770.vMPLL_AD_FUNC_CNTL = cpu_to_be32(mpll_ad_func_cntl);
	mclk->mclk770.vMPLL_AD_FUNC_CNTL_2 = cpu_to_be32(mpll_ad_func_cntl_2);
	mclk->mclk770.vMPLL_DQ_FUNC_CNTL = cpu_to_be32(mpll_dq_func_cntl);
	mclk->mclk770.vMPLL_DQ_FUNC_CNTL_2 = cpu_to_be32(mpll_dq_func_cntl_2);
	mclk->mclk770.vMCLK_PWRMGT_CNTL = cpu_to_be32(mclk_pwrmgt_cntl);
	mclk->mclk770.vDLL_CNTL = cpu_to_be32(dll_cntl);

	return 0;
}