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
struct sdhci_host {int clock; scalar_t__ ioaddr; int /*<<< orphan*/  mmc; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void sdhci_iproc_writel(struct sdhci_host *host, u32 val, int reg)
{
	pr_debug("%s: writel [0x%02x] 0x%08x\n",
		 mmc_hostname(host->mmc), reg, val);

	writel(val, host->ioaddr + reg);

	if (host->clock <= 400000) {
		/* Round up to micro-second four SD clock delay */
		if (host->clock)
			udelay((4 * 1000000 + host->clock - 1) / host->clock);
		else
			udelay(10);
	}
}