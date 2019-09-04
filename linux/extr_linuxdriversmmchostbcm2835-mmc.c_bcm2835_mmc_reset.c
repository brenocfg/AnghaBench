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
typedef  int u8 ;
struct bcm2835_host {int max_delay; int /*<<< orphan*/  lock; int /*<<< orphan*/  mmc; scalar_t__ clock; } ;

/* Variables and functions */
 int SDHCI_RESET_ALL ; 
 int /*<<< orphan*/  SDHCI_SOFTWARE_RESET ; 
 int /*<<< orphan*/  bcm2835_mmc_dumpregs (struct bcm2835_host*) ; 
 int bcm2835_mmc_readb (struct bcm2835_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_mmc_writeb (struct bcm2835_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warning (char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void bcm2835_mmc_reset(struct bcm2835_host *host, u8 mask)
{
	unsigned long timeout;
	unsigned long flags;

	spin_lock_irqsave(&host->lock, flags);
	bcm2835_mmc_writeb(host, mask, SDHCI_SOFTWARE_RESET);

	if (mask & SDHCI_RESET_ALL)
		host->clock = 0;

	/* Wait max 100 ms */
	timeout = 100;

	/* hw clears the bit when it's done */
	while (bcm2835_mmc_readb(host, SDHCI_SOFTWARE_RESET) & mask) {
		if (timeout == 0) {
			pr_err("%s: Reset 0x%x never completed.\n",
				mmc_hostname(host->mmc), (int)mask);
			bcm2835_mmc_dumpregs(host);
			return;
		}
		timeout--;
		spin_unlock_irqrestore(&host->lock, flags);
		mdelay(1);
		spin_lock_irqsave(&host->lock, flags);
	}

	if (100-timeout > 10 && 100-timeout > host->max_delay) {
		host->max_delay = 100-timeout;
		pr_warning("Warning: MMC controller hung for %d ms\n", host->max_delay);
	}
	spin_unlock_irqrestore(&host->lock, flags);
}