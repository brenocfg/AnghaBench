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
struct intel_crtc_state {int dummy; } ;
struct intel_crtc {int /*<<< orphan*/  pipe; } ;
struct dpll {int m1; int m2; int /*<<< orphan*/  vco; int /*<<< orphan*/  n; int /*<<< orphan*/  p2; int /*<<< orphan*/  p1; } ;
struct bxt_clk_div {int m2_int; int m2_frac; int m2_frac_en; int /*<<< orphan*/  vco; int /*<<< orphan*/  n; int /*<<< orphan*/  p2; int /*<<< orphan*/  p1; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bxt_find_best_dpll (struct intel_crtc_state*,int,struct dpll*) ; 
 int /*<<< orphan*/  pipe_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
bxt_ddi_hdmi_pll_dividers(struct intel_crtc *intel_crtc,
			  struct intel_crtc_state *crtc_state, int clock,
			  struct bxt_clk_div *clk_div)
{
	struct dpll best_clock;

	/* Calculate HDMI div */
	/*
	 * FIXME: tie the following calculation into
	 * i9xx_crtc_compute_clock
	 */
	if (!bxt_find_best_dpll(crtc_state, clock, &best_clock)) {
		DRM_DEBUG_DRIVER("no PLL dividers found for clock %d pipe %c\n",
				 clock, pipe_name(intel_crtc->pipe));
		return false;
	}

	clk_div->p1 = best_clock.p1;
	clk_div->p2 = best_clock.p2;
	WARN_ON(best_clock.m1 != 2);
	clk_div->n = best_clock.n;
	clk_div->m2_int = best_clock.m2 >> 22;
	clk_div->m2_frac = best_clock.m2 & ((1 << 22) - 1);
	clk_div->m2_frac_en = clk_div->m2_frac != 0;

	clk_div->vco = best_clock.vco;

	return true;
}