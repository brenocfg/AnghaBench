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
struct a6xx_gmu {int nr_clocks; int /*<<< orphan*/  clocks; int /*<<< orphan*/  core_clk; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int devm_clk_bulk_get_all (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_clk_bulk_get_clock (int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int a6xx_gmu_clocks_probe(struct a6xx_gmu *gmu)
{
	int ret = devm_clk_bulk_get_all(gmu->dev, &gmu->clocks);

	if (ret < 1)
		return ret;

	gmu->nr_clocks = ret;

	gmu->core_clk = msm_clk_bulk_get_clock(gmu->clocks,
		gmu->nr_clocks, "gmu");

	return 0;
}