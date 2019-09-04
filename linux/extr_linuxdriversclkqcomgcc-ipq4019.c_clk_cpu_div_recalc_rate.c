#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u64 ;
typedef  int u32 ;
struct clk_hw {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  regmap; } ;
struct TYPE_4__ {int shift; int /*<<< orphan*/  width; int /*<<< orphan*/  reg; TYPE_1__ clkr; } ;
struct clk_fepll {TYPE_2__ cdiv; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int clk_fepll_vco_calc_rate (struct clk_fepll*,unsigned long) ; 
 int /*<<< orphan*/  do_div (unsigned long,int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct clk_fepll* to_clk_fepll (struct clk_hw*) ; 

__attribute__((used)) static unsigned long
clk_cpu_div_recalc_rate(struct clk_hw *hw,
			unsigned long parent_rate)
{
	struct clk_fepll *pll = to_clk_fepll(hw);
	u32 cdiv, pre_div;
	u64 rate;

	regmap_read(pll->cdiv.clkr.regmap, pll->cdiv.reg, &cdiv);
	cdiv = (cdiv >> pll->cdiv.shift) & (BIT(pll->cdiv.width) - 1);

	/*
	 * Some dividers have value in 0.5 fraction so multiply both VCO
	 * frequency(parent_rate) and pre_div with 2 to make integer
	 * calculation.
	 */
	if (cdiv > 10)
		pre_div = (cdiv + 1) * 2;
	else
		pre_div = cdiv + 12;

	rate = clk_fepll_vco_calc_rate(pll, parent_rate) * 2;
	do_div(rate, pre_div);

	return rate;
}