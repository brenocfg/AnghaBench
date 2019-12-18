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
struct st_slim_rproc {scalar_t__* clks; } ;

/* Variables and functions */
 int ST_SLIM_MAX_CLK ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 

__attribute__((used)) static void slim_clk_disable(struct st_slim_rproc *slim_rproc)
{
	int clk;

	for (clk = 0; clk < ST_SLIM_MAX_CLK && slim_rproc->clks[clk]; clk++)
		clk_disable_unprepare(slim_rproc->clks[clk]);
}