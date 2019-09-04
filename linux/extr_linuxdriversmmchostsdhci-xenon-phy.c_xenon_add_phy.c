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
struct xenon_priv {scalar_t__ phy_type; int /*<<< orphan*/  phy_params; } ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_host {int /*<<< orphan*/  mmc; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ EMMC_5_1_PHY ; 
 int /*<<< orphan*/  NR_PHY_TYPES ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ match_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_types ; 
 struct xenon_priv* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int xenon_alloc_emmc_phy (struct sdhci_host*) ; 
 int xenon_emmc_phy_parse_param_dt (struct sdhci_host*,struct device_node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xenon_add_phy(struct device_node *np, struct sdhci_host *host,
			 const char *phy_name)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct xenon_priv *priv = sdhci_pltfm_priv(pltfm_host);
	int ret;

	priv->phy_type = match_string(phy_types, NR_PHY_TYPES, phy_name);
	if (priv->phy_type < 0) {
		dev_err(mmc_dev(host->mmc),
			"Unable to determine PHY name %s. Use default eMMC 5.1 PHY\n",
			phy_name);
		priv->phy_type = EMMC_5_1_PHY;
	}

	ret = xenon_alloc_emmc_phy(host);
	if (ret)
		return ret;

	return xenon_emmc_phy_parse_param_dt(host, np, priv->phy_params);
}