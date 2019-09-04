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
struct mmc_ios {int signal_voltage; } ;
struct TYPE_2__ {int /*<<< orphan*/  vqmmc; } ;
struct mmc_host {TYPE_1__ supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
#define  MMC_SIGNAL_VOLTAGE_120 130 
#define  MMC_SIGNAL_VOLTAGE_180 129 
#define  MMC_SIGNAL_VOLTAGE_330 128 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmc_dev (struct mmc_host*) ; 
 int regulator_set_voltage (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int mmci_sig_volt_switch(struct mmc_host *mmc, struct mmc_ios *ios)
{
	int ret = 0;

	if (!IS_ERR(mmc->supply.vqmmc)) {

		switch (ios->signal_voltage) {
		case MMC_SIGNAL_VOLTAGE_330:
			ret = regulator_set_voltage(mmc->supply.vqmmc,
						2700000, 3600000);
			break;
		case MMC_SIGNAL_VOLTAGE_180:
			ret = regulator_set_voltage(mmc->supply.vqmmc,
						1700000, 1950000);
			break;
		case MMC_SIGNAL_VOLTAGE_120:
			ret = regulator_set_voltage(mmc->supply.vqmmc,
						1100000, 1300000);
			break;
		}

		if (ret)
			dev_warn(mmc_dev(mmc), "Voltage switch failed\n");
	}

	return ret;
}