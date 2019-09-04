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
typedef  int u16 ;
struct sdhci_host {int max_clk; TYPE_1__* mmc; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ actual_clock; } ;

/* Variables and functions */
 int SDHCI_CLOCK_CARD_EN ; 
 int /*<<< orphan*/  SDHCI_CLOCK_CONTROL ; 
 int SDHCI_CLOCK_INT_EN ; 
 int SDHCI_CLOCK_INT_STABLE ; 
 int SDHCI_DIVIDER_SHIFT ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned int,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct device* mmc_dev (TYPE_1__*) ; 
 int sdhci_readw (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writew (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdhci_cns3xxx_set_clock(struct sdhci_host *host, unsigned int clock)
{
	struct device *dev = mmc_dev(host->mmc);
	int div = 1;
	u16 clk;
	unsigned long timeout;

	host->mmc->actual_clock = 0;

	sdhci_writew(host, 0, SDHCI_CLOCK_CONTROL);

	if (clock == 0)
		return;

	while (host->max_clk / div > clock) {
		/*
		 * On CNS3xxx divider grows linearly up to 4, and then
		 * exponentially up to 256.
		 */
		if (div < 4)
			div += 1;
		else if (div < 256)
			div *= 2;
		else
			break;
	}

	dev_dbg(dev, "desired SD clock: %d, actual: %d\n",
		clock, host->max_clk / div);

	/* Divide by 3 is special. */
	if (div != 3)
		div >>= 1;

	clk = div << SDHCI_DIVIDER_SHIFT;
	clk |= SDHCI_CLOCK_INT_EN;
	sdhci_writew(host, clk, SDHCI_CLOCK_CONTROL);

	timeout = 20;
	while (!((clk = sdhci_readw(host, SDHCI_CLOCK_CONTROL))
			& SDHCI_CLOCK_INT_STABLE)) {
		if (timeout == 0) {
			dev_warn(dev, "clock is unstable");
			break;
		}
		timeout--;
		mdelay(1);
	}

	clk |= SDHCI_CLOCK_CARD_EN;
	sdhci_writew(host, clk, SDHCI_CLOCK_CONTROL);
}