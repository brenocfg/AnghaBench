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
struct sdhci_tegra {int pad_control_available; TYPE_1__* soc_data; } ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_host {TYPE_2__* mmc; } ;
struct TYPE_6__ {int /*<<< orphan*/  vqmmc; } ;
struct TYPE_5__ {TYPE_3__ supply; } ;
struct TYPE_4__ {int nvquirks; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int NVQUIRK_NEEDS_PAD_CONTROL ; 
 int regulator_is_supported_voltage (int /*<<< orphan*/ ,int,int) ; 
 struct sdhci_tegra* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 

__attribute__((used)) static bool tegra_sdhci_is_pad_and_regulator_valid(struct sdhci_host *host)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_tegra *tegra_host = sdhci_pltfm_priv(pltfm_host);
	int has_1v8, has_3v3;

	/*
	 * The SoCs which have NVQUIRK_NEEDS_PAD_CONTROL require software pad
	 * voltage configuration in order to perform voltage switching. This
	 * means that valid pinctrl info is required on SDHCI instances capable
	 * of performing voltage switching. Whether or not an SDHCI instance is
	 * capable of voltage switching is determined based on the regulator.
	 */

	if (!(tegra_host->soc_data->nvquirks & NVQUIRK_NEEDS_PAD_CONTROL))
		return true;

	if (IS_ERR(host->mmc->supply.vqmmc))
		return false;

	has_1v8 = regulator_is_supported_voltage(host->mmc->supply.vqmmc,
						 1700000, 1950000);

	has_3v3 = regulator_is_supported_voltage(host->mmc->supply.vqmmc,
						 2700000, 3600000);

	if (has_1v8 == 1 && has_3v3 == 1)
		return tegra_host->pad_control_available;

	/* Fixed voltage, no pad control required. */
	return true;
}