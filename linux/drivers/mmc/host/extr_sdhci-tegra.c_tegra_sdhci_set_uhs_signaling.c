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
typedef  int u8 ;
typedef  int u32 ;
struct sdhci_tegra {int ddr_signaling; int /*<<< orphan*/  dqs_trim; scalar_t__ default_tap; scalar_t__ tuned_tap_delay; } ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_host {int tuning_loop_count; } ;

/* Variables and functions */
#define  MMC_TIMING_MMC_DDR52 133 
#define  MMC_TIMING_MMC_HS200 132 
#define  MMC_TIMING_MMC_HS400 131 
#define  MMC_TIMING_UHS_DDR50 130 
#define  MMC_TIMING_UHS_SDR104 129 
#define  MMC_TIMING_UHS_SDR50 128 
 int /*<<< orphan*/  SDHCI_TEGRA_VNDR_TUN_CTRL1_0 ; 
 int /*<<< orphan*/  SDHCI_VNDR_TUN_CTRL0_0 ; 
 int SDHCI_VNDR_TUN_CTRL0_MUL_M_MASK ; 
 int SDHCI_VNDR_TUN_CTRL0_MUL_M_SHIFT ; 
 int SDHCI_VNDR_TUN_CTRL0_START_TAP_VAL_MASK ; 
 int SDHCI_VNDR_TUN_CTRL0_START_TAP_VAL_SHIFT ; 
 int SDHCI_VNDR_TUN_CTRL0_TUN_ITER_MASK ; 
 int SDHCI_VNDR_TUN_CTRL0_TUN_ITER_SHIFT ; 
 int TRIES_128 ; 
 int TRIES_256 ; 
 struct sdhci_tegra* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_set_uhs_signaling (struct sdhci_host*,unsigned int) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_sdhci_hs400_dll_cal (struct sdhci_host*) ; 
 int /*<<< orphan*/  tegra_sdhci_pad_autocalib (struct sdhci_host*) ; 
 int /*<<< orphan*/  tegra_sdhci_set_dqs_trim (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_sdhci_set_tap (struct sdhci_host*,scalar_t__) ; 

__attribute__((used)) static void tegra_sdhci_set_uhs_signaling(struct sdhci_host *host,
					  unsigned timing)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_tegra *tegra_host = sdhci_pltfm_priv(pltfm_host);
	bool set_default_tap = false;
	bool set_dqs_trim = false;
	bool do_hs400_dll_cal = false;
	u8 iter = TRIES_256;
	u32 val;

	tegra_host->ddr_signaling = false;
	switch (timing) {
	case MMC_TIMING_UHS_SDR50:
		break;
	case MMC_TIMING_UHS_SDR104:
	case MMC_TIMING_MMC_HS200:
		/* Don't set default tap on tunable modes. */
		iter = TRIES_128;
		break;
	case MMC_TIMING_MMC_HS400:
		set_dqs_trim = true;
		do_hs400_dll_cal = true;
		iter = TRIES_128;
		break;
	case MMC_TIMING_MMC_DDR52:
	case MMC_TIMING_UHS_DDR50:
		tegra_host->ddr_signaling = true;
		set_default_tap = true;
		break;
	default:
		set_default_tap = true;
		break;
	}

	val = sdhci_readl(host, SDHCI_VNDR_TUN_CTRL0_0);
	val &= ~(SDHCI_VNDR_TUN_CTRL0_TUN_ITER_MASK |
		 SDHCI_VNDR_TUN_CTRL0_START_TAP_VAL_MASK |
		 SDHCI_VNDR_TUN_CTRL0_MUL_M_MASK);
	val |= (iter << SDHCI_VNDR_TUN_CTRL0_TUN_ITER_SHIFT |
		0 << SDHCI_VNDR_TUN_CTRL0_START_TAP_VAL_SHIFT |
		1 << SDHCI_VNDR_TUN_CTRL0_MUL_M_SHIFT);
	sdhci_writel(host, val, SDHCI_VNDR_TUN_CTRL0_0);
	sdhci_writel(host, 0, SDHCI_TEGRA_VNDR_TUN_CTRL1_0);

	host->tuning_loop_count = (iter == TRIES_128) ? 128 : 256;

	sdhci_set_uhs_signaling(host, timing);

	tegra_sdhci_pad_autocalib(host);

	if (tegra_host->tuned_tap_delay && !set_default_tap)
		tegra_sdhci_set_tap(host, tegra_host->tuned_tap_delay);
	else
		tegra_sdhci_set_tap(host, tegra_host->default_tap);

	if (set_dqs_trim)
		tegra_sdhci_set_dqs_trim(host, tegra_host->dqs_trim);

	if (do_hs400_dll_cal)
		tegra_sdhci_hs400_dll_cal(host);
}