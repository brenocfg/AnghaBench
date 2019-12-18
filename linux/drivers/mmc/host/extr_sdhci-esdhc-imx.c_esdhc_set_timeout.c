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
struct sdhci_host {int dummy; } ;
struct pltfm_imx_data {int dummy; } ;
struct mmc_command {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESDHC_SYS_CTRL_DTOCV_MASK ; 
 int /*<<< orphan*/  SDHCI_TIMEOUT_CONTROL ; 
 int /*<<< orphan*/  esdhc_clrset_le (struct sdhci_host*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ esdhc_is_usdhc (struct pltfm_imx_data*) ; 
 struct pltfm_imx_data* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 

__attribute__((used)) static void esdhc_set_timeout(struct sdhci_host *host, struct mmc_command *cmd)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct pltfm_imx_data *imx_data = sdhci_pltfm_priv(pltfm_host);

	/* use maximum timeout counter */
	esdhc_clrset_le(host, ESDHC_SYS_CTRL_DTOCV_MASK,
			esdhc_is_usdhc(imx_data) ? 0xF : 0xE,
			SDHCI_TIMEOUT_CONTROL);
}