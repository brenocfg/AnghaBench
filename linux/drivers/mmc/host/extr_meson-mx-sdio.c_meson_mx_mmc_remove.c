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
struct platform_device {int dummy; } ;
struct meson_mx_mmc_host {int /*<<< orphan*/  mmc; int /*<<< orphan*/  core_clk; int /*<<< orphan*/  cfg_div_clk; int /*<<< orphan*/  cmd_timeout; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct device* mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_free_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_remove_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_platform_device_destroy (struct device*,int /*<<< orphan*/ *) ; 
 struct meson_mx_mmc_host* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int meson_mx_mmc_remove(struct platform_device *pdev)
{
	struct meson_mx_mmc_host *host = platform_get_drvdata(pdev);
	struct device *slot_dev = mmc_dev(host->mmc);

	del_timer_sync(&host->cmd_timeout);

	mmc_remove_host(host->mmc);

	of_platform_device_destroy(slot_dev, NULL);

	clk_disable_unprepare(host->cfg_div_clk);
	clk_disable_unprepare(host->core_clk);

	mmc_free_host(host->mmc);

	return 0;
}