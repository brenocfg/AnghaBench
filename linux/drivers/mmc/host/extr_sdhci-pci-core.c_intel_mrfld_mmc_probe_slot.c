#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sdhci_pci_slot {TYPE_4__* host; TYPE_2__* chip; } ;
struct TYPE_8__ {int ocr_mask; TYPE_3__* mmc; int /*<<< orphan*/  quirks2; } ;
struct TYPE_7__ {int caps; } ;
struct TYPE_6__ {TYPE_1__* pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  devfn; } ;

/* Variables and functions */
 int ENODEV ; 
#define  INTEL_MRFLD_EMMC_0 131 
#define  INTEL_MRFLD_EMMC_1 130 
#define  INTEL_MRFLD_SD 129 
#define  INTEL_MRFLD_SDIO 128 
 int MMC_CAP_1_8V_DDR ; 
 int MMC_CAP_8_BIT_DATA ; 
 int MMC_CAP_NONREMOVABLE ; 
 int MMC_CAP_POWER_OFF_CARD ; 
 int MMC_VDD_165_195 ; 
 int MMC_VDD_20_21 ; 
 unsigned int PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDHCI_QUIRK2_NO_1_8_V ; 
 int /*<<< orphan*/  intel_mrfld_mmc_fix_up_power_slot (struct sdhci_pci_slot*) ; 

__attribute__((used)) static int intel_mrfld_mmc_probe_slot(struct sdhci_pci_slot *slot)
{
	unsigned int func = PCI_FUNC(slot->chip->pdev->devfn);

	switch (func) {
	case INTEL_MRFLD_EMMC_0:
	case INTEL_MRFLD_EMMC_1:
		slot->host->mmc->caps |= MMC_CAP_NONREMOVABLE |
					 MMC_CAP_8_BIT_DATA |
					 MMC_CAP_1_8V_DDR;
		break;
	case INTEL_MRFLD_SD:
		slot->host->quirks2 |= SDHCI_QUIRK2_NO_1_8_V;
		break;
	case INTEL_MRFLD_SDIO:
		/* Advertise 2.0v for compatibility with the SDIO card's OCR */
		slot->host->ocr_mask = MMC_VDD_20_21 | MMC_VDD_165_195;
		slot->host->mmc->caps |= MMC_CAP_NONREMOVABLE |
					 MMC_CAP_POWER_OFF_CARD;
		break;
	default:
		return -ENODEV;
	}

	intel_mrfld_mmc_fix_up_power_slot(slot);
	return 0;
}