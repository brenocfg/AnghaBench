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
struct wmt_mci_priv {scalar_t__ sdmmc_base; int /*<<< orphan*/  clk_sdmmc; } ;
struct mmc_ios {scalar_t__ power_mode; int bus_width; int /*<<< orphan*/  clock; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int BM_EIGHTBIT_MODE ; 
 int BM_FOURBIT_MODE ; 
 int EXT_EIGHTBIT ; 
#define  MMC_BUS_WIDTH_1 130 
#define  MMC_BUS_WIDTH_4 129 
#define  MMC_BUS_WIDTH_8 128 
 scalar_t__ MMC_POWER_OFF ; 
 scalar_t__ MMC_POWER_UP ; 
 scalar_t__ SDMMC_BUSMODE ; 
 scalar_t__ SDMMC_EXTCTRL ; 
 int /*<<< orphan*/  WMT_SD_POWER_OFF ; 
 int /*<<< orphan*/  WMT_SD_POWER_ON ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wmt_mci_priv* mmc_priv (struct mmc_host*) ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  wmt_reset_hardware (struct mmc_host*) ; 
 int /*<<< orphan*/  wmt_set_sd_power (struct wmt_mci_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static void wmt_mci_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{
	struct wmt_mci_priv *priv;
	u32 busmode, extctrl;

	priv = mmc_priv(mmc);

	if (ios->power_mode == MMC_POWER_UP) {
		wmt_reset_hardware(mmc);

		wmt_set_sd_power(priv, WMT_SD_POWER_ON);
	}
	if (ios->power_mode == MMC_POWER_OFF)
		wmt_set_sd_power(priv, WMT_SD_POWER_OFF);

	if (ios->clock != 0)
		clk_set_rate(priv->clk_sdmmc, ios->clock);

	busmode = readb(priv->sdmmc_base + SDMMC_BUSMODE);
	extctrl = readb(priv->sdmmc_base + SDMMC_EXTCTRL);

	busmode &= ~(BM_EIGHTBIT_MODE | BM_FOURBIT_MODE);
	extctrl &= ~EXT_EIGHTBIT;

	switch (ios->bus_width) {
	case MMC_BUS_WIDTH_8:
		busmode |= BM_EIGHTBIT_MODE;
		extctrl |= EXT_EIGHTBIT;
		break;
	case MMC_BUS_WIDTH_4:
		busmode |= BM_FOURBIT_MODE;
		break;
	case MMC_BUS_WIDTH_1:
		break;
	}

	writeb(busmode, priv->sdmmc_base + SDMMC_BUSMODE);
	writeb(extctrl, priv->sdmmc_base + SDMMC_EXTCTRL);
}