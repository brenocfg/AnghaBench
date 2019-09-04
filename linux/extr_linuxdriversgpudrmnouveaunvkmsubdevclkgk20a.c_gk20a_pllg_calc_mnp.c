#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nvkm_subdev {int dummy; } ;
struct gk20a_pll {int m; int n; int pl; } ;
struct TYPE_3__ {struct nvkm_subdev subdev; } ;
struct gk20a_clk {unsigned long parent_rate; int (* div_to_pl ) (int) ;int (* pl_to_div ) (int) ;TYPE_2__* params; TYPE_1__ base; } ;
struct TYPE_4__ {int max_vco; int min_vco; int max_m; int min_n; int min_pl; int min_m; int min_u; int max_u; int max_n; int /*<<< orphan*/  max_pl; } ;

/* Variables and functions */
 unsigned long KHZ ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int abs (int) ; 
 int gk20a_pllg_calc_rate (struct gk20a_clk*,struct gk20a_pll*) ; 
 int max (int,int) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvkm_debug (struct nvkm_subdev*,char*,int,...) ; 
 int stub1 (int) ; 
 int stub2 (int) ; 
 int stub3 (int) ; 
 int stub4 (int) ; 
 int stub5 (int) ; 
 int stub6 (int) ; 
 int stub7 (int) ; 
 int stub8 (int) ; 

int
gk20a_pllg_calc_mnp(struct gk20a_clk *clk, unsigned long rate,
		    struct gk20a_pll *pll)
{
	struct nvkm_subdev *subdev = &clk->base.subdev;
	u32 target_clk_f, ref_clk_f, target_freq;
	u32 min_vco_f, max_vco_f;
	u32 low_pl, high_pl, best_pl;
	u32 target_vco_f;
	u32 best_m, best_n;
	u32 best_delta = ~0;
	u32 pl;

	target_clk_f = rate * 2 / KHZ;
	ref_clk_f = clk->parent_rate / KHZ;

	target_vco_f = target_clk_f + target_clk_f / 50;
	max_vco_f = max(clk->params->max_vco, target_vco_f);
	min_vco_f = clk->params->min_vco;
	best_m = clk->params->max_m;
	best_n = clk->params->min_n;
	best_pl = clk->params->min_pl;

	/* min_pl <= high_pl <= max_pl */
	high_pl = (max_vco_f + target_vco_f - 1) / target_vco_f;
	high_pl = min(high_pl, clk->params->max_pl);
	high_pl = max(high_pl, clk->params->min_pl);
	high_pl = clk->div_to_pl(high_pl);

	/* min_pl <= low_pl <= max_pl */
	low_pl = min_vco_f / target_vco_f;
	low_pl = min(low_pl, clk->params->max_pl);
	low_pl = max(low_pl, clk->params->min_pl);
	low_pl = clk->div_to_pl(low_pl);

	nvkm_debug(subdev, "low_PL %d(div%d), high_PL %d(div%d)", low_pl,
		   clk->pl_to_div(low_pl), high_pl, clk->pl_to_div(high_pl));

	/* Select lowest possible VCO */
	for (pl = low_pl; pl <= high_pl; pl++) {
		u32 m, n, n2;

		target_vco_f = target_clk_f * clk->pl_to_div(pl);

		for (m = clk->params->min_m; m <= clk->params->max_m; m++) {
			u32 u_f = ref_clk_f / m;

			if (u_f < clk->params->min_u)
				break;
			if (u_f > clk->params->max_u)
				continue;

			n = (target_vco_f * m) / ref_clk_f;
			n2 = ((target_vco_f * m) + (ref_clk_f - 1)) / ref_clk_f;

			if (n > clk->params->max_n)
				break;

			for (; n <= n2; n++) {
				u32 vco_f;

				if (n < clk->params->min_n)
					continue;
				if (n > clk->params->max_n)
					break;

				vco_f = ref_clk_f * n / m;

				if (vco_f >= min_vco_f && vco_f <= max_vco_f) {
					u32 delta, lwv;

					lwv = (vco_f + (clk->pl_to_div(pl) / 2))
						/ clk->pl_to_div(pl);
					delta = abs(lwv - target_clk_f);

					if (delta < best_delta) {
						best_delta = delta;
						best_m = m;
						best_n = n;
						best_pl = pl;

						if (best_delta == 0)
							goto found_match;
					}
				}
			}
		}
	}

found_match:
	WARN_ON(best_delta == ~0);

	if (best_delta != 0)
		nvkm_debug(subdev,
			   "no best match for target @ %dMHz on gpc_pll",
			   target_clk_f / KHZ);

	pll->m = best_m;
	pll->n = best_n;
	pll->pl = best_pl;

	target_freq = gk20a_pllg_calc_rate(clk, pll);

	nvkm_debug(subdev,
		   "actual target freq %d KHz, M %d, N %d, PL %d(div%d)\n",
		   target_freq / KHZ, pll->m, pll->n, pll->pl,
		   clk->pl_to_div(pll->pl));
	return 0;
}