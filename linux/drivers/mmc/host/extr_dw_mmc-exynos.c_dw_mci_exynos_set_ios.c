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
struct mmc_ios {unsigned int clock; int timing; int /*<<< orphan*/  bus_width; } ;
struct dw_mci_exynos_priv_data {int ddr_timing; int sdr_timing; int ciu_div; int /*<<< orphan*/  tuned_sample; int /*<<< orphan*/  hs400_timing; } ;
struct dw_mci {struct dw_mci_exynos_priv_data* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMC_BUS_WIDTH_8 ; 
#define  MMC_TIMING_MMC_DDR52 132 
#define  MMC_TIMING_MMC_HS400 131 
#define  MMC_TIMING_UHS_DDR50 130 
#define  MMC_TIMING_UHS_SDR104 129 
#define  MMC_TIMING_UHS_SDR50 128 
 int SDMMC_CLKSEL_UP_SAMPLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_mci_exynos_adjust_clock (struct dw_mci*,unsigned int) ; 
 int /*<<< orphan*/  dw_mci_exynos_config_hs400 (struct dw_mci*,int) ; 
 int /*<<< orphan*/  dw_mci_exynos_set_clksel_timing (struct dw_mci*,int) ; 

__attribute__((used)) static void dw_mci_exynos_set_ios(struct dw_mci *host, struct mmc_ios *ios)
{
	struct dw_mci_exynos_priv_data *priv = host->priv;
	unsigned int wanted = ios->clock;
	u32 timing = ios->timing, clksel;

	switch (timing) {
	case MMC_TIMING_MMC_HS400:
		/* Update tuned sample timing */
		clksel = SDMMC_CLKSEL_UP_SAMPLE(
				priv->hs400_timing, priv->tuned_sample);
		wanted <<= 1;
		break;
	case MMC_TIMING_MMC_DDR52:
		clksel = priv->ddr_timing;
		/* Should be double rate for DDR mode */
		if (ios->bus_width == MMC_BUS_WIDTH_8)
			wanted <<= 1;
		break;
	case MMC_TIMING_UHS_SDR104:
	case MMC_TIMING_UHS_SDR50:
		clksel = (priv->sdr_timing & 0xfff8ffff) |
			(priv->ciu_div << 16);
		break;
	case MMC_TIMING_UHS_DDR50:
		clksel = (priv->ddr_timing & 0xfff8ffff) |
			(priv->ciu_div << 16);
		break;
	default:
		clksel = priv->sdr_timing;
	}

	/* Set clock timing for the requested speed mode*/
	dw_mci_exynos_set_clksel_timing(host, clksel);

	/* Configure setting for HS400 */
	dw_mci_exynos_config_hs400(host, timing);

	/* Configure clock rate */
	dw_mci_exynos_adjust_clock(host, wanted);
}