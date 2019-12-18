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
struct sdhci_host {int /*<<< orphan*/  mmc; } ;
struct sdhci_arasan_soc_ctl_map {int /*<<< orphan*/  baseclkfreq; } ;
struct sdhci_arasan_data {int /*<<< orphan*/  soc_ctl_base; struct sdhci_arasan_soc_ctl_map* soc_ctl_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_CLOSEST (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_arasan_syscon_write (struct sdhci_host*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sdhci_arasan_data* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 

__attribute__((used)) static void sdhci_arasan_update_baseclkfreq(struct sdhci_host *host)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_arasan_data *sdhci_arasan = sdhci_pltfm_priv(pltfm_host);
	const struct sdhci_arasan_soc_ctl_map *soc_ctl_map =
		sdhci_arasan->soc_ctl_map;
	u32 mhz = DIV_ROUND_CLOSEST(clk_get_rate(pltfm_host->clk), 1000000);

	/* Having a map is optional */
	if (!soc_ctl_map)
		return;

	/* If we have a map, we expect to have a syscon */
	if (!sdhci_arasan->soc_ctl_base) {
		pr_warn("%s: Have regmap, but no soc-ctl-syscon\n",
			mmc_hostname(host->mmc));
		return;
	}

	sdhci_arasan_syscon_write(host, &soc_ctl_map->baseclkfreq, mhz);
}