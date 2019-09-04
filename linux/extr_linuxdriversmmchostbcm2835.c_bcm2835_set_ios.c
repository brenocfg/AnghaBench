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
struct mmc_ios {scalar_t__ clock; scalar_t__ bus_width; } ;
struct mmc_host {int dummy; } ;
struct bcm2835_host {scalar_t__ clock; int /*<<< orphan*/  mutex; scalar_t__ ioaddr; int /*<<< orphan*/  hcfg; } ;

/* Variables and functions */
 scalar_t__ MMC_BUS_WIDTH_4 ; 
 scalar_t__ SDHCFG ; 
 int /*<<< orphan*/  SDHCFG_SLOW_CARD ; 
 int /*<<< orphan*/  SDHCFG_WIDE_EXT_BUS ; 
 int /*<<< orphan*/  SDHCFG_WIDE_INT_BUS ; 
 int /*<<< orphan*/  bcm2835_set_clock (struct bcm2835_host*,scalar_t__) ; 
 struct bcm2835_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void bcm2835_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct bcm2835_host *host = mmc_priv(mmc);

	mutex_lock(&host->mutex);

	if (!ios->clock || ios->clock != host->clock) {
		bcm2835_set_clock(host, ios->clock);
		host->clock = ios->clock;
	}

	/* set bus width */
	host->hcfg &= ~SDHCFG_WIDE_EXT_BUS;
	if (ios->bus_width == MMC_BUS_WIDTH_4)
		host->hcfg |= SDHCFG_WIDE_EXT_BUS;

	host->hcfg |= SDHCFG_WIDE_INT_BUS;

	/* Disable clever clock switching, to cope with fast core clocks */
	host->hcfg |= SDHCFG_SLOW_CARD;

	writel(host->hcfg, host->ioaddr + SDHCFG);

	mutex_unlock(&host->mutex);
}