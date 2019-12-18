#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tmio_mmc_host {struct mmc_host* mmc; struct tmio_mmc_data* pdata; } ;
struct tmio_mmc_data {scalar_t__ ocr_mask; } ;
struct mmc_host {scalar_t__ ocr_avail; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int mmc_regulator_get_supply (struct mmc_host*) ; 

__attribute__((used)) static int tmio_mmc_init_ocr(struct tmio_mmc_host *host)
{
	struct tmio_mmc_data *pdata = host->pdata;
	struct mmc_host *mmc = host->mmc;
	int err;

	err = mmc_regulator_get_supply(mmc);
	if (err)
		return err;

	/* use ocr_mask if no regulator */
	if (!mmc->ocr_avail)
		mmc->ocr_avail = pdata->ocr_mask;

	/*
	 * try again.
	 * There is possibility that regulator has not been probed
	 */
	if (!mmc->ocr_avail)
		return -EPROBE_DEFER;

	return 0;
}