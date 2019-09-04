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
struct sdhci_pltfm_host {unsigned int clock; } ;
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 

__attribute__((used)) static unsigned int esdhc_pltfm_get_max_clock(struct sdhci_host *host)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);

	return pltfm_host->clock;
}