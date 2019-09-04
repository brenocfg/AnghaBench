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
struct bcm2835_host {int ier; TYPE_1__* mmc; scalar_t__ clock; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  ios; } ;

/* Variables and functions */
 int SDHCI_INT_BUS_POWER ; 
 int SDHCI_INT_CRC ; 
 int SDHCI_INT_DATA_CRC ; 
 int SDHCI_INT_DATA_END ; 
 int SDHCI_INT_DATA_END_BIT ; 
 int SDHCI_INT_DATA_TIMEOUT ; 
 int /*<<< orphan*/  SDHCI_INT_ENABLE ; 
 int SDHCI_INT_END_BIT ; 
 int SDHCI_INT_INDEX ; 
 int SDHCI_INT_RESPONSE ; 
 int SDHCI_INT_TIMEOUT ; 
 int SDHCI_RESET_ALL ; 
 int SDHCI_RESET_CMD ; 
 int SDHCI_RESET_DATA ; 
 int /*<<< orphan*/  SDHCI_SIGNAL_ENABLE ; 
 int /*<<< orphan*/  bcm2835_mmc_reset (struct bcm2835_host*,int) ; 
 int /*<<< orphan*/  bcm2835_mmc_set_ios (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcm2835_mmc_writel (struct bcm2835_host*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void bcm2835_mmc_init(struct bcm2835_host *host, int soft)
{
	unsigned long flags;
	if (soft)
		bcm2835_mmc_reset(host, SDHCI_RESET_CMD|SDHCI_RESET_DATA);
	else
		bcm2835_mmc_reset(host, SDHCI_RESET_ALL);

	host->ier = SDHCI_INT_BUS_POWER | SDHCI_INT_DATA_END_BIT |
		    SDHCI_INT_DATA_CRC | SDHCI_INT_DATA_TIMEOUT |
		    SDHCI_INT_INDEX | SDHCI_INT_END_BIT | SDHCI_INT_CRC |
		    SDHCI_INT_TIMEOUT | SDHCI_INT_DATA_END |
		    SDHCI_INT_RESPONSE;

	spin_lock_irqsave(&host->lock, flags);
	bcm2835_mmc_writel(host, host->ier, SDHCI_INT_ENABLE, 3);
	bcm2835_mmc_writel(host, host->ier, SDHCI_SIGNAL_ENABLE, 3);
	spin_unlock_irqrestore(&host->lock, flags);

	if (soft) {
		/* force clock reconfiguration */
		host->clock = 0;
		bcm2835_mmc_set_ios(host->mmc, &host->mmc->ios);
	}
}