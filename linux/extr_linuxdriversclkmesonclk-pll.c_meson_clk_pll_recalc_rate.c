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
typedef  void* u16 ;
struct pll_rate_table {void* od3; void* od2; void* od; void* m; void* n; } ;
struct meson_clk_pll_data {int /*<<< orphan*/  frac; int /*<<< orphan*/  od3; int /*<<< orphan*/  od2; int /*<<< orphan*/  od; int /*<<< orphan*/  m; int /*<<< orphan*/  n; } ;
struct clk_regmap {int /*<<< orphan*/  map; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ MESON_PARM_APPLICABLE (int /*<<< orphan*/ *) ; 
 unsigned long __pll_params_to_rate (unsigned long,struct pll_rate_table*,void*,struct meson_clk_pll_data*) ; 
 struct meson_clk_pll_data* meson_clk_pll_data (struct clk_regmap*) ; 
 void* meson_parm_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct clk_regmap* to_clk_regmap (struct clk_hw*) ; 

__attribute__((used)) static unsigned long meson_clk_pll_recalc_rate(struct clk_hw *hw,
						unsigned long parent_rate)
{
	struct clk_regmap *clk = to_clk_regmap(hw);
	struct meson_clk_pll_data *pll = meson_clk_pll_data(clk);
	struct pll_rate_table pllt;
	u16 frac;

	pllt.n = meson_parm_read(clk->map, &pll->n);
	pllt.m = meson_parm_read(clk->map, &pll->m);
	pllt.od = meson_parm_read(clk->map, &pll->od);

	pllt.od2 = MESON_PARM_APPLICABLE(&pll->od2) ?
		meson_parm_read(clk->map, &pll->od2) :
		0;

	pllt.od3 = MESON_PARM_APPLICABLE(&pll->od3) ?
		meson_parm_read(clk->map, &pll->od3) :
		0;

	frac = MESON_PARM_APPLICABLE(&pll->frac) ?
		meson_parm_read(clk->map, &pll->frac) :
		0;

	return __pll_params_to_rate(parent_rate, &pllt, frac, pll);
}