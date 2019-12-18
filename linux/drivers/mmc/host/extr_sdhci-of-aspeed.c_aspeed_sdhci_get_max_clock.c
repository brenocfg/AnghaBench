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
struct sdhci_host {TYPE_1__* mmc; } ;
struct TYPE_2__ {unsigned int f_max; } ;

/* Variables and functions */
 unsigned int sdhci_pltfm_clk_get_max_clock (struct sdhci_host*) ; 

__attribute__((used)) static unsigned int aspeed_sdhci_get_max_clock(struct sdhci_host *host)
{
	if (host->mmc->f_max)
		return host->mmc->f_max;

	return sdhci_pltfm_clk_get_max_clock(host);
}