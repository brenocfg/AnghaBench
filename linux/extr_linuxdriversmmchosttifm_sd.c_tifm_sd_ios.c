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
struct tifm_sd {int clk_freq; unsigned int clk_div; int open_drain; struct tifm_dev* dev; } ;
struct tifm_dev {int /*<<< orphan*/  lock; scalar_t__ addr; int /*<<< orphan*/  dev; } ;
struct mmc_ios {int clock; int /*<<< orphan*/  bus_mode; int /*<<< orphan*/  bus_width; int /*<<< orphan*/  power_mode; int /*<<< orphan*/  chip_select; int /*<<< orphan*/  vdd; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_BUSMODE_OPENDRAIN ; 
 int /*<<< orphan*/  MMC_BUS_WIDTH_4 ; 
 scalar_t__ SOCK_CONTROL ; 
 scalar_t__ SOCK_MMCSD_CONFIG ; 
 int TIFM_CTRL_FAST_CLK ; 
 int TIFM_MMCSD_4BBUS ; 
 int TIFM_MMCSD_CLKMASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tifm_sd* mmc_priv (struct mmc_host*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void tifm_sd_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct tifm_sd *host = mmc_priv(mmc);
	struct tifm_dev *sock = host->dev;
	unsigned int clk_div1, clk_div2;
	unsigned long flags;

	spin_lock_irqsave(&sock->lock, flags);

	dev_dbg(&sock->dev, "ios: clock = %u, vdd = %x, bus_mode = %x, "
		"chip_select = %x, power_mode = %x, bus_width = %x\n",
		ios->clock, ios->vdd, ios->bus_mode, ios->chip_select,
		ios->power_mode, ios->bus_width);

	if (ios->bus_width == MMC_BUS_WIDTH_4) {
		writel(TIFM_MMCSD_4BBUS | readl(sock->addr + SOCK_MMCSD_CONFIG),
		       sock->addr + SOCK_MMCSD_CONFIG);
	} else {
		writel((~TIFM_MMCSD_4BBUS)
		       & readl(sock->addr + SOCK_MMCSD_CONFIG),
		       sock->addr + SOCK_MMCSD_CONFIG);
	}

	if (ios->clock) {
		clk_div1 = 20000000 / ios->clock;
		if (!clk_div1)
			clk_div1 = 1;

		clk_div2 = 24000000 / ios->clock;
		if (!clk_div2)
			clk_div2 = 1;

		if ((20000000 / clk_div1) > ios->clock)
			clk_div1++;
		if ((24000000 / clk_div2) > ios->clock)
			clk_div2++;
		if ((20000000 / clk_div1) > (24000000 / clk_div2)) {
			host->clk_freq = 20000000;
			host->clk_div = clk_div1;
			writel((~TIFM_CTRL_FAST_CLK)
			       & readl(sock->addr + SOCK_CONTROL),
			       sock->addr + SOCK_CONTROL);
		} else {
			host->clk_freq = 24000000;
			host->clk_div = clk_div2;
			writel(TIFM_CTRL_FAST_CLK
			       | readl(sock->addr + SOCK_CONTROL),
			       sock->addr + SOCK_CONTROL);
		}
	} else {
		host->clk_div = 0;
	}
	host->clk_div &= TIFM_MMCSD_CLKMASK;
	writel(host->clk_div
	       | ((~TIFM_MMCSD_CLKMASK)
		  & readl(sock->addr + SOCK_MMCSD_CONFIG)),
	       sock->addr + SOCK_MMCSD_CONFIG);

	host->open_drain = (ios->bus_mode == MMC_BUSMODE_OPENDRAIN);

	/* chip_select : maybe later */
	//vdd
	//power is set before probe / after remove

	spin_unlock_irqrestore(&sock->lock, flags);
}