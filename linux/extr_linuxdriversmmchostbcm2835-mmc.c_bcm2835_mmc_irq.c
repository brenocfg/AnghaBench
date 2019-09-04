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
typedef  int u32 ;
struct bcm2835_host {int thread_isr; int /*<<< orphan*/  mmc; int /*<<< orphan*/  lock; } ;
typedef  scalar_t__ irqreturn_t ;

/* Variables and functions */
 scalar_t__ IRQ_HANDLED ; 
 scalar_t__ IRQ_NONE ; 
 scalar_t__ IRQ_WAKE_THREAD ; 
 int SDHCI_INT_BUS_POWER ; 
 int SDHCI_INT_CARD_INSERT ; 
 int SDHCI_INT_CARD_INT ; 
 int SDHCI_INT_CARD_REMOVE ; 
 int SDHCI_INT_CMD_MASK ; 
 int SDHCI_INT_DATA_MASK ; 
 int SDHCI_INT_ERROR ; 
 int /*<<< orphan*/  SDHCI_INT_STATUS ; 
 int /*<<< orphan*/  bcm2835_mmc_cmd_irq (struct bcm2835_host*,int) ; 
 int /*<<< orphan*/  bcm2835_mmc_data_irq (struct bcm2835_host*,int) ; 
 int /*<<< orphan*/  bcm2835_mmc_dumpregs (struct bcm2835_host*) ; 
 int /*<<< orphan*/  bcm2835_mmc_enable_sdio_irq_nolock (struct bcm2835_host*,int) ; 
 int bcm2835_mmc_readl (struct bcm2835_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_mmc_writel (struct bcm2835_host*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t bcm2835_mmc_irq(int irq, void *dev_id)
{
	irqreturn_t result = IRQ_NONE;
	struct bcm2835_host *host = dev_id;
	u32 intmask, mask, unexpected = 0;
	int max_loops = 16;

	spin_lock(&host->lock);

	intmask = bcm2835_mmc_readl(host, SDHCI_INT_STATUS);

	if (!intmask || intmask == 0xffffffff) {
		result = IRQ_NONE;
		goto out;
	}

	do {
		/* Clear selected interrupts. */
		mask = intmask & (SDHCI_INT_CMD_MASK | SDHCI_INT_DATA_MASK |
				  SDHCI_INT_BUS_POWER);
		bcm2835_mmc_writel(host, mask, SDHCI_INT_STATUS, 8);


		if (intmask & SDHCI_INT_CMD_MASK)
			bcm2835_mmc_cmd_irq(host, intmask & SDHCI_INT_CMD_MASK);

		if (intmask & SDHCI_INT_DATA_MASK)
			bcm2835_mmc_data_irq(host, intmask & SDHCI_INT_DATA_MASK);

		if (intmask & SDHCI_INT_BUS_POWER)
			pr_err("%s: Card is consuming too much power!\n",
				mmc_hostname(host->mmc));

		if (intmask & SDHCI_INT_CARD_INT) {
			bcm2835_mmc_enable_sdio_irq_nolock(host, false);
			host->thread_isr |= SDHCI_INT_CARD_INT;
			result = IRQ_WAKE_THREAD;
		}

		intmask &= ~(SDHCI_INT_CARD_INSERT | SDHCI_INT_CARD_REMOVE |
			     SDHCI_INT_CMD_MASK | SDHCI_INT_DATA_MASK |
			     SDHCI_INT_ERROR | SDHCI_INT_BUS_POWER |
			     SDHCI_INT_CARD_INT);

		if (intmask) {
			unexpected |= intmask;
			bcm2835_mmc_writel(host, intmask, SDHCI_INT_STATUS, 9);
		}

		if (result == IRQ_NONE)
			result = IRQ_HANDLED;

		intmask = bcm2835_mmc_readl(host, SDHCI_INT_STATUS);
	} while (intmask && --max_loops);
out:
	spin_unlock(&host->lock);

	if (unexpected) {
		pr_err("%s: Unexpected interrupt 0x%08x.\n",
			   mmc_hostname(host->mmc), unexpected);
		bcm2835_mmc_dumpregs(host);
	}

	return result;
}