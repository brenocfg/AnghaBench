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
typedef  int u16 ;
struct sdhci_host {int /*<<< orphan*/  mmc; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  O2_PLL_DLL_WDT_CONTROL1 ; 
 int /*<<< orphan*/  O2_PLL_FORCE_ACTIVE ; 
 int O2_PLL_LOCK_STATUS ; 
 int /*<<< orphan*/  O2_PLL_SOFT_RESET ; 
 int /*<<< orphan*/  ktime_add_ms (int /*<<< orphan*/ ,int) ; 
 int ktime_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_dumpregs (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_o2_wait_card_detect_stable (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int sdhci_readw (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void sdhci_o2_enable_internal_clock(struct sdhci_host *host)
{
	ktime_t timeout;
	u16 scratch;
	u32 scratch32;

	/* PLL software reset */
	scratch32 = sdhci_readl(host, O2_PLL_DLL_WDT_CONTROL1);
	scratch32 |= O2_PLL_SOFT_RESET;
	sdhci_writel(host, scratch32, O2_PLL_DLL_WDT_CONTROL1);
	udelay(1);
	scratch32 &= ~(O2_PLL_SOFT_RESET);
	sdhci_writel(host, scratch32, O2_PLL_DLL_WDT_CONTROL1);

	/* PLL force active */
	scratch32 |= O2_PLL_FORCE_ACTIVE;
	sdhci_writel(host, scratch32, O2_PLL_DLL_WDT_CONTROL1);

	/* Wait max 20 ms */
	timeout = ktime_add_ms(ktime_get(), 20);
	while (1) {
		bool timedout = ktime_after(ktime_get(), timeout);

		scratch = sdhci_readw(host, O2_PLL_DLL_WDT_CONTROL1);
		if (scratch & O2_PLL_LOCK_STATUS)
			break;
		if (timedout) {
			pr_err("%s: Internal clock never stabilised.\n",
			       mmc_hostname(host->mmc));
			sdhci_dumpregs(host);
			goto out;
		}
		udelay(10);
	}

	/* Wait for card detect finish */
	udelay(1);
	sdhci_o2_wait_card_detect_stable(host);

out:
	/* Cancel PLL force active */
	scratch32 = sdhci_readl(host, O2_PLL_DLL_WDT_CONTROL1);
	scratch32 &= ~O2_PLL_FORCE_ACTIVE;
	sdhci_writel(host, scratch32, O2_PLL_DLL_WDT_CONTROL1);
}