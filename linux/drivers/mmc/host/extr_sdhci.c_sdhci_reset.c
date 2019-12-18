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
struct sdhci_host {int quirks2; int /*<<< orphan*/  mmc; scalar_t__ clock; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int SDHCI_QUIRK2_CARD_ON_NEEDS_BUS_ON ; 
 int SDHCI_RESET_ALL ; 
 int /*<<< orphan*/  SDHCI_SOFTWARE_RESET ; 
 int /*<<< orphan*/  ktime_add_ms (int /*<<< orphan*/ ,int) ; 
 int ktime_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdhci_dumpregs (struct sdhci_host*) ; 
 int sdhci_readb (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_runtime_pm_bus_off (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_writeb (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

void sdhci_reset(struct sdhci_host *host, u8 mask)
{
	ktime_t timeout;

	sdhci_writeb(host, mask, SDHCI_SOFTWARE_RESET);

	if (mask & SDHCI_RESET_ALL) {
		host->clock = 0;
		/* Reset-all turns off SD Bus Power */
		if (host->quirks2 & SDHCI_QUIRK2_CARD_ON_NEEDS_BUS_ON)
			sdhci_runtime_pm_bus_off(host);
	}

	/* Wait max 100 ms */
	timeout = ktime_add_ms(ktime_get(), 100);

	/* hw clears the bit when it's done */
	while (1) {
		bool timedout = ktime_after(ktime_get(), timeout);

		if (!(sdhci_readb(host, SDHCI_SOFTWARE_RESET) & mask))
			break;
		if (timedout) {
			pr_err("%s: Reset 0x%x never completed.\n",
				mmc_hostname(host->mmc), (int)mask);
			sdhci_dumpregs(host);
			return;
		}
		udelay(10);
	}
}