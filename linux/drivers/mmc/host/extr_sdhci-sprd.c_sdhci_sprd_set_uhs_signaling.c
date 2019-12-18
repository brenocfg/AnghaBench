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
typedef  int /*<<< orphan*/  u16 ;
struct sdhci_sprd_host {int /*<<< orphan*/ * phy_delay; } ;
struct sdhci_host {unsigned int timing; struct mmc_host* mmc; } ;
struct TYPE_2__ {int /*<<< orphan*/  enhanced_strobe; } ;
struct mmc_host {TYPE_1__ ios; } ;

/* Variables and functions */
#define  MMC_TIMING_MMC_DDR52 137 
#define  MMC_TIMING_MMC_HS 136 
#define  MMC_TIMING_MMC_HS200 135 
#define  MMC_TIMING_MMC_HS400 134 
#define  MMC_TIMING_SD_HS 133 
#define  MMC_TIMING_UHS_DDR50 132 
#define  MMC_TIMING_UHS_SDR104 131 
#define  MMC_TIMING_UHS_SDR12 130 
#define  MMC_TIMING_UHS_SDR25 129 
#define  MMC_TIMING_UHS_SDR50 128 
 int /*<<< orphan*/  SDHCI_CTRL_UHS_DDR50 ; 
 int /*<<< orphan*/  SDHCI_CTRL_UHS_MASK ; 
 int /*<<< orphan*/  SDHCI_CTRL_UHS_SDR104 ; 
 int /*<<< orphan*/  SDHCI_CTRL_UHS_SDR12 ; 
 int /*<<< orphan*/  SDHCI_CTRL_UHS_SDR25 ; 
 int /*<<< orphan*/  SDHCI_CTRL_UHS_SDR50 ; 
 int /*<<< orphan*/  SDHCI_HOST_CONTROL2 ; 
 int /*<<< orphan*/  SDHCI_SPRD_CTRL_HS200 ; 
 int /*<<< orphan*/  SDHCI_SPRD_CTRL_HS400 ; 
 int /*<<< orphan*/  SDHCI_SPRD_REG_32_DLL_DLY ; 
 struct sdhci_sprd_host* TO_SPRD_HOST (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_readw (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writew (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdhci_sprd_set_uhs_signaling(struct sdhci_host *host,
					 unsigned int timing)
{
	struct sdhci_sprd_host *sprd_host = TO_SPRD_HOST(host);
	struct mmc_host *mmc = host->mmc;
	u32 *p = sprd_host->phy_delay;
	u16 ctrl_2;

	if (timing == host->timing)
		return;

	ctrl_2 = sdhci_readw(host, SDHCI_HOST_CONTROL2);
	/* Select Bus Speed Mode for host */
	ctrl_2 &= ~SDHCI_CTRL_UHS_MASK;
	switch (timing) {
	case MMC_TIMING_UHS_SDR12:
		ctrl_2 |= SDHCI_CTRL_UHS_SDR12;
		break;
	case MMC_TIMING_MMC_HS:
	case MMC_TIMING_SD_HS:
	case MMC_TIMING_UHS_SDR25:
		ctrl_2 |= SDHCI_CTRL_UHS_SDR25;
		break;
	case MMC_TIMING_UHS_SDR50:
		ctrl_2 |= SDHCI_CTRL_UHS_SDR50;
		break;
	case MMC_TIMING_UHS_SDR104:
		ctrl_2 |= SDHCI_CTRL_UHS_SDR104;
		break;
	case MMC_TIMING_UHS_DDR50:
	case MMC_TIMING_MMC_DDR52:
		ctrl_2 |= SDHCI_CTRL_UHS_DDR50;
		break;
	case MMC_TIMING_MMC_HS200:
		ctrl_2 |= SDHCI_SPRD_CTRL_HS200;
		break;
	case MMC_TIMING_MMC_HS400:
		ctrl_2 |= SDHCI_SPRD_CTRL_HS400;
		break;
	default:
		break;
	}

	sdhci_writew(host, ctrl_2, SDHCI_HOST_CONTROL2);

	if (!mmc->ios.enhanced_strobe)
		sdhci_writel(host, p[timing], SDHCI_SPRD_REG_32_DLL_DLY);
}