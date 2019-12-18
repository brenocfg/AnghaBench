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
struct usdhi6_host {struct mmc_host* mmc; } ;
struct mmc_ios {int /*<<< orphan*/  vdd; scalar_t__ power_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  vmmc; } ;
struct mmc_host {TYPE_1__ supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_regulator_set_ocr (struct mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usdhi6_set_power(struct usdhi6_host *host, struct mmc_ios *ios)
{
	struct mmc_host *mmc = host->mmc;

	if (!IS_ERR(mmc->supply.vmmc))
		/* Errors ignored... */
		mmc_regulator_set_ocr(mmc, mmc->supply.vmmc,
				      ios->power_mode ? ios->vdd : 0);
}