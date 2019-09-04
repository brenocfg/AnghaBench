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
struct sdhci_host {TYPE_1__* mmc; } ;
struct TYPE_2__ {scalar_t__ actual_clock; } ;

/* Variables and functions */
 int SDHCI_CLOCK_CARD_EN ; 
 int /*<<< orphan*/  SDHCI_CLOCK_CONTROL ; 
 int SDHCI_CLOCK_INT_EN ; 
 int SDHCI_CLOCK_INT_STABLE ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mmc_hostname (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int sdhci_calc_clk (struct sdhci_host*,unsigned int,scalar_t__*) ; 
 int sdhci_readw (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writew (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdhci_at91_set_clock(struct sdhci_host *host, unsigned int clock)
{
	u16 clk;
	unsigned long timeout;

	host->mmc->actual_clock = 0;

	/*
	 * There is no requirement to disable the internal clock before
	 * changing the SD clock configuration. Moreover, disabling the
	 * internal clock, changing the configuration and re-enabling the
	 * internal clock causes some bugs. It can prevent to get the internal
	 * clock stable flag ready and an unexpected switch to the base clock
	 * when using presets.
	 */
	clk = sdhci_readw(host, SDHCI_CLOCK_CONTROL);
	clk &= SDHCI_CLOCK_INT_EN;
	sdhci_writew(host, clk, SDHCI_CLOCK_CONTROL);

	if (clock == 0)
		return;

	clk = sdhci_calc_clk(host, clock, &host->mmc->actual_clock);

	clk |= SDHCI_CLOCK_INT_EN;
	sdhci_writew(host, clk, SDHCI_CLOCK_CONTROL);

	/* Wait max 20 ms */
	timeout = 20;
	while (!((clk = sdhci_readw(host, SDHCI_CLOCK_CONTROL))
		& SDHCI_CLOCK_INT_STABLE)) {
		if (timeout == 0) {
			pr_err("%s: Internal clock never stabilised.\n",
			       mmc_hostname(host->mmc));
			return;
		}
		timeout--;
		mdelay(1);
	}

	clk |= SDHCI_CLOCK_CARD_EN;
	sdhci_writew(host, clk, SDHCI_CLOCK_CONTROL);
}