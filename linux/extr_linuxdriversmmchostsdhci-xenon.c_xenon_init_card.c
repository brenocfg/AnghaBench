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
struct xenon_priv {int /*<<< orphan*/  init_card_type; } ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_host {int dummy; } ;
struct mmc_host {int dummy; } ;
struct mmc_card {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 struct sdhci_host* mmc_priv (struct mmc_host*) ; 
 struct xenon_priv* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 

__attribute__((used)) static void xenon_init_card(struct mmc_host *mmc, struct mmc_card *card)
{
	struct sdhci_host *host = mmc_priv(mmc);
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct xenon_priv *priv = sdhci_pltfm_priv(pltfm_host);

	/* Update card type*/
	priv->init_card_type = card->type;
}