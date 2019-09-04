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
struct omap_hsmmc_host {int vqmmc_enabled; } ;
struct mmc_ios {int /*<<< orphan*/  vdd; } ;
struct TYPE_2__ {int /*<<< orphan*/  vmmc; int /*<<< orphan*/  vqmmc; } ;
struct mmc_host {TYPE_1__ supply; struct mmc_ios ios; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmc_dev (struct mmc_host*) ; 
 struct omap_hsmmc_host* mmc_priv (struct mmc_host*) ; 
 int mmc_regulator_set_ocr (struct mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_hsmmc_enable_supply(struct mmc_host *mmc)
{
	int ret;
	struct omap_hsmmc_host *host = mmc_priv(mmc);
	struct mmc_ios *ios = &mmc->ios;

	if (!IS_ERR(mmc->supply.vmmc)) {
		ret = mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, ios->vdd);
		if (ret)
			return ret;
	}

	/* Enable interface voltage rail, if needed */
	if (!IS_ERR(mmc->supply.vqmmc) && !host->vqmmc_enabled) {
		ret = regulator_enable(mmc->supply.vqmmc);
		if (ret) {
			dev_err(mmc_dev(mmc), "vmmc_aux reg enable failed\n");
			goto err_vqmmc;
		}
		host->vqmmc_enabled = 1;
	}

	return 0;

err_vqmmc:
	if (!IS_ERR(mmc->supply.vmmc))
		mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, 0);

	return ret;
}