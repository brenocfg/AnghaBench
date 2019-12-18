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
typedef  int /*<<< orphan*/  u32 ;
struct mmc_host {int actual_clock; } ;
struct meson_host {int ddr; unsigned long req_rate; int /*<<< orphan*/  dev; int /*<<< orphan*/  mmc_clk; scalar_t__ regs; struct mmc_host* mmc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_DDR ; 
 int /*<<< orphan*/  CFG_STOP_CLOCK ; 
 scalar_t__ SD_EMMC_CFG ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned long,int) ; 
 int /*<<< orphan*/  meson_mmc_clk_gate (struct meson_host*) ; 
 int /*<<< orphan*/  meson_mmc_clk_ungate (struct meson_host*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int meson_mmc_clk_set(struct meson_host *host, unsigned long rate,
			     bool ddr)
{
	struct mmc_host *mmc = host->mmc;
	int ret;
	u32 cfg;

	/* Same request - bail-out */
	if (host->ddr == ddr && host->req_rate == rate)
		return 0;

	/* stop clock */
	meson_mmc_clk_gate(host);
	host->req_rate = 0;
	mmc->actual_clock = 0;

	/* return with clock being stopped */
	if (!rate)
		return 0;

	/* Stop the clock during rate change to avoid glitches */
	cfg = readl(host->regs + SD_EMMC_CFG);
	cfg |= CFG_STOP_CLOCK;
	writel(cfg, host->regs + SD_EMMC_CFG);

	if (ddr) {
		/* DDR modes require higher module clock */
		rate <<= 1;
		cfg |= CFG_DDR;
	} else {
		cfg &= ~CFG_DDR;
	}
	writel(cfg, host->regs + SD_EMMC_CFG);
	host->ddr = ddr;

	ret = clk_set_rate(host->mmc_clk, rate);
	if (ret) {
		dev_err(host->dev, "Unable to set cfg_div_clk to %lu. ret=%d\n",
			rate, ret);
		return ret;
	}

	host->req_rate = rate;
	mmc->actual_clock = clk_get_rate(host->mmc_clk);

	/* We should report the real output frequency of the controller */
	if (ddr) {
		host->req_rate >>= 1;
		mmc->actual_clock >>= 1;
	}

	dev_dbg(host->dev, "clk rate: %u Hz\n", mmc->actual_clock);
	if (rate != mmc->actual_clock)
		dev_dbg(host->dev, "requested rate was %lu\n", rate);

	/* (re)start clock */
	meson_mmc_clk_ungate(host);

	return 0;
}