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
struct usdhi6_host {int /*<<< orphan*/  mmc; int /*<<< orphan*/  clk; int /*<<< orphan*/  timeout_work; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_free_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_remove_host (int /*<<< orphan*/ ) ; 
 struct usdhi6_host* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  usdhi6_dma_release (struct usdhi6_host*) ; 
 int /*<<< orphan*/  usdhi6_mask_all (struct usdhi6_host*) ; 

__attribute__((used)) static int usdhi6_remove(struct platform_device *pdev)
{
	struct usdhi6_host *host = platform_get_drvdata(pdev);

	mmc_remove_host(host->mmc);

	usdhi6_mask_all(host);
	cancel_delayed_work_sync(&host->timeout_work);
	usdhi6_dma_release(host);
	clk_disable_unprepare(host->clk);
	mmc_free_host(host->mmc);

	return 0;
}