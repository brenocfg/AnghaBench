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
typedef  int u32 ;
struct sdhci_host {int dummy; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDHCI_BUFFER ; 
 int SDHCI_DATA_AVAILABLE ; 
 int /*<<< orphan*/  SDHCI_PRESENT_STATE ; 
 struct sdhci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  sdhci_cqe_enable (struct mmc_host*) ; 
 int sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sdhci_arasan_cqe_enable(struct mmc_host *mmc)
{
	struct sdhci_host *host = mmc_priv(mmc);
	u32 reg;

	reg = sdhci_readl(host, SDHCI_PRESENT_STATE);
	while (reg & SDHCI_DATA_AVAILABLE) {
		sdhci_readl(host, SDHCI_BUFFER);
		reg = sdhci_readl(host, SDHCI_PRESENT_STATE);
	}

	sdhci_cqe_enable(mmc);
}