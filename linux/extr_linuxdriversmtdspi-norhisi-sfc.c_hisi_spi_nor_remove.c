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
struct hifmc_host {int /*<<< orphan*/  clk; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_spi_nor_unregister_all (struct hifmc_host*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 struct hifmc_host* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int hisi_spi_nor_remove(struct platform_device *pdev)
{
	struct hifmc_host *host = platform_get_drvdata(pdev);

	hisi_spi_nor_unregister_all(host);
	mutex_destroy(&host->lock);
	clk_disable_unprepare(host->clk);
	return 0;
}