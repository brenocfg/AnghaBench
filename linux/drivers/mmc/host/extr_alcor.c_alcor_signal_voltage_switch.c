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
struct mmc_ios {int signal_voltage; } ;
struct mmc_host {int dummy; } ;
struct alcor_sdmmc_host {int /*<<< orphan*/  cmd_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  AU6601_OPT ; 
 int /*<<< orphan*/  AU6601_OPT_SD_18V ; 
#define  MMC_SIGNAL_VOLTAGE_180 129 
#define  MMC_SIGNAL_VOLTAGE_330 128 
 int /*<<< orphan*/  alcor_rmw8 (struct alcor_sdmmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct alcor_sdmmc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int alcor_signal_voltage_switch(struct mmc_host *mmc,
				       struct mmc_ios *ios)
{
	struct alcor_sdmmc_host *host = mmc_priv(mmc);

	mutex_lock(&host->cmd_mutex);

	switch (ios->signal_voltage) {
	case MMC_SIGNAL_VOLTAGE_330:
		alcor_rmw8(host, AU6601_OPT, AU6601_OPT_SD_18V, 0);
		break;
	case MMC_SIGNAL_VOLTAGE_180:
		alcor_rmw8(host, AU6601_OPT, 0, AU6601_OPT_SD_18V);
		break;
	default:
		/* No signal voltage switch required */
		break;
	}

	mutex_unlock(&host->cmd_mutex);
	return 0;
}