#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sdhci_pci_slot {TYPE_2__* host; TYPE_4__* chip; } ;
struct TYPE_10__ {int /*<<< orphan*/  caps2; } ;
struct TYPE_9__ {TYPE_3__* pdev; } ;
struct TYPE_8__ {scalar_t__ device; } ;
struct TYPE_6__ {int /*<<< orphan*/  hs400_enhanced_strobe; } ;
struct TYPE_7__ {TYPE_5__* mmc; TYPE_1__ mmc_host_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_CAP2_CQE ; 
 int /*<<< orphan*/  MMC_CAP2_CQE_DCMD ; 
 int /*<<< orphan*/  MMC_CAP2_HS400_ES ; 
 scalar_t__ PCI_DEVICE_ID_INTEL_GLK_EMMC ; 
 int byt_emmc_probe_slot (struct sdhci_pci_slot*) ; 
 int /*<<< orphan*/  intel_hs400_enhanced_strobe ; 

__attribute__((used)) static int glk_emmc_probe_slot(struct sdhci_pci_slot *slot)
{
	int ret = byt_emmc_probe_slot(slot);

	slot->host->mmc->caps2 |= MMC_CAP2_CQE;

	if (slot->chip->pdev->device != PCI_DEVICE_ID_INTEL_GLK_EMMC) {
		slot->host->mmc->caps2 |= MMC_CAP2_HS400_ES,
		slot->host->mmc_host_ops.hs400_enhanced_strobe =
						intel_hs400_enhanced_strobe;
		slot->host->mmc->caps2 |= MMC_CAP2_CQE_DCMD;
	}

	return ret;
}