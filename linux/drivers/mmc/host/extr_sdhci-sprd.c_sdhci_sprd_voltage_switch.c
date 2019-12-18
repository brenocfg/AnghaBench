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
struct sdhci_sprd_host {int /*<<< orphan*/  pins_default; int /*<<< orphan*/  pinctrl; int /*<<< orphan*/  pins_uhs; } ;
struct sdhci_host {int dummy; } ;
struct mmc_ios {int signal_voltage; } ;
struct TYPE_2__ {int /*<<< orphan*/  vqmmc; } ;
struct mmc_host {TYPE_1__ supply; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
#define  MMC_SIGNAL_VOLTAGE_180 129 
#define  MMC_SIGNAL_VOLTAGE_330 128 
 int SDHCI_RESET_CMD ; 
 int SDHCI_RESET_DATA ; 
 struct sdhci_sprd_host* TO_SPRD_HOST (struct sdhci_host*) ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 struct sdhci_host* mmc_priv (struct mmc_host*) ; 
 int mmc_regulator_set_vqmmc (struct mmc_host*,struct mmc_ios*) ; 
 int pinctrl_select_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_reset (struct sdhci_host*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int sdhci_sprd_voltage_switch(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct sdhci_host *host = mmc_priv(mmc);
	struct sdhci_sprd_host *sprd_host = TO_SPRD_HOST(host);
	int ret;

	if (!IS_ERR(mmc->supply.vqmmc)) {
		ret = mmc_regulator_set_vqmmc(mmc, ios);
		if (ret) {
			pr_err("%s: Switching signalling voltage failed\n",
			       mmc_hostname(mmc));
			return ret;
		}
	}

	if (IS_ERR(sprd_host->pinctrl))
		return 0;

	switch (ios->signal_voltage) {
	case MMC_SIGNAL_VOLTAGE_180:
		ret = pinctrl_select_state(sprd_host->pinctrl,
					   sprd_host->pins_uhs);
		if (ret) {
			pr_err("%s: failed to select uhs pin state\n",
			       mmc_hostname(mmc));
			return ret;
		}
		break;

	default:
		/* fall-through */
	case MMC_SIGNAL_VOLTAGE_330:
		ret = pinctrl_select_state(sprd_host->pinctrl,
					   sprd_host->pins_default);
		if (ret) {
			pr_err("%s: failed to select default pin state\n",
			       mmc_hostname(mmc));
			return ret;
		}
		break;
	}

	/* Wait for 300 ~ 500 us for pin state stable */
	usleep_range(300, 500);
	sdhci_reset(host, SDHCI_RESET_CMD | SDHCI_RESET_DATA);

	return 0;
}