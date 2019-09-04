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
struct tegra_clk_pll_freq_table {unsigned long input_rate; unsigned long output_rate; int p; int /*<<< orphan*/  sdm_data; int /*<<< orphan*/  cpcon; int /*<<< orphan*/  n; int /*<<< orphan*/  m; } ;
struct tegra_clk_pll {TYPE_1__* params; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {scalar_t__ pdiv_tohw; struct tegra_clk_pll_freq_table* freq_table; } ;

/* Variables and functions */
 int EINVAL ; 
 int _p_div_to_hw (struct clk_hw*,int) ; 
 int ilog2 (int) ; 
 struct tegra_clk_pll* to_clk_pll (struct clk_hw*) ; 

__attribute__((used)) static int _get_table_rate(struct clk_hw *hw,
			   struct tegra_clk_pll_freq_table *cfg,
			   unsigned long rate, unsigned long parent_rate)
{
	struct tegra_clk_pll *pll = to_clk_pll(hw);
	struct tegra_clk_pll_freq_table *sel;
	int p;

	for (sel = pll->params->freq_table; sel->input_rate != 0; sel++)
		if (sel->input_rate == parent_rate &&
		    sel->output_rate == rate)
			break;

	if (sel->input_rate == 0)
		return -EINVAL;

	if (pll->params->pdiv_tohw) {
		p = _p_div_to_hw(hw, sel->p);
		if (p < 0)
			return p;
	} else {
		p = ilog2(sel->p);
	}

	cfg->input_rate = sel->input_rate;
	cfg->output_rate = sel->output_rate;
	cfg->m = sel->m;
	cfg->n = sel->n;
	cfg->p = p;
	cfg->cpcon = sel->cpcon;
	cfg->sdm_data = sel->sdm_data;

	return 0;
}