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
struct clk_rate_request {long rate; long best_parent_rate; struct clk_hw* best_parent_hw; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 long EINVAL ; 
 long INT_MAX ; 
 long alchemy_calc_div (long,long,int,int,int /*<<< orphan*/ *) ; 
 struct clk_hw* clk_hw_get_parent_by_index (struct clk_hw*,int) ; 
 long clk_hw_get_rate (struct clk_hw*) ; 
 int /*<<< orphan*/  clk_hw_is_prepared (struct clk_hw*) ; 
 long clk_hw_round_rate (struct clk_hw*,long) ; 

__attribute__((used)) static int alchemy_clk_fgcs_detr(struct clk_hw *hw,
				 struct clk_rate_request *req,
				 int scale, int maxdiv)
{
	struct clk_hw *pc, *bpc, *free;
	long tdv, tpr, pr, nr, br, bpr, diff, lastdiff;
	int j;

	lastdiff = INT_MAX;
	bpr = 0;
	bpc = NULL;
	br = -EINVAL;
	free = NULL;

	/* look at the rates each enabled parent supplies and select
	 * the one that gets closest to but not over the requested rate.
	 */
	for (j = 0; j < 7; j++) {
		pc = clk_hw_get_parent_by_index(hw, j);
		if (!pc)
			break;

		/* if this parent is currently unused, remember it.
		 * XXX: we would actually want clk_has_active_children()
		 * but this is a good-enough approximation for now.
		 */
		if (!clk_hw_is_prepared(pc)) {
			if (!free)
				free = pc;
		}

		pr = clk_hw_get_rate(pc);
		if (pr < req->rate)
			continue;

		/* what can hardware actually provide */
		tdv = alchemy_calc_div(req->rate, pr, scale, maxdiv, NULL);
		nr = pr / tdv;
		diff = req->rate - nr;
		if (nr > req->rate)
			continue;

		if (diff < lastdiff) {
			lastdiff = diff;
			bpr = pr;
			bpc = pc;
			br = nr;
		}
		if (diff == 0)
			break;
	}

	/* if we couldn't get the exact rate we wanted from the enabled
	 * parents, maybe we can tell an available disabled/inactive one
	 * to give us a rate we can divide down to the requested rate.
	 */
	if (lastdiff && free) {
		for (j = (maxdiv == 4) ? 1 : scale; j <= maxdiv; j += scale) {
			tpr = req->rate * j;
			if (tpr < 0)
				break;
			pr = clk_hw_round_rate(free, tpr);

			tdv = alchemy_calc_div(req->rate, pr, scale, maxdiv,
					       NULL);
			nr = pr / tdv;
			diff = req->rate - nr;
			if (nr > req->rate)
				continue;
			if (diff < lastdiff) {
				lastdiff = diff;
				bpr = pr;
				bpc = free;
				br = nr;
			}
			if (diff == 0)
				break;
		}
	}

	if (br < 0)
		return br;

	req->best_parent_rate = bpr;
	req->best_parent_hw = bpc;
	req->rate = br;

	return 0;
}