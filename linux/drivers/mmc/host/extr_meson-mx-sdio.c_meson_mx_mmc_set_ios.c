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
struct mmc_ios {unsigned short vdd; unsigned long clock; int bus_width; int power_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  vmmc; } ;
struct mmc_host {TYPE_1__ supply; int /*<<< orphan*/  actual_clock; } ;
struct meson_mx_mmc_host {scalar_t__ error; int /*<<< orphan*/  cfg_div_clk; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MESON_MX_SDIO_CONF ; 
 int /*<<< orphan*/  MESON_MX_SDIO_CONF_BUS_WIDTH ; 
#define  MMC_BUS_WIDTH_1 132 
#define  MMC_BUS_WIDTH_4 131 
#define  MMC_BUS_WIDTH_8 130 
#define  MMC_POWER_OFF 129 
#define  MMC_POWER_UP 128 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 scalar_t__ clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  meson_mx_mmc_mask_bits (struct mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_dev (struct mmc_host*) ; 
 struct meson_mx_mmc_host* mmc_priv (struct mmc_host*) ; 
 scalar_t__ mmc_regulator_set_ocr (struct mmc_host*,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static void meson_mx_mmc_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct meson_mx_mmc_host *host = mmc_priv(mmc);
	unsigned short vdd = ios->vdd;
	unsigned long clk_rate = ios->clock;

	switch (ios->bus_width) {
	case MMC_BUS_WIDTH_1:
		meson_mx_mmc_mask_bits(mmc, MESON_MX_SDIO_CONF,
				       MESON_MX_SDIO_CONF_BUS_WIDTH, 0);
		break;

	case MMC_BUS_WIDTH_4:
		meson_mx_mmc_mask_bits(mmc, MESON_MX_SDIO_CONF,
				       MESON_MX_SDIO_CONF_BUS_WIDTH,
				       MESON_MX_SDIO_CONF_BUS_WIDTH);
		break;

	case MMC_BUS_WIDTH_8:
	default:
		dev_err(mmc_dev(mmc), "unsupported bus width: %d\n",
			ios->bus_width);
		host->error = -EINVAL;
		return;
	}

	host->error = clk_set_rate(host->cfg_div_clk, ios->clock);
	if (host->error) {
		dev_warn(mmc_dev(mmc),
				"failed to set MMC clock to %lu: %d\n",
				clk_rate, host->error);
		return;
	}

	mmc->actual_clock = clk_get_rate(host->cfg_div_clk);

	switch (ios->power_mode) {
	case MMC_POWER_OFF:
		vdd = 0;
		/* fall through */
	case MMC_POWER_UP:
		if (!IS_ERR(mmc->supply.vmmc)) {
			host->error = mmc_regulator_set_ocr(mmc,
							    mmc->supply.vmmc,
							    vdd);
			if (host->error)
				return;
		}
		break;
	}
}