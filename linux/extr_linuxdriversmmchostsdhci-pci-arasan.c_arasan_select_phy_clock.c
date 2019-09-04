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
typedef  int u8 ;
struct sdhci_pci_slot {int dummy; } ;
struct TYPE_4__ {scalar_t__ hs400_enhanced_strobe; } ;
struct sdhci_host {TYPE_3__* mmc; TYPE_1__ mmc_host_ops; } ;
struct arasan_host {int chg_clk; } ;
struct TYPE_5__ {int clock; int timing; int drv_type; } ;
struct TYPE_6__ {TYPE_2__ ios; } ;

/* Variables and functions */
 int /*<<< orphan*/  DDR50_MODE ; 
 int DLLTRM_ICP ; 
 int /*<<< orphan*/  ENHSTRB_MODE ; 
 int /*<<< orphan*/  HISPD_MODE ; 
 int /*<<< orphan*/  HS200_MODE ; 
 int /*<<< orphan*/  HS400_MODE ; 
 int /*<<< orphan*/  LEGACY_MODE ; 
#define  MMC_TIMING_LEGACY 135 
#define  MMC_TIMING_MMC_DDR52 134 
#define  MMC_TIMING_MMC_HS 133 
#define  MMC_TIMING_MMC_HS200 132 
#define  MMC_TIMING_MMC_HS400 131 
#define  MMC_TIMING_SD_HS 130 
#define  MMC_TIMING_UHS_DDR50 129 
#define  MMC_TIMING_UHS_SDR104 128 
 int /*<<< orphan*/  arasan_phy_set (struct sdhci_host*,int /*<<< orphan*/ ,int,int,int,int,int) ; 
 struct arasan_host* sdhci_pci_priv (struct sdhci_pci_slot*) ; 
 struct sdhci_pci_slot* sdhci_priv (struct sdhci_host*) ; 

__attribute__((used)) static int arasan_select_phy_clock(struct sdhci_host *host)
{
	struct sdhci_pci_slot *slot = sdhci_priv(host);
	struct arasan_host *arasan_host = sdhci_pci_priv(slot);
	u8 clk;

	if (arasan_host->chg_clk == host->mmc->ios.clock)
		return 0;

	arasan_host->chg_clk = host->mmc->ios.clock;
	if (host->mmc->ios.clock == 200000000)
		clk = 0x0;
	else if (host->mmc->ios.clock == 100000000)
		clk = 0x2;
	else if (host->mmc->ios.clock == 50000000)
		clk = 0x1;
	else
		clk = 0x0;

	if (host->mmc_host_ops.hs400_enhanced_strobe) {
		arasan_phy_set(host, ENHSTRB_MODE, 1, 0x0, 0x0,
			       DLLTRM_ICP, clk);
	} else {
		switch (host->mmc->ios.timing) {
		case MMC_TIMING_LEGACY:
			arasan_phy_set(host, LEGACY_MODE, 0x0, 0x0, 0x0,
				       0x0, 0x0);
			break;
		case MMC_TIMING_MMC_HS:
		case MMC_TIMING_SD_HS:
			arasan_phy_set(host, HISPD_MODE, 0x3, 0x0, 0x2,
				       DLLTRM_ICP, clk);
			break;
		case MMC_TIMING_MMC_HS200:
		case MMC_TIMING_UHS_SDR104:
			arasan_phy_set(host, HS200_MODE, 0x2,
				       host->mmc->ios.drv_type, 0x0,
				       DLLTRM_ICP, clk);
			break;
		case MMC_TIMING_MMC_DDR52:
		case MMC_TIMING_UHS_DDR50:
			arasan_phy_set(host, DDR50_MODE, 0x1, 0x0,
				       0x0, DLLTRM_ICP, clk);
			break;
		case MMC_TIMING_MMC_HS400:
			arasan_phy_set(host, HS400_MODE, 0x1,
				       host->mmc->ios.drv_type, 0xa,
				       DLLTRM_ICP, clk);
			break;
		default:
			break;
		}
	}
	return 0;
}