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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sdhci_pci_slot {TYPE_1__* chip; } ;
struct sdhci_host {TYPE_2__* mmc; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {scalar_t__ retune_period; } ;
struct TYPE_3__ {struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_MSLEEP_DURATION ; 
 int EIO ; 
 int SDHCI_RESET_CMD ; 
 int SDHCI_RESET_DATA ; 
 int /*<<< orphan*/  SDHCI_SOFTWARE_RESET ; 
 int /*<<< orphan*/  amd_config_tuning_phase (struct pci_dev*,int) ; 
 int /*<<< orphan*/  amd_enable_manual_tuning (struct pci_dev*) ; 
 int /*<<< orphan*/  amd_tuning_reset (struct sdhci_host*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ mmc_send_tuning (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 struct sdhci_pci_slot* sdhci_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_writeb (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amd_execute_tuning_hs200(struct sdhci_host *host, u32 opcode)
{
	struct sdhci_pci_slot *slot = sdhci_priv(host);
	struct pci_dev *pdev = slot->chip->pdev;
	u8 valid_win = 0;
	u8 valid_win_max = 0;
	u8 valid_win_end = 0;
	u8 ctrl, tune_around;

	amd_tuning_reset(host);

	for (tune_around = 0; tune_around < 12; tune_around++) {
		amd_config_tuning_phase(pdev, tune_around);

		if (mmc_send_tuning(host->mmc, opcode, NULL)) {
			valid_win = 0;
			msleep(AMD_MSLEEP_DURATION);
			ctrl = SDHCI_RESET_CMD | SDHCI_RESET_DATA;
			sdhci_writeb(host, ctrl, SDHCI_SOFTWARE_RESET);
		} else if (++valid_win > valid_win_max) {
			valid_win_max = valid_win;
			valid_win_end = tune_around;
		}
	}

	if (!valid_win_max) {
		dev_err(&pdev->dev, "no tuning point found\n");
		return -EIO;
	}

	amd_config_tuning_phase(pdev, valid_win_end - valid_win_max / 2);

	amd_enable_manual_tuning(pdev);

	host->mmc->retune_period = 0;

	return 0;
}