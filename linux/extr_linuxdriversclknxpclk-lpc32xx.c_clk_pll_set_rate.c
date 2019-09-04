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
typedef  int u32 ;
struct lpc32xx_pll_clk {int mode; unsigned long m_div; unsigned long n_div; int p_div; int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PLL_BYPASS 132 
 int PLL_CTRL_BYPASS ; 
 int PLL_CTRL_DIRECT ; 
 int PLL_CTRL_FEEDBACK ; 
#define  PLL_DIRECT 131 
#define  PLL_DIRECT_BYPASS 130 
#define  PLL_INTEGER 129 
#define  PLL_NON_INTEGER 128 
 int /*<<< orphan*/  clk_regmap ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct lpc32xx_pll_clk* to_lpc32xx_pll_clk (struct clk_hw*) ; 

__attribute__((used)) static int clk_pll_set_rate(struct clk_hw *hw, unsigned long rate,
			    unsigned long parent_rate)
{
	struct lpc32xx_pll_clk *clk = to_lpc32xx_pll_clk(hw);
	u32 val;
	unsigned long new_rate;

	/* Validate PLL clock parameters computed on round rate stage */
	switch (clk->mode) {
	case PLL_DIRECT:
		val = PLL_CTRL_DIRECT;
		val |= (clk->m_div - 1) << 1;
		val |= (clk->n_div - 1) << 9;
		new_rate = (parent_rate * clk->m_div) / clk->n_div;
		break;
	case PLL_BYPASS:
		val = PLL_CTRL_BYPASS;
		val |= (clk->p_div - 1) << 11;
		new_rate = parent_rate / (1 << (clk->p_div));
		break;
	case PLL_DIRECT_BYPASS:
		val = PLL_CTRL_DIRECT | PLL_CTRL_BYPASS;
		new_rate = parent_rate;
		break;
	case PLL_INTEGER:
		val = PLL_CTRL_FEEDBACK;
		val |= (clk->m_div - 1) << 1;
		val |= (clk->n_div - 1) << 9;
		val |= (clk->p_div - 1) << 11;
		new_rate = (parent_rate * clk->m_div) / clk->n_div;
		break;
	case PLL_NON_INTEGER:
		val = 0x0;
		val |= (clk->m_div - 1) << 1;
		val |= (clk->n_div - 1) << 9;
		val |= (clk->p_div - 1) << 11;
		new_rate = (parent_rate * clk->m_div) /
				(clk->n_div * (1 << clk->p_div));
		break;
	default:
		return -EINVAL;
	}

	/* Sanity check that round rate is equal to the requested one */
	if (new_rate != rate)
		return -EINVAL;

	return regmap_update_bits(clk_regmap, clk->reg, 0x1FFFF, val);
}