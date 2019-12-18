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
struct TYPE_4__ {int parent_rate; TYPE_1__* params; } ;
struct gm20b_clk {int safe_fmax_vmin; TYPE_2__ base; } ;
struct gk20a_pll {int m; int n; void* pl; } ;
struct TYPE_3__ {int min_vco; } ;

/* Variables and functions */
 void* DIV_ROUND_UP (int,int) ; 
 int KHZ ; 
 int gk20a_pllg_calc_rate (TYPE_2__*,struct gk20a_pll*) ; 

__attribute__((used)) static void
gm20b_dvfs_calc_safe_pll(struct gm20b_clk *clk, struct gk20a_pll *pll)
{
	u32 rate = gk20a_pllg_calc_rate(&clk->base, pll) / KHZ;
	u32 parent_rate = clk->base.parent_rate / KHZ;
	u32 nmin, nsafe;

	/* remove a safe margin of 10% */
	if (rate > clk->safe_fmax_vmin)
		rate = rate * (100 - 10) / 100;

	/* gpc2clk */
	rate *= 2;

	nmin = DIV_ROUND_UP(pll->m * clk->base.params->min_vco, parent_rate);
	nsafe = pll->m * rate / (clk->base.parent_rate);

	if (nsafe < nmin) {
		pll->pl = DIV_ROUND_UP(nmin * parent_rate, pll->m * rate);
		nsafe = nmin;
	}

	pll->n = nsafe;
}