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
struct bcm2835_host {int overclock_50; unsigned int max_clk; unsigned int max_overclock; int max_delay; TYPE_1__* mmc; } ;
struct TYPE_2__ {unsigned int actual_clock; } ;

/* Variables and functions */
 int SDHCI_CLOCK_CARD_EN ; 
 int /*<<< orphan*/  SDHCI_CLOCK_CONTROL ; 
 int SDHCI_CLOCK_INT_EN ; 
 int SDHCI_CLOCK_INT_STABLE ; 
 int SDHCI_DIVIDER_HI_SHIFT ; 
 int SDHCI_DIVIDER_SHIFT ; 
 int SDHCI_DIV_HI_MASK ; 
 int SDHCI_DIV_MASK ; 
 int SDHCI_DIV_MASK_LEN ; 
 int SDHCI_MAX_DIV_SPEC_300 ; 
 int /*<<< orphan*/  bcm2835_mmc_dumpregs (struct bcm2835_host*) ; 
 int bcm2835_mmc_readw (struct bcm2835_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2835_mmc_writew (struct bcm2835_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mmc_hostname (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pr_warning (char*,int) ; 

void bcm2835_mmc_set_clock(struct bcm2835_host *host, unsigned int clock)
{
	int div = 0; /* Initialized for compiler warning */
	int real_div = div, clk_mul = 1;
	u16 clk = 0;
	unsigned long timeout;
	unsigned int input_clock = clock;

	if (host->overclock_50 && (clock == 50000000))
		clock = host->overclock_50 * 1000000 + 999999;

	host->mmc->actual_clock = 0;

	bcm2835_mmc_writew(host, 0, SDHCI_CLOCK_CONTROL);

	if (clock == 0)
		return;

	/* Version 3.00 divisors must be a multiple of 2. */
	if (host->max_clk <= clock)
		div = 1;
	else {
		for (div = 2; div < SDHCI_MAX_DIV_SPEC_300;
			 div += 2) {
			if ((host->max_clk / div) <= clock)
				break;
		}
	}

	real_div = div;
	div >>= 1;

	if (real_div)
		clock = (host->max_clk * clk_mul) / real_div;
	host->mmc->actual_clock = clock;

	if ((clock > input_clock) && (clock > host->max_overclock)) {
		pr_warn("%s: Overclocking to %dHz\n",
			mmc_hostname(host->mmc), clock);
		host->max_overclock = clock;
	}

	clk |= (div & SDHCI_DIV_MASK) << SDHCI_DIVIDER_SHIFT;
	clk |= ((div & SDHCI_DIV_HI_MASK) >> SDHCI_DIV_MASK_LEN)
		<< SDHCI_DIVIDER_HI_SHIFT;
	clk |= SDHCI_CLOCK_INT_EN;
	bcm2835_mmc_writew(host, clk, SDHCI_CLOCK_CONTROL);

	/* Wait max 20 ms */
	timeout = 20;
	while (!((clk = bcm2835_mmc_readw(host, SDHCI_CLOCK_CONTROL))
		& SDHCI_CLOCK_INT_STABLE)) {
		if (timeout == 0) {
			pr_err("%s: Internal clock never "
				"stabilised.\n", mmc_hostname(host->mmc));
			bcm2835_mmc_dumpregs(host);
			return;
		}
		timeout--;
		mdelay(1);
	}

	if (20-timeout > 10 && 20-timeout > host->max_delay) {
		host->max_delay = 20-timeout;
		pr_warning("Warning: MMC controller hung for %d ms\n", host->max_delay);
	}

	clk |= SDHCI_CLOCK_CARD_EN;
	bcm2835_mmc_writew(host, clk, SDHCI_CLOCK_CONTROL);
}