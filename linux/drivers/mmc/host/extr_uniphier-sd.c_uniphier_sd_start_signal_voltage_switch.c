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
typedef  int /*<<< orphan*/  u32 ;
struct uniphier_sd_priv {int /*<<< orphan*/  pinctrl; struct pinctrl_state* pinstate_uhs; struct pinctrl_state* pinstate_default; } ;
struct tmio_mmc_host {scalar_t__ ctl; } ;
struct pinctrl_state {int dummy; } ;
struct mmc_ios {int signal_voltage; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  MMC_SIGNAL_VOLTAGE_180 129 
#define  MMC_SIGNAL_VOLTAGE_330 128 
 scalar_t__ UNIPHIER_SD_VOLT ; 
 int /*<<< orphan*/  UNIPHIER_SD_VOLT_180 ; 
 int /*<<< orphan*/  UNIPHIER_SD_VOLT_330 ; 
 int /*<<< orphan*/  UNIPHIER_SD_VOLT_MASK ; 
 struct tmio_mmc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  pinctrl_select_state (int /*<<< orphan*/ ,struct pinctrl_state*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 struct uniphier_sd_priv* uniphier_sd_priv (struct tmio_mmc_host*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int uniphier_sd_start_signal_voltage_switch(struct mmc_host *mmc,
						   struct mmc_ios *ios)
{
	struct tmio_mmc_host *host = mmc_priv(mmc);
	struct uniphier_sd_priv *priv = uniphier_sd_priv(host);
	struct pinctrl_state *pinstate;
	u32 val, tmp;

	switch (ios->signal_voltage) {
	case MMC_SIGNAL_VOLTAGE_330:
		val = UNIPHIER_SD_VOLT_330;
		pinstate = priv->pinstate_default;
		break;
	case MMC_SIGNAL_VOLTAGE_180:
		val = UNIPHIER_SD_VOLT_180;
		pinstate = priv->pinstate_uhs;
		break;
	default:
		return -ENOTSUPP;
	}

	tmp = readl(host->ctl + UNIPHIER_SD_VOLT);
	tmp &= ~UNIPHIER_SD_VOLT_MASK;
	tmp |= FIELD_PREP(UNIPHIER_SD_VOLT_MASK, val);
	writel(tmp, host->ctl + UNIPHIER_SD_VOLT);

	pinctrl_select_state(priv->pinctrl, pinstate);

	return 0;
}