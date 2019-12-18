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
struct sdhci_host {int flags; int /*<<< orphan*/  complete_wq; int /*<<< orphan*/  irq; int /*<<< orphan*/  hw_name; int /*<<< orphan*/  buf_ready_int; int /*<<< orphan*/  data_timer; int /*<<< orphan*/  timer; int /*<<< orphan*/  complete_work; struct mmc_host* mmc; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  SDHCI_INT_ENABLE ; 
 int /*<<< orphan*/  SDHCI_RESET_ALL ; 
 int /*<<< orphan*/  SDHCI_SIGNAL_ENABLE ; 
 int SDHCI_USE_64_BIT_DMA ; 
 int SDHCI_USE_ADMA ; 
 int SDHCI_USE_SDMA ; 
 unsigned int WQ_HIGHPRI ; 
 unsigned int WQ_MEM_RECLAIM ; 
 unsigned int WQ_UNBOUND ; 
 int /*<<< orphan*/  alloc_workqueue (char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct sdhci_host*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int mmc_add_host (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_dev (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_complete_work ; 
 int /*<<< orphan*/  sdhci_do_reset (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_enable_card_detection (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_init (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_irq ; 
 int sdhci_led_register (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_led_unregister (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_thread_irq ; 
 int /*<<< orphan*/  sdhci_timeout_data_timer ; 
 int /*<<< orphan*/  sdhci_timeout_timer ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int __sdhci_add_host(struct sdhci_host *host)
{
	unsigned int flags = WQ_UNBOUND | WQ_MEM_RECLAIM | WQ_HIGHPRI;
	struct mmc_host *mmc = host->mmc;
	int ret;

	host->complete_wq = alloc_workqueue("sdhci", flags, 0);
	if (!host->complete_wq)
		return -ENOMEM;

	INIT_WORK(&host->complete_work, sdhci_complete_work);

	timer_setup(&host->timer, sdhci_timeout_timer, 0);
	timer_setup(&host->data_timer, sdhci_timeout_data_timer, 0);

	init_waitqueue_head(&host->buf_ready_int);

	sdhci_init(host, 0);

	ret = request_threaded_irq(host->irq, sdhci_irq, sdhci_thread_irq,
				   IRQF_SHARED,	mmc_hostname(mmc), host);
	if (ret) {
		pr_err("%s: Failed to request IRQ %d: %d\n",
		       mmc_hostname(mmc), host->irq, ret);
		goto unwq;
	}

	ret = sdhci_led_register(host);
	if (ret) {
		pr_err("%s: Failed to register LED device: %d\n",
		       mmc_hostname(mmc), ret);
		goto unirq;
	}

	ret = mmc_add_host(mmc);
	if (ret)
		goto unled;

	pr_info("%s: SDHCI controller on %s [%s] using %s\n",
		mmc_hostname(mmc), host->hw_name, dev_name(mmc_dev(mmc)),
		(host->flags & SDHCI_USE_ADMA) ?
		(host->flags & SDHCI_USE_64_BIT_DMA) ? "ADMA 64-bit" : "ADMA" :
		(host->flags & SDHCI_USE_SDMA) ? "DMA" : "PIO");

	sdhci_enable_card_detection(host);

	return 0;

unled:
	sdhci_led_unregister(host);
unirq:
	sdhci_do_reset(host, SDHCI_RESET_ALL);
	sdhci_writel(host, 0, SDHCI_INT_ENABLE);
	sdhci_writel(host, 0, SDHCI_SIGNAL_ENABLE);
	free_irq(host->irq, host);
unwq:
	destroy_workqueue(host->complete_wq);

	return ret;
}