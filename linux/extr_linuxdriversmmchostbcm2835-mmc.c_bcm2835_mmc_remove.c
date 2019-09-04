#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct platform_device {int dummy; } ;
struct bcm2835_host {int /*<<< orphan*/  mmc; scalar_t__ dma_chan_rxtx; int /*<<< orphan*/  finish_tasklet; int /*<<< orphan*/  timer; int /*<<< orphan*/  irq; int /*<<< orphan*/  lock; TYPE_2__* mrq; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {TYPE_1__* cmd; } ;
struct TYPE_3__ {int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEDIUM ; 
 int /*<<< orphan*/  SDHCI_DEVICE_DEAD ; 
 int /*<<< orphan*/  SDHCI_INT_STATUS ; 
 int /*<<< orphan*/  SDHCI_RESET_ALL ; 
 scalar_t__ bcm2835_mmc_readl (struct bcm2835_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_mmc_reset (struct bcm2835_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_release_channel (scalar_t__) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct bcm2835_host*) ; 
 int /*<<< orphan*/  mmc_free_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_remove_host (int /*<<< orphan*/ ) ; 
 struct bcm2835_host* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm2835_mmc_remove(struct platform_device *pdev)
{
	struct bcm2835_host *host = platform_get_drvdata(pdev);
	unsigned long flags;
	int dead;
	u32 scratch;

	dead = 0;
	scratch = bcm2835_mmc_readl(host, SDHCI_INT_STATUS);
	if (scratch == (u32)-1)
		dead = 1;


	if (dead) {
		spin_lock_irqsave(&host->lock, flags);

		host->flags |= SDHCI_DEVICE_DEAD;

		if (host->mrq) {
			pr_err("%s: Controller removed during "
				" transfer!\n", mmc_hostname(host->mmc));

			host->mrq->cmd->error = -ENOMEDIUM;
			tasklet_schedule(&host->finish_tasklet);
		}

		spin_unlock_irqrestore(&host->lock, flags);
	}

	mmc_remove_host(host->mmc);

	if (!dead)
		bcm2835_mmc_reset(host, SDHCI_RESET_ALL);

	free_irq(host->irq, host);

	del_timer_sync(&host->timer);

	tasklet_kill(&host->finish_tasklet);

	if (host->dma_chan_rxtx)
		dma_release_channel(host->dma_chan_rxtx);

	mmc_free_host(host->mmc);

	return 0;
}