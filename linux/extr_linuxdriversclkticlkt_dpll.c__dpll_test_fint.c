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
struct dpll_data {int flags; unsigned int max_divider; unsigned int min_divider; } ;
struct clk_hw_omap {int /*<<< orphan*/  hw; struct dpll_data* dpll_data; } ;
struct TYPE_2__ {long fint_min; long fint_max; long fint_band1_max; long fint_band2_min; } ;

/* Variables and functions */
 int DPLL_FINT_INVALID ; 
 int DPLL_FINT_UNDERFLOW ; 
 int DPLL_J_TYPE ; 
 long OMAP3PLUS_DPLL_FINT_JTYPE_MAX ; 
 long OMAP3PLUS_DPLL_FINT_JTYPE_MIN ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  clk_hw_get_parent (int /*<<< orphan*/ *) ; 
 unsigned int clk_hw_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int) ; 
 TYPE_1__* ti_clk_get_features () ; 

__attribute__((used)) static int _dpll_test_fint(struct clk_hw_omap *clk, unsigned int n)
{
	struct dpll_data *dd;
	long fint, fint_min, fint_max;
	int ret = 0;

	dd = clk->dpll_data;

	/* DPLL divider must result in a valid jitter correction val */
	fint = clk_hw_get_rate(clk_hw_get_parent(&clk->hw)) / n;

	if (dd->flags & DPLL_J_TYPE) {
		fint_min = OMAP3PLUS_DPLL_FINT_JTYPE_MIN;
		fint_max = OMAP3PLUS_DPLL_FINT_JTYPE_MAX;
	} else {
		fint_min = ti_clk_get_features()->fint_min;
		fint_max = ti_clk_get_features()->fint_max;
	}

	if (!fint_min || !fint_max) {
		WARN(1, "No fint limits available!\n");
		return DPLL_FINT_INVALID;
	}

	if (fint < ti_clk_get_features()->fint_min) {
		pr_debug("rejecting n=%d due to Fint failure, lowering max_divider\n",
			 n);
		dd->max_divider = n;
		ret = DPLL_FINT_UNDERFLOW;
	} else if (fint > ti_clk_get_features()->fint_max) {
		pr_debug("rejecting n=%d due to Fint failure, boosting min_divider\n",
			 n);
		dd->min_divider = n;
		ret = DPLL_FINT_INVALID;
	} else if (fint > ti_clk_get_features()->fint_band1_max &&
		   fint < ti_clk_get_features()->fint_band2_min) {
		pr_debug("rejecting n=%d due to Fint failure\n", n);
		ret = DPLL_FINT_INVALID;
	}

	return ret;
}