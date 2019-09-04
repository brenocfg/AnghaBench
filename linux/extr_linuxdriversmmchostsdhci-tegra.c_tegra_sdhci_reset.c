#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct sdhci_tegra_soc_data {int nvquirks; } ;
struct sdhci_tegra {int pad_calib_required; int ddr_signaling; struct sdhci_tegra_soc_data* soc_data; } ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_host {TYPE_2__* mmc; } ;
struct TYPE_3__ {int /*<<< orphan*/  vqmmc; } ;
struct TYPE_4__ {TYPE_1__ supply; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int NVQUIRK_ENABLE_DDR50 ; 
 int NVQUIRK_ENABLE_SDHCI_SPEC_300 ; 
 int NVQUIRK_ENABLE_SDR104 ; 
 int NVQUIRK_ENABLE_SDR50 ; 
 int NVQUIRK_HAS_PADCALIB ; 
 int SDHCI_CLOCK_CTRL_SDR50_TUNING_OVERRIDE ; 
 int SDHCI_CLOCK_CTRL_SPI_MODE_CLKEN_OVERRIDE ; 
 int SDHCI_MISC_CTRL_ENABLE_DDR50 ; 
 int SDHCI_MISC_CTRL_ENABLE_SDHCI_SPEC_300 ; 
 int SDHCI_MISC_CTRL_ENABLE_SDR104 ; 
 int SDHCI_MISC_CTRL_ENABLE_SDR50 ; 
 int SDHCI_RESET_ALL ; 
 int /*<<< orphan*/  SDHCI_TEGRA_VENDOR_CLOCK_CTRL ; 
 int /*<<< orphan*/  SDHCI_TEGRA_VENDOR_MISC_CTRL ; 
 struct sdhci_tegra* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_reset (struct sdhci_host*,int) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_sdhci_reset(struct sdhci_host *host, u8 mask)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_tegra *tegra_host = sdhci_pltfm_priv(pltfm_host);
	const struct sdhci_tegra_soc_data *soc_data = tegra_host->soc_data;
	u32 misc_ctrl, clk_ctrl;

	sdhci_reset(host, mask);

	if (!(mask & SDHCI_RESET_ALL))
		return;

	misc_ctrl = sdhci_readl(host, SDHCI_TEGRA_VENDOR_MISC_CTRL);
	clk_ctrl = sdhci_readl(host, SDHCI_TEGRA_VENDOR_CLOCK_CTRL);

	misc_ctrl &= ~(SDHCI_MISC_CTRL_ENABLE_SDHCI_SPEC_300 |
		       SDHCI_MISC_CTRL_ENABLE_SDR50 |
		       SDHCI_MISC_CTRL_ENABLE_DDR50 |
		       SDHCI_MISC_CTRL_ENABLE_SDR104);

	clk_ctrl &= ~SDHCI_CLOCK_CTRL_SPI_MODE_CLKEN_OVERRIDE;

	/*
	 * If the board does not define a regulator for the SDHCI
	 * IO voltage, then don't advertise support for UHS modes
	 * even if the device supports it because the IO voltage
	 * cannot be configured.
	 */
	if (!IS_ERR(host->mmc->supply.vqmmc)) {
		/* Erratum: Enable SDHCI spec v3.00 support */
		if (soc_data->nvquirks & NVQUIRK_ENABLE_SDHCI_SPEC_300)
			misc_ctrl |= SDHCI_MISC_CTRL_ENABLE_SDHCI_SPEC_300;
		/* Advertise UHS modes as supported by host */
		if (soc_data->nvquirks & NVQUIRK_ENABLE_SDR50)
			misc_ctrl |= SDHCI_MISC_CTRL_ENABLE_SDR50;
		if (soc_data->nvquirks & NVQUIRK_ENABLE_DDR50)
			misc_ctrl |= SDHCI_MISC_CTRL_ENABLE_DDR50;
		if (soc_data->nvquirks & NVQUIRK_ENABLE_SDR104)
			misc_ctrl |= SDHCI_MISC_CTRL_ENABLE_SDR104;
		if (soc_data->nvquirks & SDHCI_MISC_CTRL_ENABLE_SDR50)
			clk_ctrl |= SDHCI_CLOCK_CTRL_SDR50_TUNING_OVERRIDE;
	}

	sdhci_writel(host, misc_ctrl, SDHCI_TEGRA_VENDOR_MISC_CTRL);
	sdhci_writel(host, clk_ctrl, SDHCI_TEGRA_VENDOR_CLOCK_CTRL);

	if (soc_data->nvquirks & NVQUIRK_HAS_PADCALIB)
		tegra_host->pad_calib_required = true;

	tegra_host->ddr_signaling = false;
}