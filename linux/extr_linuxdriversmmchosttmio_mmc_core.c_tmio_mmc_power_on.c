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
struct tmio_mmc_host {TYPE_2__* pdev; int /*<<< orphan*/  (* set_pwr ) (TYPE_2__*,int) ;struct mmc_host* mmc; } ;
struct TYPE_3__ {int /*<<< orphan*/  vqmmc; int /*<<< orphan*/  vmmc; } ;
struct mmc_host {TYPE_1__ supply; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int mmc_regulator_set_ocr (struct mmc_host*,int /*<<< orphan*/ ,unsigned short) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void tmio_mmc_power_on(struct tmio_mmc_host *host, unsigned short vdd)
{
	struct mmc_host *mmc = host->mmc;
	int ret = 0;

	/* .set_ios() is returning void, so, no chance to report an error */

	if (host->set_pwr)
		host->set_pwr(host->pdev, 1);

	if (!IS_ERR(mmc->supply.vmmc)) {
		ret = mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, vdd);
		/*
		 * Attention: empiric value. With a b43 WiFi SDIO card this
		 * delay proved necessary for reliable card-insertion probing.
		 * 100us were not enough. Is this the same 140us delay, as in
		 * tmio_mmc_set_ios()?
		 */
		usleep_range(200, 300);
	}
	/*
	 * It seems, VccQ should be switched on after Vcc, this is also what the
	 * omap_hsmmc.c driver does.
	 */
	if (!IS_ERR(mmc->supply.vqmmc) && !ret) {
		ret = regulator_enable(mmc->supply.vqmmc);
		usleep_range(200, 300);
	}

	if (ret < 0)
		dev_dbg(&host->pdev->dev, "Regulators failed to power up: %d\n",
			ret);
}