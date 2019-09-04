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
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;
struct clk_pll {int post_div_shift; scalar_t__ post_div_width; int /*<<< orphan*/  config_reg; TYPE_1__ clkr; int /*<<< orphan*/  n_reg; int /*<<< orphan*/  m_reg; int /*<<< orphan*/  l_reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int BIT (scalar_t__) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct clk_pll* to_clk_pll (struct clk_hw*) ; 

__attribute__((used)) static unsigned long
clk_pll_recalc_rate(struct clk_hw *hw, unsigned long parent_rate)
{
	struct clk_pll *pll = to_clk_pll(hw);
	u32 l, m, n, config;
	unsigned long rate;
	u64 tmp;

	regmap_read(pll->clkr.regmap, pll->l_reg, &l);
	regmap_read(pll->clkr.regmap, pll->m_reg, &m);
	regmap_read(pll->clkr.regmap, pll->n_reg, &n);

	l &= 0x3ff;
	m &= 0x7ffff;
	n &= 0x7ffff;

	rate = parent_rate * l;
	if (n) {
		tmp = parent_rate;
		tmp *= m;
		do_div(tmp, n);
		rate += tmp;
	}
	if (pll->post_div_width) {
		regmap_read(pll->clkr.regmap, pll->config_reg, &config);
		config >>= pll->post_div_shift;
		config &= BIT(pll->post_div_width) - 1;
		rate /= config + 1;
	}

	return rate;
}