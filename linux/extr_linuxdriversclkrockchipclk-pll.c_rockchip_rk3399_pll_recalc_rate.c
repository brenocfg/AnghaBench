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
typedef  int u64 ;
struct rockchip_pll_rate_table {int fbdiv; scalar_t__ dsmpd; unsigned long frac; int /*<<< orphan*/  postdiv2; int /*<<< orphan*/  postdiv1; int /*<<< orphan*/  refdiv; } ;
struct rockchip_clk_pll {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rockchip_rk3399_pll_get_params (struct rockchip_clk_pll*,struct rockchip_pll_rate_table*) ; 
 struct rockchip_clk_pll* to_rockchip_clk_pll (struct clk_hw*) ; 

__attribute__((used)) static unsigned long rockchip_rk3399_pll_recalc_rate(struct clk_hw *hw,
						     unsigned long prate)
{
	struct rockchip_clk_pll *pll = to_rockchip_clk_pll(hw);
	struct rockchip_pll_rate_table cur;
	u64 rate64 = prate;

	rockchip_rk3399_pll_get_params(pll, &cur);

	rate64 *= cur.fbdiv;
	do_div(rate64, cur.refdiv);

	if (cur.dsmpd == 0) {
		/* fractional mode */
		u64 frac_rate64 = prate * cur.frac;

		do_div(frac_rate64, cur.refdiv);
		rate64 += frac_rate64 >> 24;
	}

	do_div(rate64, cur.postdiv1);
	do_div(rate64, cur.postdiv2);

	return (unsigned long)rate64;
}