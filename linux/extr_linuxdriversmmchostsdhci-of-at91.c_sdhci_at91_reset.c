#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sdhci_host {TYPE_1__* mmc; } ;
struct TYPE_2__ {int caps; } ;

/* Variables and functions */
 int MMC_CAP_NONREMOVABLE ; 
 int /*<<< orphan*/  sdhci_at91_set_force_card_detect (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_reset (struct sdhci_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdhci_at91_reset(struct sdhci_host *host, u8 mask)
{
	sdhci_reset(host, mask);

	if (host->mmc->caps & MMC_CAP_NONREMOVABLE)
		sdhci_at91_set_force_card_detect(host);
}