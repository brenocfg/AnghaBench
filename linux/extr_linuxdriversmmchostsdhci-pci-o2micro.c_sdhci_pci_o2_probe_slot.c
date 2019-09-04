#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sdhci_pci_slot {struct sdhci_host* host; struct sdhci_pci_chip* chip; } ;
struct sdhci_pci_chip {TYPE_2__* pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  execute_tuning; } ;
struct sdhci_host {TYPE_1__ mmc_host_ops; TYPE_3__* mmc; int /*<<< orphan*/  flags; int /*<<< orphan*/  quirks; } ;
struct TYPE_6__ {int /*<<< orphan*/  caps2; } ;
struct TYPE_5__ {int device; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MMC_CAP2_NO_SD ; 
 int /*<<< orphan*/  MMC_CAP2_NO_SDIO ; 
 int /*<<< orphan*/  O2_SD_MISC_SETTING ; 
 int /*<<< orphan*/  O2_SD_VENDOR_SETTING ; 
 int /*<<< orphan*/  O2_SD_VENDOR_SETTING2 ; 
#define  PCI_DEVICE_ID_O2_FUJIN2 132 
#define  PCI_DEVICE_ID_O2_SDS0 131 
#define  PCI_DEVICE_ID_O2_SDS1 130 
#define  PCI_DEVICE_ID_O2_SEABIRD0 129 
#define  PCI_DEVICE_ID_O2_SEABIRD1 128 
 int /*<<< orphan*/  SDHCI_QUIRK_MULTIBLOCK_READ_ACMD12 ; 
 int /*<<< orphan*/  SDHCI_SIGNALING_180 ; 
 int /*<<< orphan*/  SDHCI_SIGNALING_330 ; 
 int /*<<< orphan*/  mmc_hostname (TYPE_3__*) ; 
 int pci_read_config_dword (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_o2_execute_tuning ; 
 int /*<<< orphan*/  sdhci_pci_o2_enable_msi (struct sdhci_pci_chip*,struct sdhci_host*) ; 
 int sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 

int sdhci_pci_o2_probe_slot(struct sdhci_pci_slot *slot)
{
	struct sdhci_pci_chip *chip;
	struct sdhci_host *host;
	u32 reg;
	int ret;

	chip = slot->chip;
	host = slot->host;
	switch (chip->pdev->device) {
	case PCI_DEVICE_ID_O2_SDS0:
	case PCI_DEVICE_ID_O2_SEABIRD0:
	case PCI_DEVICE_ID_O2_SEABIRD1:
	case PCI_DEVICE_ID_O2_SDS1:
	case PCI_DEVICE_ID_O2_FUJIN2:
		reg = sdhci_readl(host, O2_SD_VENDOR_SETTING);
		if (reg & 0x1)
			host->quirks |= SDHCI_QUIRK_MULTIBLOCK_READ_ACMD12;

		sdhci_pci_o2_enable_msi(chip, host);

		if (chip->pdev->device == PCI_DEVICE_ID_O2_SEABIRD0) {
			ret = pci_read_config_dword(chip->pdev,
						    O2_SD_MISC_SETTING, &reg);
			if (ret)
				return -EIO;
			if (reg & (1 << 4)) {
				pr_info("%s: emmc 1.8v flag is set, force 1.8v signaling voltage\n",
					mmc_hostname(host->mmc));
				host->flags &= ~SDHCI_SIGNALING_330;
				host->flags |= SDHCI_SIGNALING_180;
				host->mmc->caps2 |= MMC_CAP2_NO_SD;
				host->mmc->caps2 |= MMC_CAP2_NO_SDIO;
			}
		}

		host->mmc_host_ops.execute_tuning = sdhci_o2_execute_tuning;

		if (chip->pdev->device != PCI_DEVICE_ID_O2_FUJIN2)
			break;
		/* set dll watch dog timer */
		reg = sdhci_readl(host, O2_SD_VENDOR_SETTING2);
		reg |= (1 << 12);
		sdhci_writel(host, reg, O2_SD_VENDOR_SETTING2);

		break;
	default:
		break;
	}

	return 0;
}