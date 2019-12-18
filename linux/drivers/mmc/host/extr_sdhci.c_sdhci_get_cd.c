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
struct sdhci_host {int flags; int quirks; int /*<<< orphan*/  mmc; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int SDHCI_CARD_PRESENT ; 
 int SDHCI_DEVICE_DEAD ; 
 int /*<<< orphan*/  SDHCI_PRESENT_STATE ; 
 int SDHCI_QUIRK_BROKEN_CARD_DETECTION ; 
 int /*<<< orphan*/  mmc_card_is_removable (int /*<<< orphan*/ ) ; 
 int mmc_gpio_get_cd (struct mmc_host*) ; 
 struct sdhci_host* mmc_priv (struct mmc_host*) ; 
 int sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sdhci_get_cd(struct mmc_host *mmc)
{
	struct sdhci_host *host = mmc_priv(mmc);
	int gpio_cd = mmc_gpio_get_cd(mmc);

	if (host->flags & SDHCI_DEVICE_DEAD)
		return 0;

	/* If nonremovable, assume that the card is always present. */
	if (!mmc_card_is_removable(host->mmc))
		return 1;

	/*
	 * Try slot gpio detect, if defined it take precedence
	 * over build in controller functionality
	 */
	if (gpio_cd >= 0)
		return !!gpio_cd;

	/* If polling, assume that the card is always present. */
	if (host->quirks & SDHCI_QUIRK_BROKEN_CARD_DETECTION)
		return 1;

	/* Host native card detect */
	return !!(sdhci_readl(host, SDHCI_PRESENT_STATE) & SDHCI_CARD_PRESENT);
}