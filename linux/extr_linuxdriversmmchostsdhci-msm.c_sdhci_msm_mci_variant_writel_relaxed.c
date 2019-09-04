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
typedef  scalar_t__ u32 ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_msm_host {scalar_t__ core_mem; } ;
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 struct sdhci_msm_host* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  writel_relaxed (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void sdhci_msm_mci_variant_writel_relaxed(u32 val,
		struct sdhci_host *host, u32 offset)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_msm_host *msm_host = sdhci_pltfm_priv(pltfm_host);

	writel_relaxed(val, msm_host->core_mem + offset);
}