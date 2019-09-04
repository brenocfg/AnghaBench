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
struct mmc_ios {scalar_t__ clock; scalar_t__ bus_width; int /*<<< orphan*/  drv_type; int /*<<< orphan*/  signal_voltage; int /*<<< orphan*/  timing; int /*<<< orphan*/  power_mode; } ;
struct mmc_host {int dummy; } ;
struct bcm2835_host {scalar_t__ clock; int /*<<< orphan*/  lock; int /*<<< orphan*/  hcfg; scalar_t__ debug; } ;

/* Variables and functions */
 scalar_t__ MMC_BUS_WIDTH_4 ; 
 int /*<<< orphan*/  SDHCFG ; 
 int /*<<< orphan*/  SDHCFG_SLOW_CARD ; 
 int /*<<< orphan*/  SDHCFG_WIDE_EXT_BUS ; 
 int /*<<< orphan*/  SDHCFG_WIDE_INT_BUS ; 
 int /*<<< orphan*/  bcm2835_sdhost_set_clock (struct bcm2835_host*,scalar_t__) ; 
 int /*<<< orphan*/  bcm2835_sdhost_write (struct bcm2835_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_event (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 struct bcm2835_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void bcm2835_sdhost_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{

	struct bcm2835_host *host = mmc_priv(mmc);
	unsigned long flags;

	if (host->debug)
		pr_info("%s: ios clock %d, pwr %d, bus_width %d, "
			"timing %d, vdd %d, drv_type %d\n",
			mmc_hostname(mmc),
			ios->clock, ios->power_mode, ios->bus_width,
			ios->timing, ios->signal_voltage, ios->drv_type);

	spin_lock_irqsave(&host->lock, flags);

	log_event("IOS<", ios->clock, 0);

	/* set bus width */
	host->hcfg &= ~SDHCFG_WIDE_EXT_BUS;
	if (ios->bus_width == MMC_BUS_WIDTH_4)
		host->hcfg |= SDHCFG_WIDE_EXT_BUS;

	host->hcfg |= SDHCFG_WIDE_INT_BUS;

	/* Disable clever clock switching, to cope with fast core clocks */
	host->hcfg |= SDHCFG_SLOW_CARD;

	bcm2835_sdhost_write(host, host->hcfg, SDHCFG);

	mmiowb();

	spin_unlock_irqrestore(&host->lock, flags);

	if (!ios->clock || ios->clock != host->clock)
		bcm2835_sdhost_set_clock(host, ios->clock);
}