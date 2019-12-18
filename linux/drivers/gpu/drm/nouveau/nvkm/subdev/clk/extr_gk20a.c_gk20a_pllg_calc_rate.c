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
struct gk20a_pll {int n; int m; int /*<<< orphan*/  pl; } ;
struct gk20a_clk {int parent_rate; int (* pl_to_div ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ) ; 

u32
gk20a_pllg_calc_rate(struct gk20a_clk *clk, struct gk20a_pll *pll)
{
	u32 rate;
	u32 divider;

	rate = clk->parent_rate * pll->n;
	divider = pll->m * clk->pl_to_div(pll->pl);

	return rate / divider / 2;
}