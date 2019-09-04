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
struct sdhci_pltfm_host {int /*<<< orphan*/  clk; } ;
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 unsigned int SYSCTL_CLKD_MAX ; 
 unsigned int clk_get_rate (int /*<<< orphan*/ ) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 

__attribute__((used)) static unsigned int sdhci_omap_get_min_clock(struct sdhci_host *host)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);

	return clk_get_rate(pltfm_host->clk) / SYSCTL_CLKD_MAX;
}