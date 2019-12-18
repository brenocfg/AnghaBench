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
typedef  int /*<<< orphan*/  u32 ;
struct mmc_ios {int power_mode; int bus_width; int /*<<< orphan*/  vdd; } ;
struct TYPE_2__ {int /*<<< orphan*/  vqmmc; int /*<<< orphan*/  vmmc; } ;
struct mmc_host {TYPE_1__ supply; } ;
struct meson_host {int vqmmc_enabled; int /*<<< orphan*/  dev; scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_BUS_WIDTH_1 ; 
 int /*<<< orphan*/  CFG_BUS_WIDTH_4 ; 
 int /*<<< orphan*/  CFG_BUS_WIDTH_8 ; 
 int /*<<< orphan*/  CFG_BUS_WIDTH_MASK ; 
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
#define  MMC_BUS_WIDTH_1 133 
#define  MMC_BUS_WIDTH_4 132 
#define  MMC_BUS_WIDTH_8 131 
#define  MMC_POWER_OFF 130 
#define  MMC_POWER_ON 129 
#define  MMC_POWER_UP 128 
 scalar_t__ SD_EMMC_CFG ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  meson_mmc_check_resampling (struct meson_host*,struct mmc_ios*) ; 
 int meson_mmc_prepare_ios_clock (struct meson_host*,struct mmc_ios*) ; 
 struct meson_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_regulator_set_ocr (struct mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void meson_mmc_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct meson_host *host = mmc_priv(mmc);
	u32 bus_width, val;
	int err;

	/*
	 * GPIO regulator, only controls switching between 1v8 and
	 * 3v3, doesn't support MMC_POWER_OFF, MMC_POWER_ON.
	 */
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

		break;

	case MMC_POWER_ON:
		if (!IS_ERR(mmc->supply.vqmmc) && !host->vqmmc_enabled) {
			int ret = regulator_enable(mmc->supply.vqmmc);

			if (ret < 0)
				dev_err(host->dev,
					"failed to enable vqmmc regulator\n");
			else
				host->vqmmc_enabled = true;
		}

		break;
	}

	/* Bus width */
	switch (ios->bus_width) {
	case MMC_BUS_WIDTH_1:
		bus_width = CFG_BUS_WIDTH_1;
		break;
	case MMC_BUS_WIDTH_4:
		bus_width = CFG_BUS_WIDTH_4;
		break;
	case MMC_BUS_WIDTH_8:
		bus_width = CFG_BUS_WIDTH_8;
		break;
	default:
		dev_err(host->dev, "Invalid ios->bus_width: %u.  Setting to 4.\n",
			ios->bus_width);
		bus_width = CFG_BUS_WIDTH_4;
	}

	val = readl(host->regs + SD_EMMC_CFG);
	val &= ~CFG_BUS_WIDTH_MASK;
	val |= FIELD_PREP(CFG_BUS_WIDTH_MASK, bus_width);
	writel(val, host->regs + SD_EMMC_CFG);

	meson_mmc_check_resampling(host, ios);
	err = meson_mmc_prepare_ios_clock(host, ios);
	if (err)
		dev_err(host->dev, "Failed to set clock: %d\n,", err);

	dev_dbg(host->dev, "SD_EMMC_CFG:  0x%08x\n", val);
}