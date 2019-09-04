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
struct sdhci_host {int /*<<< orphan*/  mmc; } ;

/* Variables and functions */
 int mmc_send_tuning (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_sdhci_set_tap (struct sdhci_host*,unsigned int) ; 

__attribute__((used)) static int tegra_sdhci_execute_tuning(struct sdhci_host *host, u32 opcode)
{
	unsigned int min, max;

	/*
	 * Start search for minimum tap value at 10, as smaller values are
	 * may wrongly be reported as working but fail at higher speeds,
	 * according to the TRM.
	 */
	min = 10;
	while (min < 255) {
		tegra_sdhci_set_tap(host, min);
		if (!mmc_send_tuning(host->mmc, opcode, NULL))
			break;
		min++;
	}

	/* Find the maximum tap value that still passes. */
	max = min + 1;
	while (max < 255) {
		tegra_sdhci_set_tap(host, max);
		if (mmc_send_tuning(host->mmc, opcode, NULL)) {
			max--;
			break;
		}
		max++;
	}

	/* The TRM states the ideal tap value is at 75% in the passing range. */
	tegra_sdhci_set_tap(host, min + ((max - min) * 3 / 4));

	return mmc_send_tuning(host->mmc, opcode, NULL);
}