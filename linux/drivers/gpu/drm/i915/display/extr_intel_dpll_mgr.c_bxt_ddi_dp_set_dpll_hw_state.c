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
struct bxt_clk_div {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bxt_ddi_dp_pll_dividers (struct intel_crtc_state*,struct bxt_clk_div*) ; 
 int bxt_ddi_set_dpll_hw_state (struct intel_crtc_state*,struct bxt_clk_div*) ; 

__attribute__((used)) static bool
bxt_ddi_dp_set_dpll_hw_state(struct intel_crtc_state *crtc_state)
{
	struct bxt_clk_div clk_div = {};

	bxt_ddi_dp_pll_dividers(crtc_state, &clk_div);

	return bxt_ddi_set_dpll_hw_state(crtc_state, &clk_div);
}