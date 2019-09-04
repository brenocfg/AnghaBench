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
typedef  unsigned int u32 ;
struct mmc_ios {scalar_t__ bus_mode; int /*<<< orphan*/  clock; } ;
struct mmc_host {int dummy; } ;
struct mmc_davinci_host {int ns_in_one_cycle; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ DAVINCI_MMCCLK ; 
 unsigned int MMCCLK_CLKEN ; 
 unsigned int MMCCLK_CLKRT_MASK ; 
 int MMCSD_INIT_CLOCK ; 
 scalar_t__ MMC_BUSMODE_OPENDRAIN ; 
 unsigned int calculate_freq_for_card (struct mmc_davinci_host*,int /*<<< orphan*/ ) ; 
 struct mmc_davinci_host* mmc_priv (struct mmc_host*) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void calculate_clk_divider(struct mmc_host *mmc, struct mmc_ios *ios)
{
	unsigned int open_drain_freq = 0, mmc_pclk = 0;
	unsigned int mmc_push_pull_freq = 0;
	struct mmc_davinci_host *host = mmc_priv(mmc);

	if (ios->bus_mode == MMC_BUSMODE_OPENDRAIN) {
		u32 temp;

		/* Ignoring the init clock value passed for fixing the inter
		 * operability with different cards.
		 */
		open_drain_freq = ((unsigned int)mmc_pclk
				/ (2 * MMCSD_INIT_CLOCK)) - 1;

		if (open_drain_freq > 0xFF)
			open_drain_freq = 0xFF;

		temp = readl(host->base + DAVINCI_MMCCLK) & ~MMCCLK_CLKRT_MASK;
		temp |= open_drain_freq;
		writel(temp, host->base + DAVINCI_MMCCLK);

		/* Convert ns to clock cycles */
		host->ns_in_one_cycle = (1000000) / (MMCSD_INIT_CLOCK/1000);
	} else {
		u32 temp;
		mmc_push_pull_freq = calculate_freq_for_card(host, ios->clock);

		if (mmc_push_pull_freq > 0xFF)
			mmc_push_pull_freq = 0xFF;

		temp = readl(host->base + DAVINCI_MMCCLK) & ~MMCCLK_CLKEN;
		writel(temp, host->base + DAVINCI_MMCCLK);

		udelay(10);

		temp = readl(host->base + DAVINCI_MMCCLK) & ~MMCCLK_CLKRT_MASK;
		temp |= mmc_push_pull_freq;
		writel(temp, host->base + DAVINCI_MMCCLK);

		writel(temp | MMCCLK_CLKEN, host->base + DAVINCI_MMCCLK);

		udelay(10);
	}
}