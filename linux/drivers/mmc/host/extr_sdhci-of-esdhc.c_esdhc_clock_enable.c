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
struct sdhci_host {int /*<<< orphan*/  mmc; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int ESDHC_CLOCK_SDCLKEN ; 
 int ESDHC_CLOCK_STABLE ; 
 int /*<<< orphan*/  ESDHC_PRSSTAT ; 
 int /*<<< orphan*/  ESDHC_SYSTEM_CONTROL ; 
 int /*<<< orphan*/  ktime_add_ms (int /*<<< orphan*/ ,int) ; 
 int ktime_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void esdhc_clock_enable(struct sdhci_host *host, bool enable)
{
	u32 val;
	ktime_t timeout;

	val = sdhci_readl(host, ESDHC_SYSTEM_CONTROL);

	if (enable)
		val |= ESDHC_CLOCK_SDCLKEN;
	else
		val &= ~ESDHC_CLOCK_SDCLKEN;

	sdhci_writel(host, val, ESDHC_SYSTEM_CONTROL);

	/* Wait max 20 ms */
	timeout = ktime_add_ms(ktime_get(), 20);
	val = ESDHC_CLOCK_STABLE;
	while  (1) {
		bool timedout = ktime_after(ktime_get(), timeout);

		if (sdhci_readl(host, ESDHC_PRSSTAT) & val)
			break;
		if (timedout) {
			pr_err("%s: Internal clock never stabilised.\n",
				mmc_hostname(host->mmc));
			break;
		}
		udelay(10);
	}
}