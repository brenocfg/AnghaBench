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
struct pxamci_host {int /*<<< orphan*/  mmc; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ MMC_STAT ; 
 scalar_t__ MMC_STRPCL ; 
 int STAT_CLK_EN ; 
 int /*<<< orphan*/  STOP_CLOCK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void pxamci_stop_clock(struct pxamci_host *host)
{
	if (readl(host->base + MMC_STAT) & STAT_CLK_EN) {
		unsigned long timeout = 10000;
		unsigned int v;

		writel(STOP_CLOCK, host->base + MMC_STRPCL);

		do {
			v = readl(host->base + MMC_STAT);
			if (!(v & STAT_CLK_EN))
				break;
			udelay(1);
		} while (timeout--);

		if (v & STAT_CLK_EN)
			dev_err(mmc_dev(host->mmc), "unable to stop clock\n");
	}
}