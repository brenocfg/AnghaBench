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
typedef  int u8 ;
typedef  int u32 ;
struct moxart_host {int sysclk; int rate; int /*<<< orphan*/  lock; scalar_t__ base; } ;
struct mmc_ios {int clock; scalar_t__ power_mode; scalar_t__ vdd; int bus_width; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int BUS_WIDTH_1 ; 
 int BUS_WIDTH_4 ; 
 int BUS_WIDTH_8 ; 
 int CLK_DIV_MASK ; 
 int CLK_HISPD ; 
 int CLK_SD ; 
 scalar_t__ MIN_POWER ; 
#define  MMC_BUS_WIDTH_4 129 
#define  MMC_BUS_WIDTH_8 128 
 scalar_t__ MMC_POWER_OFF ; 
 scalar_t__ REG_BUS_WIDTH ; 
 scalar_t__ REG_CLOCK_CONTROL ; 
 scalar_t__ REG_POWER_CONTROL ; 
 int SD_POWER_ON ; 
 struct moxart_host* mmc_priv (struct mmc_host*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void moxart_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct moxart_host *host = mmc_priv(mmc);
	unsigned long flags;
	u8 power, div;
	u32 ctrl;

	spin_lock_irqsave(&host->lock, flags);

	if (ios->clock) {
		for (div = 0; div < CLK_DIV_MASK; ++div) {
			if (ios->clock >= host->sysclk / (2 * (div + 1)))
				break;
		}
		ctrl = CLK_SD | div;
		host->rate = host->sysclk / (2 * (div + 1));
		if (host->rate > host->sysclk)
			ctrl |= CLK_HISPD;
		writel(ctrl, host->base + REG_CLOCK_CONTROL);
	}

	if (ios->power_mode == MMC_POWER_OFF) {
		writel(readl(host->base + REG_POWER_CONTROL) & ~SD_POWER_ON,
		       host->base + REG_POWER_CONTROL);
	} else {
		if (ios->vdd < MIN_POWER)
			power = 0;
		else
			power = ios->vdd - MIN_POWER;

		writel(SD_POWER_ON | (u32) power,
		       host->base + REG_POWER_CONTROL);
	}

	switch (ios->bus_width) {
	case MMC_BUS_WIDTH_4:
		writel(BUS_WIDTH_4, host->base + REG_BUS_WIDTH);
		break;
	case MMC_BUS_WIDTH_8:
		writel(BUS_WIDTH_8, host->base + REG_BUS_WIDTH);
		break;
	default:
		writel(BUS_WIDTH_1, host->base + REG_BUS_WIDTH);
		break;
	}

	spin_unlock_irqrestore(&host->lock, flags);
}