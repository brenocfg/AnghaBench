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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct sdhci_host {int flags; scalar_t__ version; int quirks2; int clock; int quirks; int timeout_clk; TYPE_3__* ops; int /*<<< orphan*/  timing; int /*<<< orphan*/  preset_enabled; TYPE_2__* mmc; } ;
struct mmc_ios {int clock; int drv_type; int /*<<< orphan*/  timing; int /*<<< orphan*/  bus_width; int /*<<< orphan*/  power_mode; int /*<<< orphan*/  vdd; } ;
struct TYPE_4__ {int /*<<< orphan*/  vmmc; } ;
struct mmc_host {TYPE_1__ supply; } ;
struct TYPE_6__ {int (* get_max_timeout_count ) (struct sdhci_host*) ;int /*<<< orphan*/  (* set_clock ) (struct sdhci_host*,int) ;int /*<<< orphan*/  (* set_uhs_signaling ) (struct sdhci_host*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_bus_width ) (struct sdhci_host*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* platform_send_init_74_clocks ) (struct sdhci_host*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_power ) (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int actual_clock; int max_busy_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMC_POWER_OFF ; 
 int /*<<< orphan*/  MMC_POWER_UNDEFINED ; 
 int /*<<< orphan*/  MMC_POWER_UP ; 
 int MMC_SET_DRIVER_TYPE_A ; 
 int MMC_SET_DRIVER_TYPE_B ; 
 int MMC_SET_DRIVER_TYPE_C ; 
 int MMC_SET_DRIVER_TYPE_D ; 
 int /*<<< orphan*/  MMC_TIMING_MMC_DDR52 ; 
 int /*<<< orphan*/  MMC_TIMING_MMC_HS ; 
 int /*<<< orphan*/  MMC_TIMING_MMC_HS200 ; 
 int /*<<< orphan*/  MMC_TIMING_MMC_HS400 ; 
 int /*<<< orphan*/  MMC_TIMING_SD_HS ; 
 int /*<<< orphan*/  MMC_TIMING_UHS_DDR50 ; 
 int /*<<< orphan*/  MMC_TIMING_UHS_SDR104 ; 
 int /*<<< orphan*/  MMC_TIMING_UHS_SDR12 ; 
 int /*<<< orphan*/  MMC_TIMING_UHS_SDR25 ; 
 int /*<<< orphan*/  MMC_TIMING_UHS_SDR50 ; 
 int SDHCI_CLOCK_CARD_EN ; 
 int /*<<< orphan*/  SDHCI_CLOCK_CONTROL ; 
 int SDHCI_CTRL_DRV_TYPE_A ; 
 int SDHCI_CTRL_DRV_TYPE_B ; 
 int SDHCI_CTRL_DRV_TYPE_C ; 
 int SDHCI_CTRL_DRV_TYPE_D ; 
 int SDHCI_CTRL_DRV_TYPE_MASK ; 
 int /*<<< orphan*/  SDHCI_CTRL_HISPD ; 
 int SDHCI_DEVICE_DEAD ; 
 int /*<<< orphan*/  SDHCI_HOST_CONTROL ; 
 int /*<<< orphan*/  SDHCI_HOST_CONTROL2 ; 
 int SDHCI_PRESET_DRV_MASK ; 
 int SDHCI_PRESET_DRV_SHIFT ; 
 int SDHCI_QUIRK2_PRESET_VALUE_BROKEN ; 
 int SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK ; 
 int SDHCI_QUIRK_NO_HISPD_BIT ; 
 int SDHCI_QUIRK_RESET_CMD_DATA_ON_IOS ; 
 int SDHCI_RESET_CMD ; 
 int SDHCI_RESET_DATA ; 
 int /*<<< orphan*/  SDHCI_SIGNAL_ENABLE ; 
 scalar_t__ SDHCI_SPEC_300 ; 
 int /*<<< orphan*/  mmc_hostname (struct mmc_host*) ; 
 struct sdhci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_regulator_set_ocr (struct mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_do_reset (struct sdhci_host*,int) ; 
 int /*<<< orphan*/  sdhci_enable_preset_value (struct sdhci_host*,int) ; 
 int sdhci_get_preset_value (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_readb (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int sdhci_readw (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_reinit (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_set_power (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writeb (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writew (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sdhci_host*,int) ; 
 int stub2 (struct sdhci_host*) ; 
 int /*<<< orphan*/  stub3 (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct sdhci_host*,int) ; 
 int /*<<< orphan*/  stub7 (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (struct sdhci_host*,int) ; 

void sdhci_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct sdhci_host *host = mmc_priv(mmc);
	u8 ctrl;

	if (ios->power_mode == MMC_POWER_UNDEFINED)
		return;

	if (host->flags & SDHCI_DEVICE_DEAD) {
		if (!IS_ERR(mmc->supply.vmmc) &&
		    ios->power_mode == MMC_POWER_OFF)
			mmc_regulator_set_ocr(mmc, mmc->supply.vmmc, 0);
		return;
	}

	/*
	 * Reset the chip on each power off.
	 * Should clear out any weird states.
	 */
	if (ios->power_mode == MMC_POWER_OFF) {
		sdhci_writel(host, 0, SDHCI_SIGNAL_ENABLE);
		sdhci_reinit(host);
	}

	if (host->version >= SDHCI_SPEC_300 &&
		(ios->power_mode == MMC_POWER_UP) &&
		!(host->quirks2 & SDHCI_QUIRK2_PRESET_VALUE_BROKEN))
		sdhci_enable_preset_value(host, false);

	if (!ios->clock || ios->clock != host->clock) {
		host->ops->set_clock(host, ios->clock);
		host->clock = ios->clock;

		if (host->quirks & SDHCI_QUIRK_DATA_TIMEOUT_USES_SDCLK &&
		    host->clock) {
			host->timeout_clk = host->mmc->actual_clock ?
						host->mmc->actual_clock / 1000 :
						host->clock / 1000;
			host->mmc->max_busy_timeout =
				host->ops->get_max_timeout_count ?
				host->ops->get_max_timeout_count(host) :
				1 << 27;
			host->mmc->max_busy_timeout /= host->timeout_clk;
		}
	}

	if (host->ops->set_power)
		host->ops->set_power(host, ios->power_mode, ios->vdd);
	else
		sdhci_set_power(host, ios->power_mode, ios->vdd);

	if (host->ops->platform_send_init_74_clocks)
		host->ops->platform_send_init_74_clocks(host, ios->power_mode);

	host->ops->set_bus_width(host, ios->bus_width);

	ctrl = sdhci_readb(host, SDHCI_HOST_CONTROL);

	if (!(host->quirks & SDHCI_QUIRK_NO_HISPD_BIT)) {
		if (ios->timing == MMC_TIMING_SD_HS ||
		     ios->timing == MMC_TIMING_MMC_HS ||
		     ios->timing == MMC_TIMING_MMC_HS400 ||
		     ios->timing == MMC_TIMING_MMC_HS200 ||
		     ios->timing == MMC_TIMING_MMC_DDR52 ||
		     ios->timing == MMC_TIMING_UHS_SDR50 ||
		     ios->timing == MMC_TIMING_UHS_SDR104 ||
		     ios->timing == MMC_TIMING_UHS_DDR50 ||
		     ios->timing == MMC_TIMING_UHS_SDR25)
			ctrl |= SDHCI_CTRL_HISPD;
		else
			ctrl &= ~SDHCI_CTRL_HISPD;
	}

	if (host->version >= SDHCI_SPEC_300) {
		u16 clk, ctrl_2;

		if (!host->preset_enabled) {
			sdhci_writeb(host, ctrl, SDHCI_HOST_CONTROL);
			/*
			 * We only need to set Driver Strength if the
			 * preset value enable is not set.
			 */
			ctrl_2 = sdhci_readw(host, SDHCI_HOST_CONTROL2);
			ctrl_2 &= ~SDHCI_CTRL_DRV_TYPE_MASK;
			if (ios->drv_type == MMC_SET_DRIVER_TYPE_A)
				ctrl_2 |= SDHCI_CTRL_DRV_TYPE_A;
			else if (ios->drv_type == MMC_SET_DRIVER_TYPE_B)
				ctrl_2 |= SDHCI_CTRL_DRV_TYPE_B;
			else if (ios->drv_type == MMC_SET_DRIVER_TYPE_C)
				ctrl_2 |= SDHCI_CTRL_DRV_TYPE_C;
			else if (ios->drv_type == MMC_SET_DRIVER_TYPE_D)
				ctrl_2 |= SDHCI_CTRL_DRV_TYPE_D;
			else {
				pr_warn("%s: invalid driver type, default to driver type B\n",
					mmc_hostname(mmc));
				ctrl_2 |= SDHCI_CTRL_DRV_TYPE_B;
			}

			sdhci_writew(host, ctrl_2, SDHCI_HOST_CONTROL2);
		} else {
			/*
			 * According to SDHC Spec v3.00, if the Preset Value
			 * Enable in the Host Control 2 register is set, we
			 * need to reset SD Clock Enable before changing High
			 * Speed Enable to avoid generating clock gliches.
			 */

			/* Reset SD Clock Enable */
			clk = sdhci_readw(host, SDHCI_CLOCK_CONTROL);
			clk &= ~SDHCI_CLOCK_CARD_EN;
			sdhci_writew(host, clk, SDHCI_CLOCK_CONTROL);

			sdhci_writeb(host, ctrl, SDHCI_HOST_CONTROL);

			/* Re-enable SD Clock */
			host->ops->set_clock(host, host->clock);
		}

		/* Reset SD Clock Enable */
		clk = sdhci_readw(host, SDHCI_CLOCK_CONTROL);
		clk &= ~SDHCI_CLOCK_CARD_EN;
		sdhci_writew(host, clk, SDHCI_CLOCK_CONTROL);

		host->ops->set_uhs_signaling(host, ios->timing);
		host->timing = ios->timing;

		if (!(host->quirks2 & SDHCI_QUIRK2_PRESET_VALUE_BROKEN) &&
				((ios->timing == MMC_TIMING_UHS_SDR12) ||
				 (ios->timing == MMC_TIMING_UHS_SDR25) ||
				 (ios->timing == MMC_TIMING_UHS_SDR50) ||
				 (ios->timing == MMC_TIMING_UHS_SDR104) ||
				 (ios->timing == MMC_TIMING_UHS_DDR50) ||
				 (ios->timing == MMC_TIMING_MMC_DDR52))) {
			u16 preset;

			sdhci_enable_preset_value(host, true);
			preset = sdhci_get_preset_value(host);
			ios->drv_type = (preset & SDHCI_PRESET_DRV_MASK)
				>> SDHCI_PRESET_DRV_SHIFT;
		}

		/* Re-enable SD Clock */
		host->ops->set_clock(host, host->clock);
	} else
		sdhci_writeb(host, ctrl, SDHCI_HOST_CONTROL);

	/*
	 * Some (ENE) controllers go apeshit on some ios operation,
	 * signalling timeout and CRC errors even on CMD0. Resetting
	 * it on each ios seems to solve the problem.
	 */
	if (host->quirks & SDHCI_QUIRK_RESET_CMD_DATA_ON_IOS)
		sdhci_do_reset(host, SDHCI_RESET_CMD | SDHCI_RESET_DATA);
}