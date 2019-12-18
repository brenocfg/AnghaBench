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
typedef  int u32 ;
struct usdhi6_host {unsigned long imclk; unsigned long rate; int /*<<< orphan*/  mmc; } ;
struct mmc_ios {unsigned long clock; scalar_t__ timing; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int,unsigned long) ; 
 scalar_t__ MMC_TIMING_UHS_DDR50 ; 
 int /*<<< orphan*/  USDHI6_SD_CLK_CTRL ; 
 int USDHI6_SD_CLK_CTRL_DIV_MASK ; 
 int USDHI6_SD_CLK_CTRL_SCLKEN ; 
 int /*<<< orphan*/  USDHI6_SD_INFO2 ; 
 int USDHI6_SD_INFO2_SCLKDIVEN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long,int,unsigned long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 unsigned long roundup_pow_of_two (int /*<<< orphan*/ ) ; 
 int usdhi6_read (struct usdhi6_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usdhi6_write (struct usdhi6_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void usdhi6_clk_set(struct usdhi6_host *host, struct mmc_ios *ios)
{
	unsigned long rate = ios->clock;
	u32 val;
	unsigned int i;

	for (i = 1000; i; i--) {
		if (usdhi6_read(host, USDHI6_SD_INFO2) & USDHI6_SD_INFO2_SCLKDIVEN)
			break;
		usleep_range(10, 100);
	}

	if (!i) {
		dev_err(mmc_dev(host->mmc), "SD bus busy, clock set aborted\n");
		return;
	}

	val = usdhi6_read(host, USDHI6_SD_CLK_CTRL) & ~USDHI6_SD_CLK_CTRL_DIV_MASK;

	if (rate) {
		unsigned long new_rate;

		if (host->imclk <= rate) {
			if (ios->timing != MMC_TIMING_UHS_DDR50) {
				/* Cannot have 1-to-1 clock in DDR mode */
				new_rate = host->imclk;
				val |= 0xff;
			} else {
				new_rate = host->imclk / 2;
			}
		} else {
			unsigned long div =
				roundup_pow_of_two(DIV_ROUND_UP(host->imclk, rate));
			val |= div >> 2;
			new_rate = host->imclk / div;
		}

		if (host->rate == new_rate)
			return;

		host->rate = new_rate;

		dev_dbg(mmc_dev(host->mmc), "target %lu, div %u, set %lu\n",
			rate, (val & 0xff) << 2, new_rate);
	}

	/*
	 * if old or new rate is equal to input rate, have to switch the clock
	 * off before changing and on after
	 */
	if (host->imclk == rate || host->imclk == host->rate || !rate)
		usdhi6_write(host, USDHI6_SD_CLK_CTRL,
			     val & ~USDHI6_SD_CLK_CTRL_SCLKEN);

	if (!rate) {
		host->rate = 0;
		return;
	}

	usdhi6_write(host, USDHI6_SD_CLK_CTRL, val);

	if (host->imclk == rate || host->imclk == host->rate ||
	    !(val & USDHI6_SD_CLK_CTRL_SCLKEN))
		usdhi6_write(host, USDHI6_SD_CLK_CTRL,
			     val | USDHI6_SD_CLK_CTRL_SCLKEN);
}