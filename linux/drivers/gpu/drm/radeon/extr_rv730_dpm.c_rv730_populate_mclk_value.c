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
typedef  int u32 ;
struct TYPE_8__ {int mclk_pwrmgt_cntl; int dll_cntl; int mpll_func_cntl; int mpll_func_cntl2; int mpll_func_cntl3; int mpll_ss; int mpll_ss2; } ;
struct TYPE_9__ {TYPE_1__ rv730; } ;
struct rv7xx_power_info {scalar_t__ mclk_ss; TYPE_2__ clk_regs; } ;
struct TYPE_10__ {int reference_freq; } ;
struct TYPE_11__ {TYPE_3__ mpll; } ;
struct radeon_device {TYPE_4__ clock; } ;
struct radeon_atom_ss {int rate; int percentage; } ;
struct atom_clock_dividers {int ref_div; int post_div; int fb_div; scalar_t__ enable_dithen; scalar_t__ enable_post_div; } ;
struct TYPE_12__ {void* vMPLL_SS2; void* vMPLL_SS; void* vMPLL_FUNC_CNTL3; void* vMPLL_FUNC_CNTL2; void* vMPLL_FUNC_CNTL; void* mclk_value; void* vDLL_CNTL; void* vMCLK_PWRMGT_CNTL; } ;
struct TYPE_13__ {TYPE_5__ mclk730; } ;
typedef  TYPE_6__* LPRV7XX_SMC_MCLK_VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_INTERNAL_MEMORY_SS ; 
 int CLK_S (int) ; 
 int CLK_S_MASK ; 
 int CLK_V (int) ; 
 int CLK_V_MASK ; 
 int /*<<< orphan*/  COMPUTE_MEMORY_PLL_PARAM ; 
 int MPLL_DITHEN ; 
 int MPLL_DIVEN ; 
 int MPLL_FB_DIV (int) ; 
 int MPLL_FB_DIV_MASK ; 
 int MPLL_HILEN (int) ; 
 int MPLL_HILEN_MASK ; 
 int MPLL_LOLEN (int) ; 
 int MPLL_LOLEN_MASK ; 
 int MPLL_REF_DIV (int) ; 
 int MPLL_REF_DIV_MASK ; 
 int SSEN ; 
 void* cpu_to_be32 (int) ; 
 int radeon_atom_get_clock_dividers (struct radeon_device*,int /*<<< orphan*/ ,int,int,struct atom_clock_dividers*) ; 
 scalar_t__ radeon_atombios_get_asic_ss_info (struct radeon_device*,struct radeon_atom_ss*,int /*<<< orphan*/ ,int) ; 
 struct rv7xx_power_info* rv770_get_pi (struct radeon_device*) ; 

int rv730_populate_mclk_value(struct radeon_device *rdev,
			      u32 engine_clock, u32 memory_clock,
			      LPRV7XX_SMC_MCLK_VALUE mclk)
{
	struct rv7xx_power_info *pi = rv770_get_pi(rdev);
	u32 mclk_pwrmgt_cntl = pi->clk_regs.rv730.mclk_pwrmgt_cntl;
	u32 dll_cntl = pi->clk_regs.rv730.dll_cntl;
	u32 mpll_func_cntl = pi->clk_regs.rv730.mpll_func_cntl;
	u32 mpll_func_cntl_2 = pi->clk_regs.rv730.mpll_func_cntl2;
	u32 mpll_func_cntl_3 = pi->clk_regs.rv730.mpll_func_cntl3;
	u32 mpll_ss = pi->clk_regs.rv730.mpll_ss;
	u32 mpll_ss2 = pi->clk_regs.rv730.mpll_ss2;
	struct atom_clock_dividers dividers;
	u32 post_divider, reference_divider;
	int ret;

	ret = radeon_atom_get_clock_dividers(rdev, COMPUTE_MEMORY_PLL_PARAM,
					     memory_clock, false, &dividers);
	if (ret)
		return ret;

	reference_divider = dividers.ref_div + 1;

	if (dividers.enable_post_div)
		post_divider = ((dividers.post_div >> 4) & 0xf) +
			(dividers.post_div & 0xf) + 2;
	else
		post_divider = 1;

	/* setup the registers */
	if (dividers.enable_post_div)
		mpll_func_cntl |= MPLL_DIVEN;
	else
		mpll_func_cntl &= ~MPLL_DIVEN;

	mpll_func_cntl &= ~(MPLL_REF_DIV_MASK | MPLL_HILEN_MASK | MPLL_LOLEN_MASK);
	mpll_func_cntl |= MPLL_REF_DIV(dividers.ref_div);
	mpll_func_cntl |= MPLL_HILEN((dividers.post_div >> 4) & 0xf);
	mpll_func_cntl |= MPLL_LOLEN(dividers.post_div & 0xf);

	mpll_func_cntl_3 &= ~MPLL_FB_DIV_MASK;
	mpll_func_cntl_3 |= MPLL_FB_DIV(dividers.fb_div);
	if (dividers.enable_dithen)
		mpll_func_cntl_3 |= MPLL_DITHEN;
	else
		mpll_func_cntl_3 &= ~MPLL_DITHEN;

	if (pi->mclk_ss) {
		struct radeon_atom_ss ss;
		u32 vco_freq = memory_clock * post_divider;

		if (radeon_atombios_get_asic_ss_info(rdev, &ss,
						     ASIC_INTERNAL_MEMORY_SS, vco_freq)) {
			u32 reference_clock = rdev->clock.mpll.reference_freq;
			u32 clk_s = reference_clock * 5 / (reference_divider * ss.rate);
			u32 clk_v = ss.percentage * dividers.fb_div / (clk_s * 10000);

			mpll_ss &= ~CLK_S_MASK;
			mpll_ss |= CLK_S(clk_s);
			mpll_ss |= SSEN;

			mpll_ss2 &= ~CLK_V_MASK;
			mpll_ss |= CLK_V(clk_v);
		}
	}


	mclk->mclk730.vMCLK_PWRMGT_CNTL = cpu_to_be32(mclk_pwrmgt_cntl);
	mclk->mclk730.vDLL_CNTL = cpu_to_be32(dll_cntl);
	mclk->mclk730.mclk_value = cpu_to_be32(memory_clock);
	mclk->mclk730.vMPLL_FUNC_CNTL = cpu_to_be32(mpll_func_cntl);
	mclk->mclk730.vMPLL_FUNC_CNTL2 = cpu_to_be32(mpll_func_cntl_2);
	mclk->mclk730.vMPLL_FUNC_CNTL3 = cpu_to_be32(mpll_func_cntl_3);
	mclk->mclk730.vMPLL_SS = cpu_to_be32(mpll_ss);
	mclk->mclk730.vMPLL_SS2 = cpu_to_be32(mpll_ss2);

	return 0;
}