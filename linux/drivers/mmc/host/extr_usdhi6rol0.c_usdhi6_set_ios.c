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
typedef  int u32 ;
struct usdhi6_host {scalar_t__ rate; } ;
struct mmc_ios {scalar_t__ clock; int power_mode; int /*<<< orphan*/  timing; int /*<<< orphan*/  bus_width; int /*<<< orphan*/  vdd; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_BUS_WIDTH_1 ; 
#define  MMC_POWER_OFF 130 
#define  MMC_POWER_ON 129 
#define  MMC_POWER_UP 128 
 int /*<<< orphan*/  MMC_TIMING_UHS_DDR50 ; 
 int /*<<< orphan*/  USDHI6_SDIF_MODE ; 
 int /*<<< orphan*/  USDHI6_SD_OPTION ; 
 int USDHI6_SD_OPTION_WIDTH_1 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmc_dev (struct mmc_host*) ; 
 struct usdhi6_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  usdhi6_clk_set (struct usdhi6_host*,struct mmc_ios*) ; 
 int /*<<< orphan*/  usdhi6_only_cd (struct usdhi6_host*) ; 
 int usdhi6_read (struct usdhi6_host*,int /*<<< orphan*/ ) ; 
 int usdhi6_reset (struct usdhi6_host*) ; 
 int /*<<< orphan*/  usdhi6_set_power (struct usdhi6_host*,struct mmc_ios*) ; 
 int /*<<< orphan*/  usdhi6_write (struct usdhi6_host*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void usdhi6_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct usdhi6_host *host = mmc_priv(mmc);
	u32 option, mode;
	int ret;

	dev_dbg(mmc_dev(mmc), "%uHz, OCR: %u, power %u, bus-width %u, timing %u\n",
		ios->clock, ios->vdd, ios->power_mode, ios->bus_width, ios->timing);

	switch (ios->power_mode) {
	case MMC_POWER_OFF:
		usdhi6_set_power(host, ios);
		usdhi6_only_cd(host);
		break;
	case MMC_POWER_UP:
		/*
		 * We only also touch USDHI6_SD_OPTION from .request(), which
		 * cannot race with MMC_POWER_UP
		 */
		ret = usdhi6_reset(host);
		if (ret < 0) {
			dev_err(mmc_dev(mmc), "Cannot reset the interface!\n");
		} else {
			usdhi6_set_power(host, ios);
			usdhi6_only_cd(host);
		}
		break;
	case MMC_POWER_ON:
		option = usdhi6_read(host, USDHI6_SD_OPTION);
		/*
		 * The eMMC standard only allows 4 or 8 bits in the DDR mode,
		 * the same probably holds for SD cards. We check here anyway,
		 * since the datasheet explicitly requires 4 bits for DDR.
		 */
		if (ios->bus_width == MMC_BUS_WIDTH_1) {
			if (ios->timing == MMC_TIMING_UHS_DDR50)
				dev_err(mmc_dev(mmc),
					"4 bits are required for DDR\n");
			option |= USDHI6_SD_OPTION_WIDTH_1;
			mode = 0;
		} else {
			option &= ~USDHI6_SD_OPTION_WIDTH_1;
			mode = ios->timing == MMC_TIMING_UHS_DDR50;
		}
		usdhi6_write(host, USDHI6_SD_OPTION, option);
		usdhi6_write(host, USDHI6_SDIF_MODE, mode);
		break;
	}

	if (host->rate != ios->clock)
		usdhi6_clk_set(host, ios);
}