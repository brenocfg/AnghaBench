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
struct sunxi_mmc_host {int /*<<< orphan*/  reset; int /*<<< orphan*/  clk_ahb; int /*<<< orphan*/  clk_mmc; int /*<<< orphan*/  clk_output; int /*<<< orphan*/  clk_sample; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sunxi_mmc_reset_host (struct sunxi_mmc_host*) ; 

__attribute__((used)) static void sunxi_mmc_disable(struct sunxi_mmc_host *host)
{
	sunxi_mmc_reset_host(host);

	clk_disable_unprepare(host->clk_sample);
	clk_disable_unprepare(host->clk_output);
	clk_disable_unprepare(host->clk_mmc);
	clk_disable_unprepare(host->clk_ahb);

	if (!IS_ERR(host->reset))
		reset_control_assert(host->reset);
}