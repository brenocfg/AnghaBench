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
struct mvsd_host {int /*<<< orphan*/  clk; int /*<<< orphan*/  timer; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_free_host (struct mmc_host*) ; 
 struct mvsd_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_remove_host (struct mmc_host*) ; 
 int /*<<< orphan*/  mvsd_power_down (struct mvsd_host*) ; 
 struct mmc_host* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int mvsd_remove(struct platform_device *pdev)
{
	struct mmc_host *mmc = platform_get_drvdata(pdev);

	struct mvsd_host *host = mmc_priv(mmc);

	mmc_remove_host(mmc);
	del_timer_sync(&host->timer);
	mvsd_power_down(host);

	if (!IS_ERR(host->clk))
		clk_disable_unprepare(host->clk);
	mmc_free_host(mmc);

	return 0;
}