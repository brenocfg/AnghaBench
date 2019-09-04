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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sdhci_host {int /*<<< orphan*/  ier; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESDHC_TBCTL ; 
 int /*<<< orphan*/  ESDHC_TB_EN ; 
 int /*<<< orphan*/  SDHCI_INT_ENABLE ; 
 int SDHCI_RESET_ALL ; 
 int /*<<< orphan*/  SDHCI_SIGNAL_ENABLE ; 
 int /*<<< orphan*/  sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_reset (struct sdhci_host*,int) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void esdhc_reset(struct sdhci_host *host, u8 mask)
{
	u32 val;

	sdhci_reset(host, mask);

	sdhci_writel(host, host->ier, SDHCI_INT_ENABLE);
	sdhci_writel(host, host->ier, SDHCI_SIGNAL_ENABLE);

	if (mask & SDHCI_RESET_ALL) {
		val = sdhci_readl(host, ESDHC_TBCTL);
		val &= ~ESDHC_TB_EN;
		sdhci_writel(host, val, ESDHC_TBCTL);
	}
}