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
struct sdhci_tegra {int enable_hwcq; } ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_host {TYPE_1__* mmc; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 scalar_t__ device_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 struct sdhci_tegra* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  tegra_sdhci_parse_pad_autocal_dt (struct sdhci_host*) ; 
 int /*<<< orphan*/  tegra_sdhci_parse_tap_and_trim (struct sdhci_host*) ; 

__attribute__((used)) static void tegra_sdhci_parse_dt(struct sdhci_host *host)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_tegra *tegra_host = sdhci_pltfm_priv(pltfm_host);

	if (device_property_read_bool(host->mmc->parent, "supports-cqe"))
		tegra_host->enable_hwcq = true;
	else
		tegra_host->enable_hwcq = false;

	tegra_sdhci_parse_pad_autocal_dt(host);
	tegra_sdhci_parse_tap_and_trim(host);
}