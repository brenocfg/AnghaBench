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
 int SDHCI_CARD_PRESENT ; 
 int SDHCI_CARD_PRES_SHIFT ; 
 int SDHCI_CD_LVL ; 
 int SDHCI_CD_LVL_SHIFT ; 
 int /*<<< orphan*/  SDHCI_PRESENT_STATE ; 
 int /*<<< orphan*/  ktime_add_ms (int /*<<< orphan*/ ,int) ; 
 int ktime_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_dumpregs (struct sdhci_host*) ; 
 int sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void sdhci_o2_wait_card_detect_stable(struct sdhci_host *host)
{
	ktime_t timeout;
	u32 scratch32;

	/* Wait max 50 ms */
	timeout = ktime_add_ms(ktime_get(), 50);
	while (1) {
		bool timedout = ktime_after(ktime_get(), timeout);

		scratch32 = sdhci_readl(host, SDHCI_PRESENT_STATE);
		if ((scratch32 & SDHCI_CARD_PRESENT) >> SDHCI_CARD_PRES_SHIFT
		    == (scratch32 & SDHCI_CD_LVL) >> SDHCI_CD_LVL_SHIFT)
			break;

		if (timedout) {
			pr_err("%s: Card Detect debounce never finished.\n",
			       mmc_hostname(host->mmc));
			sdhci_dumpregs(host);
			return;
		}
		udelay(10);
	}
}