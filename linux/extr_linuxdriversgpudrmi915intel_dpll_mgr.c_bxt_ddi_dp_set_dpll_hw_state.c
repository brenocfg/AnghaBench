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
struct intel_dpll_hw_state {int dummy; } ;
struct bxt_clk_div {int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  bxt_ddi_dp_pll_dividers (int,struct bxt_clk_div*) ; 
 int bxt_ddi_set_dpll_hw_state (int,struct bxt_clk_div*,struct intel_dpll_hw_state*) ; 

__attribute__((used)) static bool
bxt_ddi_dp_set_dpll_hw_state(int clock,
			     struct intel_dpll_hw_state *dpll_hw_state)
{
	struct bxt_clk_div clk_div = {0};

	bxt_ddi_dp_pll_dividers(clock, &clk_div);

	return bxt_ddi_set_dpll_hw_state(clock, &clk_div, dpll_hw_state);
}