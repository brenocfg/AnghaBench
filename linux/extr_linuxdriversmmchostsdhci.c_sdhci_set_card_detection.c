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
struct sdhci_host {int quirks; int ier; int /*<<< orphan*/  mmc; } ;

/* Variables and functions */
 int SDHCI_CARD_PRESENT ; 
 int SDHCI_INT_CARD_INSERT ; 
 int SDHCI_INT_CARD_REMOVE ; 
 int /*<<< orphan*/  SDHCI_INT_ENABLE ; 
 int /*<<< orphan*/  SDHCI_PRESENT_STATE ; 
 int SDHCI_QUIRK_BROKEN_CARD_DETECTION ; 
 int /*<<< orphan*/  SDHCI_SIGNAL_ENABLE ; 
 int /*<<< orphan*/  mmc_card_is_removable (int /*<<< orphan*/ ) ; 
 int sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdhci_set_card_detection(struct sdhci_host *host, bool enable)
{
	u32 present;

	if ((host->quirks & SDHCI_QUIRK_BROKEN_CARD_DETECTION) ||
	    !mmc_card_is_removable(host->mmc))
		return;

	if (enable) {
		present = sdhci_readl(host, SDHCI_PRESENT_STATE) &
				      SDHCI_CARD_PRESENT;

		host->ier |= present ? SDHCI_INT_CARD_REMOVE :
				       SDHCI_INT_CARD_INSERT;
	} else {
		host->ier &= ~(SDHCI_INT_CARD_REMOVE | SDHCI_INT_CARD_INSERT);
	}

	sdhci_writel(host, host->ier, SDHCI_INT_ENABLE);
	sdhci_writel(host, host->ier, SDHCI_SIGNAL_ENABLE);
}