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
typedef  int u16 ;
struct sdhci_host {scalar_t__ version; int /*<<< orphan*/  mmc; scalar_t__ v4_mode; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int SDHCI_CLOCK_CARD_EN ; 
 int /*<<< orphan*/  SDHCI_CLOCK_CONTROL ; 
 int SDHCI_CLOCK_INT_EN ; 
 int SDHCI_CLOCK_INT_STABLE ; 
 int SDHCI_CLOCK_PLL_EN ; 
 scalar_t__ SDHCI_SPEC_410 ; 
 int /*<<< orphan*/  ktime_add_ms (int /*<<< orphan*/ ,int) ; 
 int ktime_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_dumpregs (struct sdhci_host*) ; 
 int sdhci_readw (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writew (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

void sdhci_enable_clk(struct sdhci_host *host, u16 clk)
{
	ktime_t timeout;

	clk |= SDHCI_CLOCK_INT_EN;
	sdhci_writew(host, clk, SDHCI_CLOCK_CONTROL);

	/* Wait max 150 ms */
	timeout = ktime_add_ms(ktime_get(), 150);
	while (1) {
		bool timedout = ktime_after(ktime_get(), timeout);

		clk = sdhci_readw(host, SDHCI_CLOCK_CONTROL);
		if (clk & SDHCI_CLOCK_INT_STABLE)
			break;
		if (timedout) {
			pr_err("%s: Internal clock never stabilised.\n",
			       mmc_hostname(host->mmc));
			sdhci_dumpregs(host);
			return;
		}
		udelay(10);
	}

	if (host->version >= SDHCI_SPEC_410 && host->v4_mode) {
		clk |= SDHCI_CLOCK_PLL_EN;
		clk &= ~SDHCI_CLOCK_INT_STABLE;
		sdhci_writew(host, clk, SDHCI_CLOCK_CONTROL);

		/* Wait max 150 ms */
		timeout = ktime_add_ms(ktime_get(), 150);
		while (1) {
			bool timedout = ktime_after(ktime_get(), timeout);

			clk = sdhci_readw(host, SDHCI_CLOCK_CONTROL);
			if (clk & SDHCI_CLOCK_INT_STABLE)
				break;
			if (timedout) {
				pr_err("%s: PLL clock never stabilised.\n",
				       mmc_hostname(host->mmc));
				sdhci_dumpregs(host);
				return;
			}
			udelay(10);
		}
	}

	clk |= SDHCI_CLOCK_CARD_EN;
	sdhci_writew(host, clk, SDHCI_CLOCK_CONTROL);
}