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
struct omap_hsmmc_host {scalar_t__ vqmmc_enabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  vqmmc; int /*<<< orphan*/  vmmc; } ;
struct mmc_host {TYPE_1__ supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmc_dev (struct mmc_host*) ; 
 struct omap_hsmmc_host* mmc_priv (struct mmc_host*) ; 
 int mmc_regulator_set_ocr (struct mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_hsmmc_disable_supply(struct mmc_host *mmc)
{
	int ret;
	int status;
	struct omap_hsmmc_host *host = mmc_priv(mmc);

	if (!IS_ERR(mmc->supply.vqmmc) && host->vqmmc_enabled) {
		ret = regulator_disable(mmc->supply.vqmmc);
		if (ret) {
			dev_err(mmc_dev(mmc), "vmmc_aux reg disable failed\n");
			return ret;
		}
		host->vqmmc_enabled = 0;
	}

	if (!IS_ERR(mmc->supply.vmmc)) {
		ret = mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, 0);
		if (ret)
			goto err_set_ocr;
	}

	return 0;

err_set_ocr:
	if (!IS_ERR(mmc->supply.vqmmc)) {
		status = regulator_enable(mmc->supply.vqmmc);
		if (status)
			dev_err(mmc_dev(mmc), "vmmc_aux re-enable failed\n");
	}

	return ret;
}