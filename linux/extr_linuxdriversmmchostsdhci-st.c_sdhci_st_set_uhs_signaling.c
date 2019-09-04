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
typedef  int u16 ;
struct st_mmc_platform_data {int /*<<< orphan*/  top_ioaddr; } ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_host {int /*<<< orphan*/  mmc; } ;

/* Variables and functions */
#define  MMC_TIMING_MMC_DDR52 134 
#define  MMC_TIMING_MMC_HS200 133 
#define  MMC_TIMING_UHS_DDR50 132 
#define  MMC_TIMING_UHS_SDR104 131 
#define  MMC_TIMING_UHS_SDR12 130 
#define  MMC_TIMING_UHS_SDR25 129 
#define  MMC_TIMING_UHS_SDR50 128 
 int SDHCI_CTRL_UHS_DDR50 ; 
 int SDHCI_CTRL_UHS_MASK ; 
 int SDHCI_CTRL_UHS_SDR104 ; 
 int SDHCI_CTRL_UHS_SDR12 ; 
 int SDHCI_CTRL_UHS_SDR25 ; 
 int SDHCI_CTRL_UHS_SDR50 ; 
 int SDHCI_CTRL_VDD_180 ; 
 int /*<<< orphan*/  SDHCI_HOST_CONTROL2 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 struct st_mmc_platform_data* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int sdhci_readw (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int sdhci_st_set_dll_for_clock (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_writew (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_mmcss_set_static_delay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdhci_st_set_uhs_signaling(struct sdhci_host *host,
					unsigned int uhs)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct st_mmc_platform_data *pdata = sdhci_pltfm_priv(pltfm_host);
	u16 ctrl_2 = sdhci_readw(host, SDHCI_HOST_CONTROL2);
	int ret = 0;

	/* Select Bus Speed Mode for host */
	ctrl_2 &= ~SDHCI_CTRL_UHS_MASK;
	switch (uhs) {
	/*
	 * Set V18_EN -- UHS modes do not work without this.
	 * does not change signaling voltage
	 */

	case MMC_TIMING_UHS_SDR12:
		st_mmcss_set_static_delay(pdata->top_ioaddr);
		ctrl_2 |= SDHCI_CTRL_UHS_SDR12 | SDHCI_CTRL_VDD_180;
		break;
	case MMC_TIMING_UHS_SDR25:
		st_mmcss_set_static_delay(pdata->top_ioaddr);
		ctrl_2 |= SDHCI_CTRL_UHS_SDR25 | SDHCI_CTRL_VDD_180;
		break;
	case MMC_TIMING_UHS_SDR50:
		st_mmcss_set_static_delay(pdata->top_ioaddr);
		ctrl_2 |= SDHCI_CTRL_UHS_SDR50 | SDHCI_CTRL_VDD_180;
		ret = sdhci_st_set_dll_for_clock(host);
		break;
	case MMC_TIMING_UHS_SDR104:
	case MMC_TIMING_MMC_HS200:
		st_mmcss_set_static_delay(pdata->top_ioaddr);
		ctrl_2 |= SDHCI_CTRL_UHS_SDR104 | SDHCI_CTRL_VDD_180;
		ret =  sdhci_st_set_dll_for_clock(host);
		break;
	case MMC_TIMING_UHS_DDR50:
	case MMC_TIMING_MMC_DDR52:
		st_mmcss_set_static_delay(pdata->top_ioaddr);
		ctrl_2 |= SDHCI_CTRL_UHS_DDR50 | SDHCI_CTRL_VDD_180;
		break;
	}

	if (ret)
		dev_warn(mmc_dev(host->mmc), "Error setting dll for clock "
						"(uhs %d)\n", uhs);

	dev_dbg(mmc_dev(host->mmc), "uhs %d, ctrl_2 %04X\n", uhs, ctrl_2);

	sdhci_writew(host, ctrl_2, SDHCI_HOST_CONTROL2);
}