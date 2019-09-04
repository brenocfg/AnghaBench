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
struct sdhci_host {int flags; int /*<<< orphan*/  lock; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int SDHCI_CARD_PRESENT ; 
 int SDHCI_DEVICE_DEAD ; 
 int /*<<< orphan*/  SDHCI_PRESENT_STATE ; 
 int mmc_gpio_get_cd (struct mmc_host*) ; 
 struct sdhci_host* mmc_priv (struct mmc_host*) ; 
 int sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int bxt_get_cd(struct mmc_host *mmc)
{
	int gpio_cd = mmc_gpio_get_cd(mmc);
	struct sdhci_host *host = mmc_priv(mmc);
	unsigned long flags;
	int ret = 0;

	if (!gpio_cd)
		return 0;

	spin_lock_irqsave(&host->lock, flags);

	if (host->flags & SDHCI_DEVICE_DEAD)
		goto out;

	ret = !!(sdhci_readl(host, SDHCI_PRESENT_STATE) & SDHCI_CARD_PRESENT);
out:
	spin_unlock_irqrestore(&host->lock, flags);

	return ret;
}