#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sdhci_pci_slot {TYPE_2__* host; } ;
struct TYPE_4__ {TYPE_1__* mmc; } ;
struct TYPE_3__ {int caps; } ;

/* Variables and functions */
 int MMC_CAP_NONREMOVABLE ; 
 int MMC_CAP_POWER_OFF_CARD ; 

__attribute__((used)) static int mfd_sdio_probe_slot(struct sdhci_pci_slot *slot)
{
	slot->host->mmc->caps |= MMC_CAP_POWER_OFF_CARD | MMC_CAP_NONREMOVABLE;
	return 0;
}