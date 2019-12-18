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
struct exynos_adc {int /*<<< orphan*/  dev; int /*<<< orphan*/  clk; int /*<<< orphan*/  sclk; TYPE_1__* data; } ;
struct TYPE_2__ {scalar_t__ needs_sclk; } ;

/* Variables and functions */
 int clk_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int exynos_adc_prepare_clk(struct exynos_adc *info)
{
	int ret;

	ret = clk_prepare(info->clk);
	if (ret) {
		dev_err(info->dev, "failed preparing adc clock: %d\n", ret);
		return ret;
	}

	if (info->data->needs_sclk) {
		ret = clk_prepare(info->sclk);
		if (ret) {
			clk_unprepare(info->clk);
			dev_err(info->dev,
				"failed preparing sclk_adc clock: %d\n", ret);
			return ret;
		}
	}

	return 0;
}