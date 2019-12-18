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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct msm_gpu {int nr_clocks; int /*<<< orphan*/  grp_clks; void* rbbmtimer_clk; void* core_clk; } ;

/* Variables and functions */
 int devm_clk_bulk_get_all (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* msm_clk_bulk_get_clock (int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int get_clocks(struct platform_device *pdev, struct msm_gpu *gpu)
{
	int ret = devm_clk_bulk_get_all(&pdev->dev, &gpu->grp_clks);

	if (ret < 1) {
		gpu->nr_clocks = 0;
		return ret;
	}

	gpu->nr_clocks = ret;

	gpu->core_clk = msm_clk_bulk_get_clock(gpu->grp_clks,
		gpu->nr_clocks, "core");

	gpu->rbbmtimer_clk = msm_clk_bulk_get_clock(gpu->grp_clks,
		gpu->nr_clocks, "rbbmtimer");

	return 0;
}