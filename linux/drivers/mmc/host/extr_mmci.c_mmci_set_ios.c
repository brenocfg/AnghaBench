#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct variant_data {int pwrreg_powerup; int opendrain; scalar_t__ explicit_mclk_control; scalar_t__ pwrreg_clkgate; scalar_t__ signal_direction; } ;
struct mmci_host {int vqmmc_enabled; int pwr_reg_add; scalar_t__ clock_cache; int /*<<< orphan*/  lock; TYPE_3__* ops; int /*<<< orphan*/  clk; int /*<<< orphan*/  mclk; struct mmc_host* mmc; struct variant_data* variant; int /*<<< orphan*/  pins_default; int /*<<< orphan*/  pinctrl; int /*<<< orphan*/  pins_opendrain; TYPE_1__* plat; } ;
struct mmc_ios {int power_mode; scalar_t__ bus_width; scalar_t__ bus_mode; scalar_t__ clock; int /*<<< orphan*/  vdd; } ;
struct TYPE_5__ {int /*<<< orphan*/  vqmmc; int /*<<< orphan*/  vmmc; } ;
struct mmc_host {TYPE_2__ supply; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_pwrreg ) (struct mmci_host*,int) ;int /*<<< orphan*/  (* set_clkreg ) (struct mmci_host*,scalar_t__) ;} ;
struct TYPE_4__ {scalar_t__ (* ios_handler ) (int /*<<< orphan*/ ,struct mmc_ios*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int MCI_PWR_ON ; 
 int MCI_ST_DATA2DIREN ; 
 int MCI_ST_DATA31DIREN ; 
 int MCI_ST_DATA74DIREN ; 
 scalar_t__ MMC_BUSMODE_OPENDRAIN ; 
 scalar_t__ MMC_BUS_WIDTH_1 ; 
 scalar_t__ MMC_BUS_WIDTH_4 ; 
#define  MMC_POWER_OFF 130 
#define  MMC_POWER_ON 129 
#define  MMC_POWER_UP 128 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mmc_dev (struct mmc_host*) ; 
 struct mmci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_regulator_set_ocr (struct mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmci_reg_delay (struct mmci_host*) ; 
 int /*<<< orphan*/  mmci_set_clkreg (struct mmci_host*,scalar_t__) ; 
 int /*<<< orphan*/  mmci_write_pwrreg (struct mmci_host*,int) ; 
 int /*<<< orphan*/  pinctrl_select_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,struct mmc_ios*) ; 
 int /*<<< orphan*/  stub2 (struct mmci_host*,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (struct mmci_host*,int) ; 

__attribute__((used)) static void mmci_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct mmci_host *host = mmc_priv(mmc);
	struct variant_data *variant = host->variant;
	u32 pwr = 0;
	unsigned long flags;
	int ret;

	if (host->plat->ios_handler &&
		host->plat->ios_handler(mmc_dev(mmc), ios))
			dev_err(mmc_dev(mmc), "platform ios_handler failed\n");

	switch (ios->power_mode) {
	case MMC_POWER_OFF:
		if (!IS_ERR(mmc->supply.vmmc))
			mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, 0);

		if (!IS_ERR(mmc->supply.vqmmc) && host->vqmmc_enabled) {
			regulator_disable(mmc->supply.vqmmc);
			host->vqmmc_enabled = false;
		}

		break;
	case MMC_POWER_UP:
		if (!IS_ERR(mmc->supply.vmmc))
			mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, ios->vdd);

		/*
		 * The ST Micro variant doesn't have the PL180s MCI_PWR_UP
		 * and instead uses MCI_PWR_ON so apply whatever value is
		 * configured in the variant data.
		 */
		pwr |= variant->pwrreg_powerup;

		break;
	case MMC_POWER_ON:
		if (!IS_ERR(mmc->supply.vqmmc) && !host->vqmmc_enabled) {
			ret = regulator_enable(mmc->supply.vqmmc);
			if (ret < 0)
				dev_err(mmc_dev(mmc),
					"failed to enable vqmmc regulator\n");
			else
				host->vqmmc_enabled = true;
		}

		pwr |= MCI_PWR_ON;
		break;
	}

	if (variant->signal_direction && ios->power_mode != MMC_POWER_OFF) {
		/*
		 * The ST Micro variant has some additional bits
		 * indicating signal direction for the signals in
		 * the SD/MMC bus and feedback-clock usage.
		 */
		pwr |= host->pwr_reg_add;

		if (ios->bus_width == MMC_BUS_WIDTH_4)
			pwr &= ~MCI_ST_DATA74DIREN;
		else if (ios->bus_width == MMC_BUS_WIDTH_1)
			pwr &= (~MCI_ST_DATA74DIREN &
				~MCI_ST_DATA31DIREN &
				~MCI_ST_DATA2DIREN);
	}

	if (variant->opendrain) {
		if (ios->bus_mode == MMC_BUSMODE_OPENDRAIN)
			pwr |= variant->opendrain;
	} else {
		/*
		 * If the variant cannot configure the pads by its own, then we
		 * expect the pinctrl to be able to do that for us
		 */
		if (ios->bus_mode == MMC_BUSMODE_OPENDRAIN)
			pinctrl_select_state(host->pinctrl, host->pins_opendrain);
		else
			pinctrl_select_state(host->pinctrl, host->pins_default);
	}

	/*
	 * If clock = 0 and the variant requires the MMCIPOWER to be used for
	 * gating the clock, the MCI_PWR_ON bit is cleared.
	 */
	if (!ios->clock && variant->pwrreg_clkgate)
		pwr &= ~MCI_PWR_ON;

	if (host->variant->explicit_mclk_control &&
	    ios->clock != host->clock_cache) {
		ret = clk_set_rate(host->clk, ios->clock);
		if (ret < 0)
			dev_err(mmc_dev(host->mmc),
				"Error setting clock rate (%d)\n", ret);
		else
			host->mclk = clk_get_rate(host->clk);
	}
	host->clock_cache = ios->clock;

	spin_lock_irqsave(&host->lock, flags);

	if (host->ops && host->ops->set_clkreg)
		host->ops->set_clkreg(host, ios->clock);
	else
		mmci_set_clkreg(host, ios->clock);

	if (host->ops && host->ops->set_pwrreg)
		host->ops->set_pwrreg(host, pwr);
	else
		mmci_write_pwrreg(host, pwr);

	mmci_reg_delay(host);

	spin_unlock_irqrestore(&host->lock, flags);
}