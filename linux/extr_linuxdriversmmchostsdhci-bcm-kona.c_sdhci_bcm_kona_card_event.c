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
struct sdhci_host {int /*<<< orphan*/  mmc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ mmc_gpio_get_cd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_bcm_kona_sd_card_emulate (struct sdhci_host*,int) ; 

__attribute__((used)) static void sdhci_bcm_kona_card_event(struct sdhci_host *host)
{
	if (mmc_gpio_get_cd(host->mmc) > 0) {
		dev_dbg(mmc_dev(host->mmc),
			"card inserted\n");
		sdhci_bcm_kona_sd_card_emulate(host, 1);
	} else {
		dev_dbg(mmc_dev(host->mmc),
			"card removed\n");
		sdhci_bcm_kona_sd_card_emulate(host, 0);
	}
}