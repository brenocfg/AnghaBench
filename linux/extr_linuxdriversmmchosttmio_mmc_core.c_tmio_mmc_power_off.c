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
struct tmio_mmc_host {int /*<<< orphan*/  pdev; int /*<<< orphan*/  (* set_pwr ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;struct mmc_host* mmc; } ;
struct TYPE_2__ {int /*<<< orphan*/  vmmc; int /*<<< orphan*/  vqmmc; } ;
struct mmc_host {TYPE_1__ supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_regulator_set_ocr (struct mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tmio_mmc_power_off(struct tmio_mmc_host *host)
{
	struct mmc_host *mmc = host->mmc;

	if (!IS_ERR(mmc->supply.vqmmc))
		regulator_disable(mmc->supply.vqmmc);

	if (!IS_ERR(mmc->supply.vmmc))
		mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, 0);

	if (host->set_pwr)
		host->set_pwr(host->pdev, 0);
}