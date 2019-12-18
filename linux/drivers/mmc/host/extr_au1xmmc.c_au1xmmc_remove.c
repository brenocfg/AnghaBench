#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct au1xmmc_host {int flags; TYPE_2__* mmc; int /*<<< orphan*/  ioarea; scalar_t__ iobase; int /*<<< orphan*/  irq; int /*<<< orphan*/  clk; int /*<<< orphan*/  finish_task; int /*<<< orphan*/  data_task; TYPE_1__* platdata; } ;
struct TYPE_6__ {int caps; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* cd_setup ) (TYPE_2__*,int /*<<< orphan*/ ) ;scalar_t__ led; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_CONFIG (struct au1xmmc_host*) ; 
 int /*<<< orphan*/  HOST_CONFIG2 (struct au1xmmc_host*) ; 
 int /*<<< orphan*/  HOST_ENABLE (struct au1xmmc_host*) ; 
 int HOST_F_DBDMA ; 
 int MMC_CAP_NEEDS_POLL ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au1xmmc_dbdma_shutdown (struct au1xmmc_host*) ; 
 int /*<<< orphan*/  au1xmmc_set_power (struct au1xmmc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct au1xmmc_host*) ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_classdev_unregister (scalar_t__) ; 
 int /*<<< orphan*/  mmc_free_host (TYPE_2__*) ; 
 int /*<<< orphan*/  mmc_remove_host (TYPE_2__*) ; 
 struct au1xmmc_host* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  release_resource (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int au1xmmc_remove(struct platform_device *pdev)
{
	struct au1xmmc_host *host = platform_get_drvdata(pdev);

	if (host) {
		mmc_remove_host(host->mmc);

#ifdef CONFIG_LEDS_CLASS
		if (host->platdata && host->platdata->led)
			led_classdev_unregister(host->platdata->led);
#endif

		if (host->platdata && host->platdata->cd_setup &&
		    !(host->mmc->caps & MMC_CAP_NEEDS_POLL))
			host->platdata->cd_setup(host->mmc, 0);

		__raw_writel(0, HOST_ENABLE(host));
		__raw_writel(0, HOST_CONFIG(host));
		__raw_writel(0, HOST_CONFIG2(host));
		wmb(); /* drain writebuffer */

		tasklet_kill(&host->data_task);
		tasklet_kill(&host->finish_task);

		if (host->flags & HOST_F_DBDMA)
			au1xmmc_dbdma_shutdown(host);

		au1xmmc_set_power(host, 0);

		clk_disable_unprepare(host->clk);
		clk_put(host->clk);

		free_irq(host->irq, host);
		iounmap((void *)host->iobase);
		release_resource(host->ioarea);
		kfree(host->ioarea);

		mmc_free_host(host->mmc);
	}
	return 0;
}