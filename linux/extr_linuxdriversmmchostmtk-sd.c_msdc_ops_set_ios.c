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
struct msdc_host {int vqmmc_enabled; scalar_t__ timing; int /*<<< orphan*/  mclk; int /*<<< orphan*/  dev; } ;
struct mmc_ios {int power_mode; scalar_t__ timing; int /*<<< orphan*/  clock; int /*<<< orphan*/  vdd; int /*<<< orphan*/  bus_width; } ;
struct TYPE_2__ {int /*<<< orphan*/  vqmmc; int /*<<< orphan*/  vmmc; } ;
struct mmc_host {TYPE_1__ supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
#define  MMC_POWER_OFF 130 
#define  MMC_POWER_ON 129 
#define  MMC_POWER_UP 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct msdc_host* mmc_priv (struct mmc_host*) ; 
 int mmc_regulator_set_ocr (struct mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msdc_init_hw (struct msdc_host*) ; 
 int /*<<< orphan*/  msdc_set_buswidth (struct msdc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msdc_set_mclk (struct msdc_host*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void msdc_ops_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct msdc_host *host = mmc_priv(mmc);
	int ret;

	msdc_set_buswidth(host, ios->bus_width);

	/* Suspend/Resume will do power off/on */
	switch (ios->power_mode) {
	case MMC_POWER_UP:
		if (!IS_ERR(mmc->supply.vmmc)) {
			msdc_init_hw(host);
			ret = mmc_regulator_set_ocr(mmc, mmc->supply.vmmc,
					ios->vdd);
			if (ret) {
				dev_err(host->dev, "Failed to set vmmc power!\n");
				return;
			}
		}
		break;
	case MMC_POWER_ON:
		if (!IS_ERR(mmc->supply.vqmmc) && !host->vqmmc_enabled) {
			ret = regulator_enable(mmc->supply.vqmmc);
			if (ret)
				dev_err(host->dev, "Failed to set vqmmc power!\n");
			else
				host->vqmmc_enabled = true;
		}
		break;
	case MMC_POWER_OFF:
		if (!IS_ERR(mmc->supply.vmmc))
			mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, 0);

		if (!IS_ERR(mmc->supply.vqmmc) && host->vqmmc_enabled) {
			regulator_disable(mmc->supply.vqmmc);
			host->vqmmc_enabled = false;
		}
		break;
	default:
		break;
	}

	if (host->mclk != ios->clock || host->timing != ios->timing)
		msdc_set_mclk(host, ios->timing, ios->clock);
}