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
typedef  int /*<<< orphan*/  u16 ;
struct mmc_ios {scalar_t__ clock; scalar_t__ bus_width; scalar_t__ drv_type; int /*<<< orphan*/  signal_voltage; int /*<<< orphan*/  timing; int /*<<< orphan*/  power_mode; } ;
struct mmc_host {int dummy; } ;
struct bcm2835_host {scalar_t__ clock; int pwr; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ MMC_BUS_WIDTH_4 ; 
 scalar_t__ MMC_SET_DRIVER_TYPE_A ; 
 scalar_t__ MMC_SET_DRIVER_TYPE_C ; 
 int /*<<< orphan*/  SDHCI_CLOCK_CARD_EN ; 
 int /*<<< orphan*/  SDHCI_CLOCK_CONTROL ; 
 int SDHCI_CTRL_4BITBUS ; 
 int SDHCI_CTRL_8BITBUS ; 
 int /*<<< orphan*/  SDHCI_CTRL_DRV_TYPE_A ; 
 int /*<<< orphan*/  SDHCI_CTRL_DRV_TYPE_C ; 
 int /*<<< orphan*/  SDHCI_CTRL_DRV_TYPE_MASK ; 
 int SDHCI_CTRL_HISPD ; 
 int /*<<< orphan*/  SDHCI_HOST_CONTROL ; 
 int /*<<< orphan*/  SDHCI_HOST_CONTROL2 ; 
 int SDHCI_POWER_330 ; 
 int /*<<< orphan*/  SDHCI_POWER_CONTROL ; 
 int SDHCI_POWER_ON ; 
 int bcm2835_mmc_readb (struct bcm2835_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_mmc_readw (struct bcm2835_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_mmc_set_clock (struct bcm2835_host*,scalar_t__) ; 
 int /*<<< orphan*/  bcm2835_mmc_writeb (struct bcm2835_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_mmc_writew (struct bcm2835_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bcm2835_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void bcm2835_mmc_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{

	struct bcm2835_host *host = mmc_priv(mmc);
	unsigned long flags;
	u8 ctrl;
	u16 clk, ctrl_2;

	pr_debug("bcm2835_mmc_set_ios: clock %d, pwr %d, bus_width %d, timing %d, vdd %d, drv_type %d\n",
		 ios->clock, ios->power_mode, ios->bus_width,
		 ios->timing, ios->signal_voltage, ios->drv_type);

	spin_lock_irqsave(&host->lock, flags);

	if (!ios->clock || ios->clock != host->clock) {
		bcm2835_mmc_set_clock(host, ios->clock);
		host->clock = ios->clock;
	}

	if (host->pwr != SDHCI_POWER_330) {
		host->pwr = SDHCI_POWER_330;
		bcm2835_mmc_writeb(host, SDHCI_POWER_330 | SDHCI_POWER_ON, SDHCI_POWER_CONTROL);
	}

	ctrl = bcm2835_mmc_readb(host, SDHCI_HOST_CONTROL);

	/* set bus width */
	ctrl &= ~SDHCI_CTRL_8BITBUS;
	if (ios->bus_width == MMC_BUS_WIDTH_4)
		ctrl |= SDHCI_CTRL_4BITBUS;
	else
		ctrl &= ~SDHCI_CTRL_4BITBUS;

	ctrl &= ~SDHCI_CTRL_HISPD; /* NO_HISPD_BIT */


	bcm2835_mmc_writeb(host, ctrl, SDHCI_HOST_CONTROL);
	/*
	 * We only need to set Driver Strength if the
	 * preset value enable is not set.
	 */
	ctrl_2 = bcm2835_mmc_readw(host, SDHCI_HOST_CONTROL2);
	ctrl_2 &= ~SDHCI_CTRL_DRV_TYPE_MASK;
	if (ios->drv_type == MMC_SET_DRIVER_TYPE_A)
		ctrl_2 |= SDHCI_CTRL_DRV_TYPE_A;
	else if (ios->drv_type == MMC_SET_DRIVER_TYPE_C)
		ctrl_2 |= SDHCI_CTRL_DRV_TYPE_C;

	bcm2835_mmc_writew(host, ctrl_2, SDHCI_HOST_CONTROL2);

	/* Reset SD Clock Enable */
	clk = bcm2835_mmc_readw(host, SDHCI_CLOCK_CONTROL);
	clk &= ~SDHCI_CLOCK_CARD_EN;
	bcm2835_mmc_writew(host, clk, SDHCI_CLOCK_CONTROL);

	/* Re-enable SD Clock */
	bcm2835_mmc_set_clock(host, host->clock);
	bcm2835_mmc_writeb(host, ctrl, SDHCI_HOST_CONTROL);

	mmiowb();

	spin_unlock_irqrestore(&host->lock, flags);
}