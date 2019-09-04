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
struct intel_dpll_hw_state {int pll0; int pll3; int pll2; int pll1; int ebb0; } ;
struct intel_crtc_state {struct intel_dpll_hw_state dpll_hw_state; int /*<<< orphan*/  shared_dpll; } ;
struct dpll {int m1; int m2; int n; int p1; int p2; } ;

/* Variables and functions */
 int PORT_PLL_M2_FRAC_ENABLE ; 
 int PORT_PLL_M2_FRAC_MASK ; 
 int PORT_PLL_M2_MASK ; 
 int PORT_PLL_N_MASK ; 
 int PORT_PLL_N_SHIFT ; 
 int PORT_PLL_P1_MASK ; 
 int PORT_PLL_P1_SHIFT ; 
 int PORT_PLL_P2_MASK ; 
 int PORT_PLL_P2_SHIFT ; 
 scalar_t__ WARN_ON (int) ; 
 int chv_calc_dpll_params (int,struct dpll*) ; 

__attribute__((used)) static int bxt_calc_pll_link(struct intel_crtc_state *crtc_state)
{
	struct intel_dpll_hw_state *state;
	struct dpll clock;

	/* For DDI ports we always use a shared PLL. */
	if (WARN_ON(!crtc_state->shared_dpll))
		return 0;

	state = &crtc_state->dpll_hw_state;

	clock.m1 = 2;
	clock.m2 = (state->pll0 & PORT_PLL_M2_MASK) << 22;
	if (state->pll3 & PORT_PLL_M2_FRAC_ENABLE)
		clock.m2 |= state->pll2 & PORT_PLL_M2_FRAC_MASK;
	clock.n = (state->pll1 & PORT_PLL_N_MASK) >> PORT_PLL_N_SHIFT;
	clock.p1 = (state->ebb0 & PORT_PLL_P1_MASK) >> PORT_PLL_P1_SHIFT;
	clock.p2 = (state->ebb0 & PORT_PLL_P2_MASK) >> PORT_PLL_P2_SHIFT;

	return chv_calc_dpll_params(100000, &clock);
}