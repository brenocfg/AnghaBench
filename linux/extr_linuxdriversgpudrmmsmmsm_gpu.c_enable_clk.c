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
struct msm_gpu {int fast_rate; int /*<<< orphan*/  grp_clks; int /*<<< orphan*/  nr_clocks; scalar_t__ rbbmtimer_clk; scalar_t__ core_clk; } ;

/* Variables and functions */
 int clk_bulk_prepare_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (scalar_t__,int) ; 

__attribute__((used)) static int enable_clk(struct msm_gpu *gpu)
{
	if (gpu->core_clk && gpu->fast_rate)
		clk_set_rate(gpu->core_clk, gpu->fast_rate);

	/* Set the RBBM timer rate to 19.2Mhz */
	if (gpu->rbbmtimer_clk)
		clk_set_rate(gpu->rbbmtimer_clk, 19200000);

	return clk_bulk_prepare_enable(gpu->nr_clocks, gpu->grp_clks);
}