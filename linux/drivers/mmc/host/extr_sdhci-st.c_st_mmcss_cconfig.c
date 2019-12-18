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
struct sdhci_pltfm_host {int /*<<< orphan*/  clk; } ;
struct sdhci_host {scalar_t__ ioaddr; struct mmc_host* mmc; } ;
struct mmc_host {int f_max; int caps; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BASE_CLK_FREQ_100 ; 
 int /*<<< orphan*/  BASE_CLK_FREQ_200 ; 
 int /*<<< orphan*/  BASE_CLK_FREQ_50 ; 
 int MMC_CAP_UHS_DDR50 ; 
 int MMC_CAP_UHS_SDR104 ; 
 int MMC_CAP_UHS_SDR50 ; 
 int /*<<< orphan*/  RETUNING_TIMER_CNT_MAX ; 
 int /*<<< orphan*/  ST_MMC_CCONFIG_1P8_VOLT ; 
 int /*<<< orphan*/  ST_MMC_CCONFIG_1_DEFAULT ; 
 int /*<<< orphan*/  ST_MMC_CCONFIG_2_DEFAULT ; 
 int /*<<< orphan*/  ST_MMC_CCONFIG_3_DEFAULT ; 
 int /*<<< orphan*/  ST_MMC_CCONFIG_4_DEFAULT ; 
 int /*<<< orphan*/  ST_MMC_CCONFIG_5_DEFAULT ; 
 int /*<<< orphan*/  ST_MMC_CCONFIG_DDR50 ; 
 int /*<<< orphan*/  ST_MMC_CCONFIG_EMMC_SLOT_TYPE ; 
 scalar_t__ ST_MMC_CCONFIG_REG_1 ; 
 scalar_t__ ST_MMC_CCONFIG_REG_2 ; 
 scalar_t__ ST_MMC_CCONFIG_REG_3 ; 
 scalar_t__ ST_MMC_CCONFIG_REG_4 ; 
 scalar_t__ ST_MMC_CCONFIG_REG_5 ; 
 int /*<<< orphan*/  ST_MMC_CCONFIG_SDR104 ; 
 int /*<<< orphan*/  ST_MMC_CCONFIG_SDR50 ; 
 int /*<<< orphan*/  ST_MMC_CCONFIG_TUNING_FOR_SDR50 ; 
 scalar_t__ ST_MMC_GP_OUTPUT ; 
 int /*<<< orphan*/  ST_MMC_GP_OUTPUT_CD ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmc_card_is_removable (struct mmc_host*) ; 
 int /*<<< orphan*/  of_device_is_compatible (struct device_node*,char*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void st_mmcss_cconfig(struct device_node *np, struct sdhci_host *host)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct mmc_host *mhost = host->mmc;
	u32 cconf2, cconf3, cconf4, cconf5;

	if (!of_device_is_compatible(np, "st,sdhci-stih407"))
		return;

	cconf2 = ST_MMC_CCONFIG_2_DEFAULT;
	cconf3 = ST_MMC_CCONFIG_3_DEFAULT;
	cconf4 = ST_MMC_CCONFIG_4_DEFAULT;
	cconf5 = ST_MMC_CCONFIG_5_DEFAULT;

	writel_relaxed(ST_MMC_CCONFIG_1_DEFAULT,
			host->ioaddr + ST_MMC_CCONFIG_REG_1);

	/* Set clock frequency, default to 50MHz if max-frequency is not
	 * provided */

	switch (mhost->f_max) {
	case 200000000:
		clk_set_rate(pltfm_host->clk, mhost->f_max);
		cconf2 |= BASE_CLK_FREQ_200;
		break;
	case 100000000:
		clk_set_rate(pltfm_host->clk, mhost->f_max);
		cconf2 |= BASE_CLK_FREQ_100;
		break;
	default:
		clk_set_rate(pltfm_host->clk, 50000000);
		cconf2 |= BASE_CLK_FREQ_50;
	}

	writel_relaxed(cconf2, host->ioaddr + ST_MMC_CCONFIG_REG_2);

	if (!mmc_card_is_removable(mhost))
		cconf3 |= ST_MMC_CCONFIG_EMMC_SLOT_TYPE;
	else
		/* CARD _D ET_CTRL */
		writel_relaxed(ST_MMC_GP_OUTPUT_CD,
				host->ioaddr + ST_MMC_GP_OUTPUT);

	if (mhost->caps & MMC_CAP_UHS_SDR50) {
		/* use 1.8V */
		cconf3 |= ST_MMC_CCONFIG_1P8_VOLT;
		cconf4 |= ST_MMC_CCONFIG_SDR50;
		/* Use tuning */
		cconf5 |= ST_MMC_CCONFIG_TUNING_FOR_SDR50;
		/* Max timeout for retuning */
		cconf5 |= RETUNING_TIMER_CNT_MAX;
	}

	if (mhost->caps & MMC_CAP_UHS_SDR104) {
		/*
		 * SDR104 implies the HC can support HS200 mode, so
		 * it's mandatory to use 1.8V
		 */
		cconf3 |= ST_MMC_CCONFIG_1P8_VOLT;
		cconf4 |= ST_MMC_CCONFIG_SDR104;
		/* Max timeout for retuning */
		cconf5 |= RETUNING_TIMER_CNT_MAX;
	}

	if (mhost->caps & MMC_CAP_UHS_DDR50)
		cconf4 |= ST_MMC_CCONFIG_DDR50;

	writel_relaxed(cconf3, host->ioaddr + ST_MMC_CCONFIG_REG_3);
	writel_relaxed(cconf4, host->ioaddr + ST_MMC_CCONFIG_REG_4);
	writel_relaxed(cconf5, host->ioaddr + ST_MMC_CCONFIG_REG_5);
}