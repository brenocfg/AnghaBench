#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mxcmci_host {scalar_t__ power_mode; TYPE_3__* mmc; TYPE_1__* pdata; } ;
struct TYPE_6__ {int /*<<< orphan*/  vmmc; } ;
struct TYPE_7__ {TYPE_2__ supply; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* setpower ) (int /*<<< orphan*/ ,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ MMC_POWER_OFF ; 
 scalar_t__ MMC_POWER_UP ; 
 int /*<<< orphan*/  mmc_dev (TYPE_3__*) ; 
 int /*<<< orphan*/  mmc_regulator_set_ocr (TYPE_3__*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void mxcmci_set_power(struct mxcmci_host *host, unsigned int vdd)
{
	if (!IS_ERR(host->mmc->supply.vmmc)) {
		if (host->power_mode == MMC_POWER_UP)
			mmc_regulator_set_ocr(host->mmc,
					      host->mmc->supply.vmmc, vdd);
		else if (host->power_mode == MMC_POWER_OFF)
			mmc_regulator_set_ocr(host->mmc,
					      host->mmc->supply.vmmc, 0);
	}

	if (host->pdata && host->pdata->setpower)
		host->pdata->setpower(mmc_dev(host->mmc), vdd);
}