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
struct sdhci_pci_slot {int cd_override_level; TYPE_5__* host; TYPE_3__* chip; scalar_t__ cd_idx; } ;
struct TYPE_6__ {int /*<<< orphan*/  get_cd; } ;
struct TYPE_10__ {TYPE_4__* mmc; TYPE_1__ mmc_host_ops; } ;
struct TYPE_9__ {int caps; int /*<<< orphan*/  caps2; } ;
struct TYPE_8__ {TYPE_2__* pdev; } ;
struct TYPE_7__ {scalar_t__ device; scalar_t__ subsystem_vendor; scalar_t__ subsystem_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_CAP2_AVOID_3_3V ; 
 int MMC_CAP_AGGRESSIVE_PM ; 
 int MMC_CAP_CD_WAKE ; 
 int MMC_CAP_WAIT_WHILE_BUSY ; 
 scalar_t__ PCI_DEVICE_ID_INTEL_APL_SD ; 
 scalar_t__ PCI_DEVICE_ID_INTEL_BXTM_SD ; 
 scalar_t__ PCI_DEVICE_ID_INTEL_BXT_SD ; 
 scalar_t__ PCI_DEVICE_ID_INTEL_GLK_SD ; 
 scalar_t__ PCI_SUBDEVICE_ID_NI_78E3 ; 
 scalar_t__ PCI_VENDOR_ID_NI ; 
 int /*<<< orphan*/  bxt_get_cd ; 
 int /*<<< orphan*/  byt_probe_slot (struct sdhci_pci_slot*) ; 

__attribute__((used)) static int byt_sd_probe_slot(struct sdhci_pci_slot *slot)
{
	byt_probe_slot(slot);
	slot->host->mmc->caps |= MMC_CAP_WAIT_WHILE_BUSY |
				 MMC_CAP_AGGRESSIVE_PM | MMC_CAP_CD_WAKE;
	slot->cd_idx = 0;
	slot->cd_override_level = true;
	if (slot->chip->pdev->device == PCI_DEVICE_ID_INTEL_BXT_SD ||
	    slot->chip->pdev->device == PCI_DEVICE_ID_INTEL_BXTM_SD ||
	    slot->chip->pdev->device == PCI_DEVICE_ID_INTEL_APL_SD ||
	    slot->chip->pdev->device == PCI_DEVICE_ID_INTEL_GLK_SD)
		slot->host->mmc_host_ops.get_cd = bxt_get_cd;

	if (slot->chip->pdev->subsystem_vendor == PCI_VENDOR_ID_NI &&
	    slot->chip->pdev->subsystem_device == PCI_SUBDEVICE_ID_NI_78E3)
		slot->host->mmc->caps2 |= MMC_CAP2_AVOID_3_3V;

	return 0;
}