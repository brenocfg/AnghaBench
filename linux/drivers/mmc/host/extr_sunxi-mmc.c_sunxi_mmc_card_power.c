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
struct sunxi_mmc_host {int vqmmc_enabled; int /*<<< orphan*/  ferror; struct mmc_host* mmc; } ;
struct mmc_ios {int power_mode; int /*<<< orphan*/  vdd; } ;
struct TYPE_2__ {int /*<<< orphan*/  vqmmc; int /*<<< orphan*/  vmmc; } ;
struct mmc_host {TYPE_1__ supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
#define  MMC_POWER_OFF 129 
#define  MMC_POWER_UP 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmc_dev (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_regulator_set_ocr (struct mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sunxi_mmc_card_power(struct sunxi_mmc_host *host,
				 struct mmc_ios *ios)
{
	struct mmc_host *mmc = host->mmc;

	switch (ios->power_mode) {
	case MMC_POWER_UP:
		dev_dbg(mmc_dev(mmc), "Powering card up\n");

		if (!IS_ERR(mmc->supply.vmmc)) {
			host->ferror = mmc_regulator_set_ocr(mmc,
							     mmc->supply.vmmc,
							     ios->vdd);
			if (host->ferror)
				return;
		}

		if (!IS_ERR(mmc->supply.vqmmc)) {
			host->ferror = regulator_enable(mmc->supply.vqmmc);
			if (host->ferror) {
				dev_err(mmc_dev(mmc),
					"failed to enable vqmmc\n");
				return;
			}
			host->vqmmc_enabled = true;
		}
		break;

	case MMC_POWER_OFF:
		dev_dbg(mmc_dev(mmc), "Powering card off\n");

		if (!IS_ERR(mmc->supply.vmmc))
			mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, 0);

		if (!IS_ERR(mmc->supply.vqmmc) && host->vqmmc_enabled)
			regulator_disable(mmc->supply.vqmmc);

		host->vqmmc_enabled = false;
		break;

	default:
		dev_dbg(mmc_dev(mmc), "Ignoring unknown card power state\n");
		break;
	}
}