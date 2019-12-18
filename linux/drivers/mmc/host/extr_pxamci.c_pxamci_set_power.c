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
struct regulator {int dummy; } ;
struct pxamci_host {struct mmc_host* mmc; TYPE_1__* pdata; scalar_t__ power; } ;
struct TYPE_4__ {struct regulator* vmmc; } ;
struct mmc_host {TYPE_2__ supply; } ;
struct TYPE_3__ {int ocr_mask; int (* setpower ) (int /*<<< orphan*/ ,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct regulator*) ; 
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int) ; 
 int /*<<< orphan*/  mmc_dev (struct mmc_host*) ; 
 int mmc_regulator_set_ocr (struct mmc_host*,struct regulator*,unsigned int) ; 
 int stub1 (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline int pxamci_set_power(struct pxamci_host *host,
				    unsigned char power_mode,
				    unsigned int vdd)
{
	struct mmc_host *mmc = host->mmc;
	struct regulator *supply = mmc->supply.vmmc;

	if (!IS_ERR(supply))
		return mmc_regulator_set_ocr(mmc, supply, vdd);

	if (host->power) {
		bool on = !!((1 << vdd) & host->pdata->ocr_mask);
		gpiod_set_value(host->power, on);
	}

	if (host->pdata && host->pdata->setpower)
		return host->pdata->setpower(mmc_dev(host->mmc), vdd);

	return 0;
}