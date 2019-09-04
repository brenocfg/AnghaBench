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
struct gm20b_clk {int /*<<< orphan*/  base; } ;
struct gk20a_pll {scalar_t__ m; scalar_t__ pl; void* n; } ;

/* Variables and functions */
 scalar_t__ gk20a_pllg_is_enabled (int /*<<< orphan*/ *) ; 
 void* gk20a_pllg_n_lo (int /*<<< orphan*/ *,struct gk20a_pll*) ; 
 int /*<<< orphan*/  gk20a_pllg_read_mnp (int /*<<< orphan*/ *,struct gk20a_pll*) ; 
 int gm20b_pllg_program_mnp (struct gm20b_clk*,struct gk20a_pll*) ; 
 int gm20b_pllg_slide (struct gm20b_clk*,void*) ; 

__attribute__((used)) static int
gm20b_pllg_program_mnp_slide(struct gm20b_clk *clk, const struct gk20a_pll *pll)
{
	struct gk20a_pll cur_pll;
	int ret;

	if (gk20a_pllg_is_enabled(&clk->base)) {
		gk20a_pllg_read_mnp(&clk->base, &cur_pll);

		/* just do NDIV slide if there is no change to M and PL */
		if (pll->m == cur_pll.m && pll->pl == cur_pll.pl)
			return gm20b_pllg_slide(clk, pll->n);

		/* slide down to current NDIV_LO */
		cur_pll.n = gk20a_pllg_n_lo(&clk->base, &cur_pll);
		ret = gm20b_pllg_slide(clk, cur_pll.n);
		if (ret)
			return ret;
	}

	/* program MNP with the new clock parameters and new NDIV_LO */
	cur_pll = *pll;
	cur_pll.n = gk20a_pllg_n_lo(&clk->base, &cur_pll);
	ret = gm20b_pllg_program_mnp(clk, &cur_pll);
	if (ret)
		return ret;

	/* slide up to new NDIV */
	return gm20b_pllg_slide(clk, pll->n);
}