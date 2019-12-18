#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct omap_hsmmc_host {void* pbias; TYPE_3__* dev; struct mmc_host* mmc; } ;
struct TYPE_6__ {void* vqmmc; } ;
struct mmc_host {TYPE_1__ supply; } ;
struct TYPE_8__ {scalar_t__ of_node; } ;
struct TYPE_7__ {scalar_t__ no_regulator_off_init; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 void* devm_regulator_get_optional (TYPE_3__*,char*) ; 
 TYPE_2__* mmc_pdata (struct omap_hsmmc_host*) ; 
 int mmc_regulator_get_supply (struct mmc_host*) ; 
 int omap_hsmmc_disable_boot_regulators (struct omap_hsmmc_host*) ; 

__attribute__((used)) static int omap_hsmmc_reg_get(struct omap_hsmmc_host *host)
{
	int ret;
	struct mmc_host *mmc = host->mmc;


	ret = mmc_regulator_get_supply(mmc);
	if (ret)
		return ret;

	/* Allow an aux regulator */
	if (IS_ERR(mmc->supply.vqmmc)) {
		mmc->supply.vqmmc = devm_regulator_get_optional(host->dev,
								"vmmc_aux");
		if (IS_ERR(mmc->supply.vqmmc)) {
			ret = PTR_ERR(mmc->supply.vqmmc);
			if ((ret != -ENODEV) && host->dev->of_node)
				return ret;
			dev_dbg(host->dev, "unable to get vmmc_aux regulator %ld\n",
				PTR_ERR(mmc->supply.vqmmc));
		}
	}

	host->pbias = devm_regulator_get_optional(host->dev, "pbias");
	if (IS_ERR(host->pbias)) {
		ret = PTR_ERR(host->pbias);
		if ((ret != -ENODEV) && host->dev->of_node) {
			dev_err(host->dev,
			"SD card detect fail? enable CONFIG_REGULATOR_PBIAS\n");
			return ret;
		}
		dev_dbg(host->dev, "unable to get pbias regulator %ld\n",
			PTR_ERR(host->pbias));
	}

	/* For eMMC do not power off when not in sleep state */
	if (mmc_pdata(host)->no_regulator_off_init)
		return 0;

	ret = omap_hsmmc_disable_boot_regulators(host);
	if (ret)
		return ret;

	return 0;
}