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
struct msdc_host {int /*<<< orphan*/  pins_default; int /*<<< orphan*/  pinctrl; int /*<<< orphan*/  pins_uhs; int /*<<< orphan*/  dev; } ;
struct mmc_ios {int /*<<< orphan*/  signal_voltage; } ;
struct TYPE_2__ {int /*<<< orphan*/  vqmmc; } ;
struct mmc_host {TYPE_1__ supply; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMC_SIGNAL_VOLTAGE_180 ; 
 int /*<<< orphan*/  MMC_SIGNAL_VOLTAGE_330 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct msdc_host* mmc_priv (struct mmc_host*) ; 
 int mmc_regulator_set_vqmmc (struct mmc_host*,struct mmc_ios*) ; 
 int /*<<< orphan*/  pinctrl_select_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int msdc_ops_switch_volt(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct msdc_host *host = mmc_priv(mmc);
	int ret = 0;

	if (!IS_ERR(mmc->supply.vqmmc)) {
		if (ios->signal_voltage != MMC_SIGNAL_VOLTAGE_330 &&
		    ios->signal_voltage != MMC_SIGNAL_VOLTAGE_180) {
			dev_err(host->dev, "Unsupported signal voltage!\n");
			return -EINVAL;
		}

		ret = mmc_regulator_set_vqmmc(mmc, ios);
		if (ret) {
			dev_dbg(host->dev, "Regulator set error %d (%d)\n",
				ret, ios->signal_voltage);
		} else {
			/* Apply different pinctrl settings for different signal voltage */
			if (ios->signal_voltage == MMC_SIGNAL_VOLTAGE_180)
				pinctrl_select_state(host->pinctrl, host->pins_uhs);
			else
				pinctrl_select_state(host->pinctrl, host->pins_default);
		}
	}
	return ret;
}