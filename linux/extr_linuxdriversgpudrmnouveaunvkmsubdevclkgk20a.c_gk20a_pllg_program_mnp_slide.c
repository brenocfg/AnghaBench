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
struct gk20a_pll {scalar_t__ m; scalar_t__ pl; void* n; } ;
struct gk20a_clk {int dummy; } ;

/* Variables and functions */
 scalar_t__ gk20a_pllg_is_enabled (struct gk20a_clk*) ; 
 void* gk20a_pllg_n_lo (struct gk20a_clk*,struct gk20a_pll*) ; 
 int gk20a_pllg_program_mnp (struct gk20a_clk*,struct gk20a_pll*) ; 
 int /*<<< orphan*/  gk20a_pllg_read_mnp (struct gk20a_clk*,struct gk20a_pll*) ; 
 int gk20a_pllg_slide (struct gk20a_clk*,void*) ; 

__attribute__((used)) static int
gk20a_pllg_program_mnp_slide(struct gk20a_clk *clk, const struct gk20a_pll *pll)
{
	struct gk20a_pll cur_pll;
	int ret;

	if (gk20a_pllg_is_enabled(clk)) {
		gk20a_pllg_read_mnp(clk, &cur_pll);

		/* just do NDIV slide if there is no change to M and PL */
		if (pll->m == cur_pll.m && pll->pl == cur_pll.pl)
			return gk20a_pllg_slide(clk, pll->n);

		/* slide down to current NDIV_LO */
		cur_pll.n = gk20a_pllg_n_lo(clk, &cur_pll);
		ret = gk20a_pllg_slide(clk, cur_pll.n);
		if (ret)
			return ret;
	}

	/* program MNP with the new clock parameters and new NDIV_LO */
	cur_pll = *pll;
	cur_pll.n = gk20a_pllg_n_lo(clk, &cur_pll);
	ret = gk20a_pllg_program_mnp(clk, &cur_pll);
	if (ret)
		return ret;

	/* slide up to new NDIV */
	return gk20a_pllg_slide(clk, pll->n);
}