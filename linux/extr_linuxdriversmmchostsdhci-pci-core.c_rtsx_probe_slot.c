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
struct TYPE_3__ {int /*<<< orphan*/  caps2; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_CAP2_HS200 ; 

__attribute__((used)) static int rtsx_probe_slot(struct sdhci_pci_slot *slot)
{
	slot->host->mmc->caps2 |= MMC_CAP2_HS200;
	return 0;
}