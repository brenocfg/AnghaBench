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
struct mmc_host {unsigned int actual_clock; int caps; } ;
struct bcm2835_host {int cdiv; unsigned int max_clk; int ns_per_fifo_word; scalar_t__ ioaddr; } ;

/* Variables and functions */
 int MMC_CAP_4_BIT_DATA ; 
 scalar_t__ SDCDIV ; 
 int SDCDIV_MAX_CDIV ; 
 scalar_t__ SDTOUT ; 
 struct mmc_host* mmc_from_priv (struct bcm2835_host*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void bcm2835_set_clock(struct bcm2835_host *host, unsigned int clock)
{
	struct mmc_host *mmc = mmc_from_priv(host);
	int div;

	/* The SDCDIV register has 11 bits, and holds (div - 2).  But
	 * in data mode the max is 50MHz wihout a minimum, and only
	 * the bottom 3 bits are used. Since the switch over is
	 * automatic (unless we have marked the card as slow...),
	 * chosen values have to make sense in both modes.  Ident mode
	 * must be 100-400KHz, so can range check the requested
	 * clock. CMD15 must be used to return to data mode, so this
	 * can be monitored.
	 *
	 * clock 250MHz -> 0->125MHz, 1->83.3MHz, 2->62.5MHz, 3->50.0MHz
	 *                 4->41.7MHz, 5->35.7MHz, 6->31.3MHz, 7->27.8MHz
	 *
	 *		 623->400KHz/27.8MHz
	 *		 reset value (507)->491159/50MHz
	 *
	 * BUT, the 3-bit clock divisor in data mode is too small if
	 * the core clock is higher than 250MHz, so instead use the
	 * SLOW_CARD configuration bit to force the use of the ident
	 * clock divisor at all times.
	 */

	if (clock < 100000) {
		/* Can't stop the clock, but make it as slow as possible
		 * to show willing
		 */
		host->cdiv = SDCDIV_MAX_CDIV;
		writel(host->cdiv, host->ioaddr + SDCDIV);
		return;
	}

	div = host->max_clk / clock;
	if (div < 2)
		div = 2;
	if ((host->max_clk / div) > clock)
		div++;
	div -= 2;

	if (div > SDCDIV_MAX_CDIV)
		div = SDCDIV_MAX_CDIV;

	clock = host->max_clk / (div + 2);
	mmc->actual_clock = clock;

	/* Calibrate some delays */

	host->ns_per_fifo_word = (1000000000 / clock) *
		((mmc->caps & MMC_CAP_4_BIT_DATA) ? 8 : 32);

	host->cdiv = div;
	writel(host->cdiv, host->ioaddr + SDCDIV);

	/* Set the timeout to 500ms */
	writel(mmc->actual_clock / 2, host->ioaddr + SDTOUT);
}