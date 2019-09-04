#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fimc_is {int /*<<< orphan*/ * clocks; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ISS_GATE_CLKS_MAX ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fimc_is_clocks ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fimc_is_enable_clocks(struct fimc_is *is)
{
	int i, ret;

	for (i = 0; i < ISS_GATE_CLKS_MAX; i++) {
		if (IS_ERR(is->clocks[i]))
			continue;
		ret = clk_prepare_enable(is->clocks[i]);
		if (ret < 0) {
			dev_err(&is->pdev->dev, "clock %s enable failed\n",
				fimc_is_clocks[i]);
			for (--i; i >= 0; i--)
				clk_disable(is->clocks[i]);
			return ret;
		}
		pr_debug("enabled clock: %s\n", fimc_is_clocks[i]);
	}
	return 0;
}