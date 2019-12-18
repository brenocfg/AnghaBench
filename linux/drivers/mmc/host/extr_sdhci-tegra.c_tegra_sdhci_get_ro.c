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
 unsigned int mmc_gpio_get_ro (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int tegra_sdhci_get_ro(struct sdhci_host *host)
{
	/*
	 * Write-enable shall be assumed if GPIO is missing in a board's
	 * device-tree because SDHCI's WRITE_PROTECT bit doesn't work on
	 * Tegra.
	 */
	return mmc_gpio_get_ro(host->mmc);
}