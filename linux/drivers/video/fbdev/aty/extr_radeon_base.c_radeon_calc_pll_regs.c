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
typedef  int u32 ;
struct TYPE_2__ {unsigned long ppll_max; unsigned long ppll_min; int ref_div; int /*<<< orphan*/  ref_clk; } ;
struct radeonfb_info {scalar_t__ family; TYPE_1__ pll; scalar_t__ has_CRTC2; } ;
struct radeon_regs {int ppll_ref_div; int ppll_div_3; } ;

/* Variables and functions */
 scalar_t__ CHIP_FAMILY_R200 ; 
 int /*<<< orphan*/  DISP_OUTPUT_CNTL ; 
 int /*<<< orphan*/  FP2_GEN_CNTL ; 
 int FP2_ON ; 
 int INREG (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_R300_VARIANT (struct radeonfb_info*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 
 int round_div (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void radeon_calc_pll_regs(struct radeonfb_info *rinfo, struct radeon_regs *regs,
				 unsigned long freq)
{
	static const struct {
		int divider;
		int bitvalue;
	} *post_div,
	  post_divs[] = {
		{ 1,  0 },
		{ 2,  1 },
		{ 4,  2 },
		{ 8,  3 },
		{ 3,  4 },
		{ 16, 5 },
		{ 6,  6 },
		{ 12, 7 },
		{ 0,  0 },
	};
	int fb_div, pll_output_freq = 0;
	int uses_dvo = 0;

	/* Check if the DVO port is enabled and sourced from the primary CRTC. I'm
	 * not sure which model starts having FP2_GEN_CNTL, I assume anything more
	 * recent than an r(v)100...
	 */
#if 1
	/* XXX I had reports of flicker happening with the cinema display
	 * on TMDS1 that seem to be fixed if I also forbit odd dividers in
	 * this case. This could just be a bandwidth calculation issue, I
	 * haven't implemented the bandwidth code yet, but in the meantime,
	 * forcing uses_dvo to 1 fixes it and shouln't have bad side effects,
	 * I haven't seen a case were were absolutely needed an odd PLL
	 * divider. I'll find a better fix once I have more infos on the
	 * real cause of the problem.
	 */
	while (rinfo->has_CRTC2) {
		u32 fp2_gen_cntl = INREG(FP2_GEN_CNTL);
		u32 disp_output_cntl;
		int source;

		/* FP2 path not enabled */
		if ((fp2_gen_cntl & FP2_ON) == 0)
			break;
		/* Not all chip revs have the same format for this register,
		 * extract the source selection
		 */
		if (rinfo->family == CHIP_FAMILY_R200 || IS_R300_VARIANT(rinfo)) {
			source = (fp2_gen_cntl >> 10) & 0x3;
			/* sourced from transform unit, check for transform unit
			 * own source
			 */
			if (source == 3) {
				disp_output_cntl = INREG(DISP_OUTPUT_CNTL);
				source = (disp_output_cntl >> 12) & 0x3;
			}
		} else
			source = (fp2_gen_cntl >> 13) & 0x1;
		/* sourced from CRTC2 -> exit */
		if (source == 1)
			break;

		/* so we end up on CRTC1, let's set uses_dvo to 1 now */
		uses_dvo = 1;
		break;
	}
#else
	uses_dvo = 1;
#endif
	if (freq > rinfo->pll.ppll_max)
		freq = rinfo->pll.ppll_max;
	if (freq*12 < rinfo->pll.ppll_min)
		freq = rinfo->pll.ppll_min / 12;
	pr_debug("freq = %lu, PLL min = %u, PLL max = %u\n",
	       freq, rinfo->pll.ppll_min, rinfo->pll.ppll_max);

	for (post_div = &post_divs[0]; post_div->divider; ++post_div) {
		pll_output_freq = post_div->divider * freq;
		/* If we output to the DVO port (external TMDS), we don't allow an
		 * odd PLL divider as those aren't supported on this path
		 */
		if (uses_dvo && (post_div->divider & 1))
			continue;
		if (pll_output_freq >= rinfo->pll.ppll_min  &&
		    pll_output_freq <= rinfo->pll.ppll_max)
			break;
	}

	/* If we fall through the bottom, try the "default value"
	   given by the terminal post_div->bitvalue */
	if ( !post_div->divider ) {
		post_div = &post_divs[post_div->bitvalue];
		pll_output_freq = post_div->divider * freq;
	}
	pr_debug("ref_div = %d, ref_clk = %d, output_freq = %d\n",
	       rinfo->pll.ref_div, rinfo->pll.ref_clk,
	       pll_output_freq);

	/* If we fall through the bottom, try the "default value"
	   given by the terminal post_div->bitvalue */
	if ( !post_div->divider ) {
		post_div = &post_divs[post_div->bitvalue];
		pll_output_freq = post_div->divider * freq;
	}
	pr_debug("ref_div = %d, ref_clk = %d, output_freq = %d\n",
	       rinfo->pll.ref_div, rinfo->pll.ref_clk,
	       pll_output_freq);

	fb_div = round_div(rinfo->pll.ref_div*pll_output_freq,
				  rinfo->pll.ref_clk);
	regs->ppll_ref_div = rinfo->pll.ref_div;
	regs->ppll_div_3 = fb_div | (post_div->bitvalue << 16);

	pr_debug("post div = 0x%x\n", post_div->bitvalue);
	pr_debug("fb_div = 0x%x\n", fb_div);
	pr_debug("ppll_div_3 = 0x%x\n", regs->ppll_div_3);
}