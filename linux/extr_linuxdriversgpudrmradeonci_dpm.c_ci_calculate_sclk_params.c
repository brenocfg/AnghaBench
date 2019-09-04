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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct TYPE_7__ {int reference_freq; } ;
struct TYPE_8__ {TYPE_2__ spll; } ;
struct radeon_device {TYPE_3__ clock; } ;
struct radeon_atom_ss {int rate; int percentage; } ;
struct TYPE_6__ {int cg_spll_func_cntl_3; int cg_spll_func_cntl_4; int cg_spll_spread_spectrum; int cg_spll_spread_spectrum_2; } ;
struct ci_power_info {scalar_t__ caps_sclk_ss_support; TYPE_1__ clock_registers; } ;
struct atom_clock_dividers {int ref_div; int fb_div; int post_div; scalar_t__ post_divider; } ;
struct TYPE_9__ {int SclkFrequency; int CgSpllFuncCntl3; int CgSpllFuncCntl4; int SpllSpreadSpectrum; int SpllSpreadSpectrum2; scalar_t__ SclkDid; } ;
typedef  TYPE_4__ SMU7_Discrete_GraphicsLevel ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_INTERNAL_ENGINE_SS ; 
 int CLK_S (int) ; 
 int CLK_S_MASK ; 
 int CLK_V (int) ; 
 int CLK_V_MASK ; 
 int /*<<< orphan*/  COMPUTE_GPUCLK_INPUT_FLAG_SCLK ; 
 int SPLL_DITHEN ; 
 int SPLL_FB_DIV (int) ; 
 int SPLL_FB_DIV_MASK ; 
 int SSEN ; 
 struct ci_power_info* ci_get_pi (struct radeon_device*) ; 
 int radeon_atom_get_clock_dividers (struct radeon_device*,int /*<<< orphan*/ ,int,int,struct atom_clock_dividers*) ; 
 scalar_t__ radeon_atombios_get_asic_ss_info (struct radeon_device*,struct radeon_atom_ss*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ci_calculate_sclk_params(struct radeon_device *rdev,
				    u32 engine_clock,
				    SMU7_Discrete_GraphicsLevel *sclk)
{
	struct ci_power_info *pi = ci_get_pi(rdev);
	struct atom_clock_dividers dividers;
	u32 spll_func_cntl_3 = pi->clock_registers.cg_spll_func_cntl_3;
	u32 spll_func_cntl_4 = pi->clock_registers.cg_spll_func_cntl_4;
	u32 cg_spll_spread_spectrum = pi->clock_registers.cg_spll_spread_spectrum;
	u32 cg_spll_spread_spectrum_2 = pi->clock_registers.cg_spll_spread_spectrum_2;
	u32 reference_clock = rdev->clock.spll.reference_freq;
	u32 reference_divider;
	u32 fbdiv;
	int ret;

	ret = radeon_atom_get_clock_dividers(rdev,
					     COMPUTE_GPUCLK_INPUT_FLAG_SCLK,
					     engine_clock, false, &dividers);
	if (ret)
		return ret;

	reference_divider = 1 + dividers.ref_div;
	fbdiv = dividers.fb_div & 0x3FFFFFF;

	spll_func_cntl_3 &= ~SPLL_FB_DIV_MASK;
	spll_func_cntl_3 |= SPLL_FB_DIV(fbdiv);
	spll_func_cntl_3 |= SPLL_DITHEN;

	if (pi->caps_sclk_ss_support) {
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

	sclk->SclkFrequency = engine_clock;
	sclk->CgSpllFuncCntl3 = spll_func_cntl_3;
	sclk->CgSpllFuncCntl4 = spll_func_cntl_4;
	sclk->SpllSpreadSpectrum = cg_spll_spread_spectrum;
	sclk->SpllSpreadSpectrum2  = cg_spll_spread_spectrum_2;
	sclk->SclkDid = (u8)dividers.post_divider;

	return 0;
}