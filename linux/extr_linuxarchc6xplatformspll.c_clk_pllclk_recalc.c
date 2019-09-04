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
typedef  int u8 ;
typedef  int u32 ;
struct pll_data {unsigned long input_rate; int flags; int /*<<< orphan*/  num; } ;
struct clk {unsigned long rate; int flags; TYPE_1__* parent; struct pll_data* pll_data; } ;
struct TYPE_2__ {unsigned long rate; } ;

/* Variables and functions */
 int FIXED_RATE_PLL ; 
 int /*<<< orphan*/  PLLCTL ; 
 int PLLCTL_PLLEN ; 
 int PLLDIV_EN ; 
 int PLLDIV_RATIO_MASK ; 
 int /*<<< orphan*/  PLLM ; 
 int PLLM_PLLM_MASK ; 
 int /*<<< orphan*/  PLLPOST ; 
 int /*<<< orphan*/  PLLPRE ; 
 int PLL_HAS_MUL ; 
 int PLL_HAS_POST ; 
 int PLL_HAS_PRE ; 
 int pll_read (struct pll_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,...) ; 

__attribute__((used)) static unsigned long clk_pllclk_recalc(struct clk *clk)
{
	u32 ctrl, mult = 0, prediv = 0, postdiv = 0;
	u8 bypass;
	struct pll_data *pll = clk->pll_data;
	unsigned long rate = clk->rate;

	if (clk->flags & FIXED_RATE_PLL)
		return rate;

	ctrl = pll_read(pll, PLLCTL);
	rate = pll->input_rate = clk->parent->rate;

	if (ctrl & PLLCTL_PLLEN)
		bypass = 0;
	else
		bypass = 1;

	if (pll->flags & PLL_HAS_MUL) {
		mult = pll_read(pll, PLLM);
		mult = (mult & PLLM_PLLM_MASK) + 1;
	}
	if (pll->flags & PLL_HAS_PRE) {
		prediv = pll_read(pll, PLLPRE);
		if (prediv & PLLDIV_EN)
			prediv = (prediv & PLLDIV_RATIO_MASK) + 1;
		else
			prediv = 0;
	}
	if (pll->flags & PLL_HAS_POST) {
		postdiv = pll_read(pll, PLLPOST);
		if (postdiv & PLLDIV_EN)
			postdiv = (postdiv & PLLDIV_RATIO_MASK) + 1;
		else
			postdiv = 1;
	}

	if (!bypass) {
		if (prediv)
			rate /= prediv;
		if (mult)
			rate *= mult;
		if (postdiv)
			rate /= postdiv;

		pr_debug("PLL%d: input = %luMHz, pre[%d] mul[%d] post[%d] "
			 "--> %luMHz output.\n",
			 pll->num, clk->parent->rate / 1000000,
			 prediv, mult, postdiv, rate / 1000000);
	} else
		pr_debug("PLL%d: input = %luMHz, bypass mode.\n",
			 pll->num, clk->parent->rate / 1000000);

	return rate;
}