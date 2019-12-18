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
struct st_slim_rproc {int /*<<< orphan*/  rproc; scalar_t__* clks; } ;

/* Variables and functions */
 int ST_SLIM_MAX_CLK ; 
 int /*<<< orphan*/  clk_put (scalar_t__) ; 
 int /*<<< orphan*/  rproc_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rproc_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slim_clk_disable (struct st_slim_rproc*) ; 

void st_slim_rproc_put(struct st_slim_rproc *slim_rproc)
{
	int clk;

	if (!slim_rproc)
		return;

	slim_clk_disable(slim_rproc);

	for (clk = 0; clk < ST_SLIM_MAX_CLK && slim_rproc->clks[clk]; clk++)
		clk_put(slim_rproc->clks[clk]);

	rproc_del(slim_rproc->rproc);
	rproc_free(slim_rproc->rproc);
}