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
struct mmc_host {int sdio_irqs; int caps2; int caps; TYPE_1__* ops; int /*<<< orphan*/  sdio_irq_thread; int /*<<< orphan*/  sdio_irq_thread_abort; int /*<<< orphan*/  claimed; } ;
struct mmc_card {struct mmc_host* host; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable_sdio_irq ) (struct mmc_host*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int MMC_CAP2_SDIO_IRQ_NOTHREAD ; 
 int MMC_CAP_SDIO_IRQ ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct mmc_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sdio_card_irq_put(struct mmc_card *card)
{
	struct mmc_host *host = card->host;

	WARN_ON(!host->claimed);

	if (host->sdio_irqs < 1)
		return -EINVAL;

	if (!--host->sdio_irqs) {
		if (!(host->caps2 & MMC_CAP2_SDIO_IRQ_NOTHREAD)) {
			atomic_set(&host->sdio_irq_thread_abort, 1);
			kthread_stop(host->sdio_irq_thread);
		} else if (host->caps & MMC_CAP_SDIO_IRQ) {
			host->ops->enable_sdio_irq(host, 0);
		}
	}

	return 0;
}