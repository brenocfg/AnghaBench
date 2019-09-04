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
struct meson_clk_mpll_data {int /*<<< orphan*/  flags; } ;
struct clk_regmap {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct meson_clk_mpll_data* meson_clk_mpll_data (struct clk_regmap*) ; 
 int /*<<< orphan*/  params_from_rate (unsigned long,unsigned long,unsigned int*,unsigned int*,int /*<<< orphan*/ ) ; 
 long rate_from_params (unsigned long,unsigned int,unsigned int) ; 
 struct clk_regmap* to_clk_regmap (struct clk_hw*) ; 

__attribute__((used)) static long mpll_round_rate(struct clk_hw *hw,
			    unsigned long rate,
			    unsigned long *parent_rate)
{
	struct clk_regmap *clk = to_clk_regmap(hw);
	struct meson_clk_mpll_data *mpll = meson_clk_mpll_data(clk);
	unsigned int sdm, n2;

	params_from_rate(rate, *parent_rate, &sdm, &n2, mpll->flags);
	return rate_from_params(*parent_rate, sdm, n2);
}