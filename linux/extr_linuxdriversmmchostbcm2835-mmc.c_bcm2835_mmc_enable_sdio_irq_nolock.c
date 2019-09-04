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
struct bcm2835_host {int flags; int /*<<< orphan*/  ier; } ;

/* Variables and functions */
 int SDHCI_DEVICE_DEAD ; 
 int /*<<< orphan*/  SDHCI_INT_CARD_INT ; 
 int /*<<< orphan*/  SDHCI_INT_ENABLE ; 
 int /*<<< orphan*/  SDHCI_SIGNAL_ENABLE ; 
 int /*<<< orphan*/  bcm2835_mmc_writel (struct bcm2835_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmiowb () ; 

__attribute__((used)) static void bcm2835_mmc_enable_sdio_irq_nolock(struct bcm2835_host *host, int enable)
{
	if (!(host->flags & SDHCI_DEVICE_DEAD)) {
		if (enable)
			host->ier |= SDHCI_INT_CARD_INT;
		else
			host->ier &= ~SDHCI_INT_CARD_INT;

		bcm2835_mmc_writel(host, host->ier, SDHCI_INT_ENABLE, 7);
		bcm2835_mmc_writel(host, host->ier, SDHCI_SIGNAL_ENABLE, 7);
		mmiowb();
	}
}