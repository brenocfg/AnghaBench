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
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_7__ {int cg_spll_func_cntl; int cg_spll_func_cntl_2; int cg_spll_func_cntl_3; int cg_spll_spread_spectrum; int cg_spll_spread_spectrum_2; } ;
struct TYPE_8__ {TYPE_1__ rv770; } ;
struct rv7xx_power_info {scalar_t__ sclk_ss; TYPE_2__ clk_regs; } ;
struct TYPE_9__ {int reference_freq; } ;
struct TYPE_10__ {TYPE_3__ spll; } ;
struct radeon_device {TYPE_4__ clock; } ;
struct radeon_atom_ss {int rate; int percentage; } ;
struct atom_clock_dividers {int ref_div; int post_div; } ;
struct TYPE_11__ {void* vCG_SPLL_SPREAD_SPECTRUM_2; void* vCG_SPLL_SPREAD_SPECTRUM; void* vCG_SPLL_FUNC_CNTL_3; void* vCG_SPLL_FUNC_CNTL_2; void* vCG_SPLL_FUNC_CNTL; void* sclk_value; } ;
typedef  TYPE_5__ RV770_SMC_SCLK_VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_INTERNAL_ENGINE_SS ; 
 int CLK_S (int) ; 
 int CLK_S_MASK ; 
 int CLK_V (int) ; 
 int CLK_V_MASK ; 
 int /*<<< orphan*/  COMPUTE_ENGINE_PLL_PARAM ; 
 int SCLK_MUX_SEL (int) ; 
 int SCLK_MUX_SEL_MASK ; 
 int SPLL_DITHEN ; 
 int SPLL_FB_DIV (int) ; 
 int SPLL_FB_DIV_MASK ; 
 int SPLL_PDIV_A (int) ; 
 int SPLL_PDIV_A_MASK ; 
 int SPLL_REF_DIV (int) ; 
 int SPLL_REF_DIV_MASK ; 
 int SSEN ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int radeon_atom_get_clock_dividers (struct radeon_device*,int /*<<< orphan*/ ,int,int,struct atom_clock_dividers*) ; 
 scalar_t__ radeon_atombios_get_asic_ss_info (struct radeon_device*,struct radeon_atom_ss*,int /*<<< orphan*/ ,int) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 

int rv740_populate_sclk_value(struct radeon_device *rdev, u32 engine_clock,
			      RV770_SMC_SCLK_VALUE *sclk)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	struct atom_clock_dividers dividers;
	u32 spll_func_cntl = pi->clk_regs.rv770.cg_spll_func_cntl;
	u32 spll_func_cntl_2 = pi->clk_regs.rv770.cg_spll_func_cntl_2;
	u32 spll_func_cntl_3 = pi->clk_regs.rv770.cg_spll_func_cntl_3;
	u32 cg_spll_spread_spectrum = pi->clk_regs.rv770.cg_spll_spread_spectrum;
	u32 cg_spll_spread_spectrum_2 = pi->clk_regs.rv770.cg_spll_spread_spectrum_2;
	u64 tmp;
	u32 reference_clock = rdev->clock.spll.reference_freq;
	u32 reference_divider;
	u32 fbdiv;
	int ret;

	ret = radeon_atom_get_clock_dividers(rdev, COMPUTE_ENGINE_PLL_PARAM,
					     engine_clock, false, &dividers);
	if (ret)
		return ret;

	reference_divider = 1 + dividers.ref_div;

	tmp = (u64) engine_clock * reference_divider * dividers.post_div * 16384;
	do_div(tmp, reference_clock);
	fbdiv = (u32) tmp;

	spll_func_cntl &= ~(SPLL_PDIV_A_MASK | SPLL_REF_DIV_MASK);
	spll_func_cntl |= SPLL_REF_DIV(dividers.ref_div);
	spll_func_cntl |= SPLL_PDIV_A(dividers.post_div);

	spll_func_cntl_2 &= ~SCLK_MUX_SEL_MASK;
	spll_func_cntl_2 |= SCLK_MUX_SEL(2);

	spll_func_cntl_3 &= ~SPLL_FB_DIV_MASK;
	spll_func_cntl_3 |= SPLL_FB_DIV(fbdiv);
	spll_func_cntl_3 |= SPLL_DITHEN;

	if (pi->sclk_ss) {
		struct radeon_atom_ss ss;
		u32 vco_freq = engine_clock * dividers.post_div;

		if (radeon_atombios_get_asic_ss_info(rdev, &ss,
						     ASIC_INTERNAL_ENGINE_SS, vco_freq)) {
			u32 clk_s = reference_clock * 5 / (reference_divider * ss.rate);
			u32 clk_v = 4 * ss.percentage * fbdiv / (clk_s * 10000);

			cg_spll_spread_spectrum &= ~CLK_S_MASK;
			cg_spll_spread_spectrum |= CLK_S(clk_s);
			cg_spll_spread_spectrum |= SSEN;

			cg_spll_spread_spectrum_2 &= ~CLK_V_MASK;
			cg_spll_spread_spectrum_2 |= CLK_V(clk_v);
		}
	}

	sclk->sclk_value = cpu_to_be32(engine_clock);
	sclk->vCG_SPLL_FUNC_CNTL = cpu_to_be32(spll_func_cntl);
	sclk->vCG_SPLL_FUNC_CNTL_2 = cpu_to_be32(spll_func_cntl_2);
	sclk->vCG_SPLL_FUNC_CNTL_3 = cpu_to_be32(spll_func_cntl_3);
	sclk->vCG_SPLL_SPREAD_SPECTRUM = cpu_to_be32(cg_spll_spread_spectrum);
	sclk->vCG_SPLL_SPREAD_SPECTRUM_2 = cpu_to_be32(cg_spll_spread_spectrum_2);

	return 0;
}