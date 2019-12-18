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
typedef  int /*<<< orphan*/  u8 ;
struct xenon_priv {int /*<<< orphan*/  sdhc_id; } ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 struct xenon_priv* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  xenon_enable_sdhc (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenon_enable_sdhc_parallel_tran (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenon_mask_cmd_conflict_err (struct sdhci_host*) ; 
 int /*<<< orphan*/  xenon_set_acg (struct sdhci_host*,int) ; 
 int /*<<< orphan*/  xenon_set_sdclk_off_idle (struct sdhci_host*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int xenon_sdhc_prepare(struct sdhci_host *host)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct xenon_priv *priv = sdhci_pltfm_priv(pltfm_host);
	u8 sdhc_id = priv->sdhc_id;

	/* Enable SDHC */
	xenon_enable_sdhc(host, sdhc_id);

	/* Enable ACG */
	xenon_set_acg(host, true);

	/* Enable Parallel Transfer Mode */
	xenon_enable_sdhc_parallel_tran(host, sdhc_id);

	/* Disable SDCLK-Off-While-Idle before card init */
	xenon_set_sdclk_off_idle(host, sdhc_id, false);

	xenon_mask_cmd_conflict_err(host);

	return 0;
}