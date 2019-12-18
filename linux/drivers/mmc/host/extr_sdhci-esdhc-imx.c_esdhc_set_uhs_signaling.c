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
typedef  int u32 ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_host {int /*<<< orphan*/  clock; TYPE_1__* ops; scalar_t__ ioaddr; } ;
struct esdhc_platform_data {int delay_line; } ;
struct pltfm_imx_data {int is_ddr; struct esdhc_platform_data boarddata; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_clock ) (struct sdhci_host*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ ESDHC_DLL_CTRL ; 
 int ESDHC_DLL_OVERRIDE_EN_SHIFT ; 
 int ESDHC_DLL_OVERRIDE_VAL_SHIFT ; 
 scalar_t__ ESDHC_MIX_CTRL ; 
 int ESDHC_MIX_CTRL_DDREN ; 
 int ESDHC_MIX_CTRL_HS400_EN ; 
#define  MMC_TIMING_LEGACY 137 
#define  MMC_TIMING_MMC_DDR52 136 
#define  MMC_TIMING_MMC_HS 135 
#define  MMC_TIMING_MMC_HS200 134 
#define  MMC_TIMING_MMC_HS400 133 
#define  MMC_TIMING_UHS_DDR50 132 
#define  MMC_TIMING_UHS_SDR104 131 
#define  MMC_TIMING_UHS_SDR12 130 
#define  MMC_TIMING_UHS_SDR25 129 
#define  MMC_TIMING_UHS_SDR50 128 
 int /*<<< orphan*/  esdhc_change_pinstate (struct sdhci_host*,unsigned int) ; 
 int /*<<< orphan*/  esdhc_reset_tuning (struct sdhci_host*) ; 
 int /*<<< orphan*/  esdhc_set_strobe_dll (struct sdhci_host*) ; 
 int /*<<< orphan*/  is_imx53_esdhc (struct pltfm_imx_data*) ; 
 int readl (scalar_t__) ; 
 struct pltfm_imx_data* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  stub1 (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void esdhc_set_uhs_signaling(struct sdhci_host *host, unsigned timing)
{
	u32 m;
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct pltfm_imx_data *imx_data = sdhci_pltfm_priv(pltfm_host);
	struct esdhc_platform_data *boarddata = &imx_data->boarddata;

	/* disable ddr mode and disable HS400 mode */
	m = readl(host->ioaddr + ESDHC_MIX_CTRL);
	m &= ~(ESDHC_MIX_CTRL_DDREN | ESDHC_MIX_CTRL_HS400_EN);
	imx_data->is_ddr = 0;

	switch (timing) {
	case MMC_TIMING_UHS_SDR12:
	case MMC_TIMING_UHS_SDR25:
	case MMC_TIMING_UHS_SDR50:
	case MMC_TIMING_UHS_SDR104:
	case MMC_TIMING_MMC_HS:
	case MMC_TIMING_MMC_HS200:
		writel(m, host->ioaddr + ESDHC_MIX_CTRL);
		break;
	case MMC_TIMING_UHS_DDR50:
	case MMC_TIMING_MMC_DDR52:
		m |= ESDHC_MIX_CTRL_DDREN;
		writel(m, host->ioaddr + ESDHC_MIX_CTRL);
		imx_data->is_ddr = 1;
		if (boarddata->delay_line) {
			u32 v;
			v = boarddata->delay_line <<
				ESDHC_DLL_OVERRIDE_VAL_SHIFT |
				(1 << ESDHC_DLL_OVERRIDE_EN_SHIFT);
			if (is_imx53_esdhc(imx_data))
				v <<= 1;
			writel(v, host->ioaddr + ESDHC_DLL_CTRL);
		}
		break;
	case MMC_TIMING_MMC_HS400:
		m |= ESDHC_MIX_CTRL_DDREN | ESDHC_MIX_CTRL_HS400_EN;
		writel(m, host->ioaddr + ESDHC_MIX_CTRL);
		imx_data->is_ddr = 1;
		/* update clock after enable DDR for strobe DLL lock */
		host->ops->set_clock(host, host->clock);
		esdhc_set_strobe_dll(host);
		break;
	case MMC_TIMING_LEGACY:
	default:
		esdhc_reset_tuning(host);
		break;
	}

	esdhc_change_pinstate(host, timing);
}