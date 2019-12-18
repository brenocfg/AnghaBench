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
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_msm_host {int /*<<< orphan*/  saved_tuning_phase; } ;
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 int msm_config_cm_dll_phase (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int msm_init_cm_dll (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_msm_is_tuning_needed (struct sdhci_host*) ; 
 struct sdhci_msm_host* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 

__attribute__((used)) static int sdhci_msm_restore_sdr_dll_config(struct sdhci_host *host)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_msm_host *msm_host = sdhci_pltfm_priv(pltfm_host);
	int ret;

	/*
	 * SDR DLL comes into picture only for timing modes which needs
	 * tuning.
	 */
	if (!sdhci_msm_is_tuning_needed(host))
		return 0;

	/* Reset the tuning block */
	ret = msm_init_cm_dll(host);
	if (ret)
		return ret;

	/* Restore the tuning block */
	ret = msm_config_cm_dll_phase(host, msm_host->saved_tuning_phase);

	return ret;
}