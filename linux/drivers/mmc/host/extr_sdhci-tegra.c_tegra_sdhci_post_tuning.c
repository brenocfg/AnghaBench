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
struct sdhci_tegra_soc_data {int min_tap_delay; int max_tap_delay; } ;
struct sdhci_tegra {int tuned_tap_delay; int curr_clk_rate; struct sdhci_tegra_soc_data* soc_data; } ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_host {int tuning_loop_count; int /*<<< orphan*/  mmc; } ;

/* Variables and functions */
 int SDHCI_CLOCK_CTRL_TAP_MASK ; 
 int SDHCI_CLOCK_CTRL_TAP_SHIFT ; 
 int /*<<< orphan*/  SDHCI_TEGRA_VENDOR_CLOCK_CTRL ; 
 int /*<<< orphan*/  SDHCI_TEGRA_VNDR_TUN_STATUS1 ; 
 int SDHCI_TEGRA_VNDR_TUN_STATUS1_END_TAP_SHIFT ; 
 int SDHCI_TEGRA_VNDR_TUN_STATUS1_TAP_MASK ; 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 struct sdhci_tegra* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_sdhci_set_tap (struct sdhci_host*,int) ; 
 int /*<<< orphan*/  tegra_sdhci_tap_correction (struct sdhci_host*,int,int,int) ; 

__attribute__((used)) static void tegra_sdhci_post_tuning(struct sdhci_host *host)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_tegra *tegra_host = sdhci_pltfm_priv(pltfm_host);
	const struct sdhci_tegra_soc_data *soc_data = tegra_host->soc_data;
	u32 avg_tap_dly, val, min_tap_dly, max_tap_dly;
	u8 fixed_tap, start_tap, end_tap, window_width;
	u8 thdupper, thdlower;
	u8 num_iter;
	u32 clk_rate_mhz, period_ps, bestcase, worstcase;

	/* retain HW tuned tap to use incase if no correction is needed */
	val = sdhci_readl(host, SDHCI_TEGRA_VENDOR_CLOCK_CTRL);
	tegra_host->tuned_tap_delay = (val & SDHCI_CLOCK_CTRL_TAP_MASK) >>
				      SDHCI_CLOCK_CTRL_TAP_SHIFT;
	if (soc_data->min_tap_delay && soc_data->max_tap_delay) {
		min_tap_dly = soc_data->min_tap_delay;
		max_tap_dly = soc_data->max_tap_delay;
		clk_rate_mhz = tegra_host->curr_clk_rate / USEC_PER_SEC;
		period_ps = USEC_PER_SEC / clk_rate_mhz;
		bestcase = period_ps / min_tap_dly;
		worstcase = period_ps / max_tap_dly;
		/*
		 * Upper and Lower bound thresholds used to detect merged and
		 * bubble windows
		 */
		thdupper = (2 * worstcase + bestcase) / 2;
		thdlower = worstcase / 4;
		/*
		 * fixed tap is used when HW tuning result contains single edge
		 * and tap is set at fixed tap delay relative to the first edge
		 */
		avg_tap_dly = (period_ps * 2) / (min_tap_dly + max_tap_dly);
		fixed_tap = avg_tap_dly / 2;

		val = sdhci_readl(host, SDHCI_TEGRA_VNDR_TUN_STATUS1);
		start_tap = val & SDHCI_TEGRA_VNDR_TUN_STATUS1_TAP_MASK;
		end_tap = (val >> SDHCI_TEGRA_VNDR_TUN_STATUS1_END_TAP_SHIFT) &
			  SDHCI_TEGRA_VNDR_TUN_STATUS1_TAP_MASK;
		window_width = end_tap - start_tap;
		num_iter = host->tuning_loop_count;
		/*
		 * partial window includes edges of the tuning range.
		 * merged window includes more taps so window width is higher
		 * than upper threshold.
		 */
		if (start_tap == 0 || (end_tap == (num_iter - 1)) ||
		    (end_tap == num_iter - 2) || window_width >= thdupper) {
			pr_debug("%s: Apply tuning correction\n",
				 mmc_hostname(host->mmc));
			tegra_sdhci_tap_correction(host, thdupper, thdlower,
						   fixed_tap);
		}
	}

	tegra_sdhci_set_tap(host, tegra_host->tuned_tap_delay);
}