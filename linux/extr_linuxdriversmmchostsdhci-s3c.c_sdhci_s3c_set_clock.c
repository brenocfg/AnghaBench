#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sdhci_s3c {int cur_clk; int /*<<< orphan*/ * clk_rates; struct clk** clk_bus; TYPE_2__* pdev; } ;
struct sdhci_host {scalar_t__ ioaddr; int /*<<< orphan*/  max_clk; TYPE_1__* mmc; } ;
struct clk {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {scalar_t__ actual_clock; } ;

/* Variables and functions */
 int MAX_BUS_CLK ; 
 scalar_t__ S3C64XX_SDHCI_CONTROL4 ; 
 int S3C64XX_SDHCI_CONTROL4_DRIVE_9mA ; 
 int S3C64XX_SDHCI_CTRL2_ENCMDCNFMSK ; 
 int S3C64XX_SDHCI_CTRL2_ENSTAASYNCCLR ; 
 scalar_t__ S3C_SDHCI_CONTROL2 ; 
 scalar_t__ S3C_SDHCI_CONTROL3 ; 
 int S3C_SDHCI_CTRL2_DFCNT_NONE ; 
 int S3C_SDHCI_CTRL2_ENCLKOUTHOLD ; 
 int S3C_SDHCI_CTRL2_ENFBCLKRX ; 
 int S3C_SDHCI_CTRL2_SELBASECLK_MASK ; 
 int S3C_SDHCI_CTRL2_SELBASECLK_SHIFT ; 
 int S3C_SDHCI_CTRL3_FCSEL0 ; 
 int S3C_SDHCI_CTRL3_FCSEL1 ; 
 int S3C_SDHCI_CTRL3_FCSEL2 ; 
 int S3C_SDHCI_CTRL3_FCSEL3 ; 
 scalar_t__ SDHCI_CLOCK_CONTROL ; 
 unsigned int UINT_MAX ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct clk*) ; 
 int /*<<< orphan*/  clk_prepare_enable (struct clk*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,unsigned int,unsigned int) ; 
 int readl (scalar_t__) ; 
 unsigned int sdhci_s3c_consider_clock (struct sdhci_s3c*,int,unsigned int) ; 
 int /*<<< orphan*/  sdhci_set_clock (struct sdhci_host*,unsigned int) ; 
 struct sdhci_s3c* to_s3c (struct sdhci_host*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sdhci_s3c_set_clock(struct sdhci_host *host, unsigned int clock)
{
	struct sdhci_s3c *ourhost = to_s3c(host);
	unsigned int best = UINT_MAX;
	unsigned int delta;
	int best_src = 0;
	int src;
	u32 ctrl;

	host->mmc->actual_clock = 0;

	/* don't bother if the clock is going off. */
	if (clock == 0) {
		sdhci_set_clock(host, clock);
		return;
	}

	for (src = 0; src < MAX_BUS_CLK; src++) {
		delta = sdhci_s3c_consider_clock(ourhost, src, clock);
		if (delta < best) {
			best = delta;
			best_src = src;
		}
	}

	dev_dbg(&ourhost->pdev->dev,
		"selected source %d, clock %d, delta %d\n",
		 best_src, clock, best);

	/* select the new clock source */
	if (ourhost->cur_clk != best_src) {
		struct clk *clk = ourhost->clk_bus[best_src];

		clk_prepare_enable(clk);
		if (ourhost->cur_clk >= 0)
			clk_disable_unprepare(
					ourhost->clk_bus[ourhost->cur_clk]);

		ourhost->cur_clk = best_src;
		host->max_clk = ourhost->clk_rates[best_src];
	}

	/* turn clock off to card before changing clock source */
	writew(0, host->ioaddr + SDHCI_CLOCK_CONTROL);

	ctrl = readl(host->ioaddr + S3C_SDHCI_CONTROL2);
	ctrl &= ~S3C_SDHCI_CTRL2_SELBASECLK_MASK;
	ctrl |= best_src << S3C_SDHCI_CTRL2_SELBASECLK_SHIFT;
	writel(ctrl, host->ioaddr + S3C_SDHCI_CONTROL2);

	/* reprogram default hardware configuration */
	writel(S3C64XX_SDHCI_CONTROL4_DRIVE_9mA,
		host->ioaddr + S3C64XX_SDHCI_CONTROL4);

	ctrl = readl(host->ioaddr + S3C_SDHCI_CONTROL2);
	ctrl |= (S3C64XX_SDHCI_CTRL2_ENSTAASYNCCLR |
		  S3C64XX_SDHCI_CTRL2_ENCMDCNFMSK |
		  S3C_SDHCI_CTRL2_ENFBCLKRX |
		  S3C_SDHCI_CTRL2_DFCNT_NONE |
		  S3C_SDHCI_CTRL2_ENCLKOUTHOLD);
	writel(ctrl, host->ioaddr + S3C_SDHCI_CONTROL2);

	/* reconfigure the controller for new clock rate */
	ctrl = (S3C_SDHCI_CTRL3_FCSEL1 | S3C_SDHCI_CTRL3_FCSEL0);
	if (clock < 25 * 1000000)
		ctrl |= (S3C_SDHCI_CTRL3_FCSEL3 | S3C_SDHCI_CTRL3_FCSEL2);
	writel(ctrl, host->ioaddr + S3C_SDHCI_CONTROL3);

	sdhci_set_clock(host, clock);
}