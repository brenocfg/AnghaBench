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
struct sdhci_tegra {unsigned long curr_clk_rate; int pad_calib_required; scalar_t__ ddr_signaling; } ;
struct sdhci_pltfm_host {int /*<<< orphan*/  clk; } ;
struct sdhci_host {unsigned long max_clk; } ;

/* Variables and functions */
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 
 struct sdhci_tegra* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 void sdhci_set_clock (struct sdhci_host*,unsigned int) ; 
 int /*<<< orphan*/  tegra_sdhci_pad_autocalib (struct sdhci_host*) ; 

__attribute__((used)) static void tegra_sdhci_set_clock(struct sdhci_host *host, unsigned int clock)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_tegra *tegra_host = sdhci_pltfm_priv(pltfm_host);
	unsigned long host_clk;

	if (!clock)
		return sdhci_set_clock(host, clock);

	/*
	 * In DDR50/52 modes the Tegra SDHCI controllers require the SDHCI
	 * divider to be configured to divided the host clock by two. The SDHCI
	 * clock divider is calculated as part of sdhci_set_clock() by
	 * sdhci_calc_clk(). The divider is calculated from host->max_clk and
	 * the requested clock rate.
	 *
	 * By setting the host->max_clk to clock * 2 the divider calculation
	 * will always result in the correct value for DDR50/52 modes,
	 * regardless of clock rate rounding, which may happen if the value
	 * from clk_get_rate() is used.
	 */
	host_clk = tegra_host->ddr_signaling ? clock * 2 : clock;
	clk_set_rate(pltfm_host->clk, host_clk);
	tegra_host->curr_clk_rate = host_clk;
	if (tegra_host->ddr_signaling)
		host->max_clk = host_clk;
	else
		host->max_clk = clk_get_rate(pltfm_host->clk);

	sdhci_set_clock(host, clock);

	if (tegra_host->pad_calib_required) {
		tegra_sdhci_pad_autocalib(host);
		tegra_host->pad_calib_required = false;
	}
}