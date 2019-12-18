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
 int MMC_CAP_WAIT_WHILE_BUSY ; 
 int /*<<< orphan*/  byt_probe_slot (struct sdhci_pci_slot*) ; 
 int ni_set_max_freq (struct sdhci_pci_slot*) ; 

__attribute__((used)) static int ni_byt_sdio_probe_slot(struct sdhci_pci_slot *slot)
{
	int err;

	byt_probe_slot(slot);

	err = ni_set_max_freq(slot);
	if (err)
		return err;

	slot->host->mmc->caps |= MMC_CAP_POWER_OFF_CARD | MMC_CAP_NONREMOVABLE |
				 MMC_CAP_WAIT_WHILE_BUSY;
	return 0;
}