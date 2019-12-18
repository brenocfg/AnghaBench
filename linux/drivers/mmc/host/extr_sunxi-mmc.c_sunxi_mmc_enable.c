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
struct sunxi_mmc_host {int /*<<< orphan*/  reset; int /*<<< orphan*/  clk_ahb; int /*<<< orphan*/  clk_mmc; int /*<<< orphan*/  clk_output; int /*<<< orphan*/  clk_sample; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int reset_control_reset (int /*<<< orphan*/ ) ; 
 int sunxi_mmc_reset_host (struct sunxi_mmc_host*) ; 

__attribute__((used)) static int sunxi_mmc_enable(struct sunxi_mmc_host *host)
{
	int ret;

	if (!IS_ERR(host->reset)) {
		ret = reset_control_reset(host->reset);
		if (ret) {
			dev_err(host->dev, "Couldn't reset the MMC controller (%d)\n",
				ret);
			return ret;
		}
	}

	ret = clk_prepare_enable(host->clk_ahb);
	if (ret) {
		dev_err(host->dev, "Couldn't enable the bus clocks (%d)\n", ret);
		goto error_assert_reset;
	}

	ret = clk_prepare_enable(host->clk_mmc);
	if (ret) {
		dev_err(host->dev, "Enable mmc clk err %d\n", ret);
		goto error_disable_clk_ahb;
	}

	ret = clk_prepare_enable(host->clk_output);
	if (ret) {
		dev_err(host->dev, "Enable output clk err %d\n", ret);
		goto error_disable_clk_mmc;
	}

	ret = clk_prepare_enable(host->clk_sample);
	if (ret) {
		dev_err(host->dev, "Enable sample clk err %d\n", ret);
		goto error_disable_clk_output;
	}

	/*
	 * Sometimes the controller asserts the irq on boot for some reason,
	 * make sure the controller is in a sane state before enabling irqs.
	 */
	ret = sunxi_mmc_reset_host(host);
	if (ret)
		goto error_disable_clk_sample;

	return 0;

error_disable_clk_sample:
	clk_disable_unprepare(host->clk_sample);
error_disable_clk_output:
	clk_disable_unprepare(host->clk_output);
error_disable_clk_mmc:
	clk_disable_unprepare(host->clk_mmc);
error_disable_clk_ahb:
	clk_disable_unprepare(host->clk_ahb);
error_assert_reset:
	if (!IS_ERR(host->reset))
		reset_control_assert(host->reset);
	return ret;
}