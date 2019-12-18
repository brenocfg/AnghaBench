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
 int ENODEV ; 
 int MMC_CAP_8_BIT_DATA ; 
 int MMC_CAP_NONREMOVABLE ; 
 int arasan_phy_init (TYPE_2__*) ; 

__attribute__((used)) static int arasan_pci_probe_slot(struct sdhci_pci_slot *slot)
{
	int err;

	slot->host->mmc->caps |= MMC_CAP_NONREMOVABLE | MMC_CAP_8_BIT_DATA;
	err = arasan_phy_init(slot->host);
	if (err)
		return -ENODEV;
	return 0;
}