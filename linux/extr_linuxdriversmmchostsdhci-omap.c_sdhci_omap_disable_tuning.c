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
struct sdhci_omap_host {int dummy; } ;

/* Variables and functions */
 int AC12_SCLK_SEL ; 
 int DLL_FORCE_VALUE ; 
 int DLL_SWT ; 
 int /*<<< orphan*/  SDHCI_OMAP_AC12 ; 
 int /*<<< orphan*/  SDHCI_OMAP_DLL ; 
 int sdhci_omap_readl (struct sdhci_omap_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_omap_writel (struct sdhci_omap_host*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sdhci_omap_disable_tuning(struct sdhci_omap_host *omap_host)
{
	u32 reg;

	reg = sdhci_omap_readl(omap_host, SDHCI_OMAP_AC12);
	reg &= ~AC12_SCLK_SEL;
	sdhci_omap_writel(omap_host, SDHCI_OMAP_AC12, reg);

	reg = sdhci_omap_readl(omap_host, SDHCI_OMAP_DLL);
	reg &= ~(DLL_FORCE_VALUE | DLL_SWT);
	sdhci_omap_writel(omap_host, SDHCI_OMAP_DLL, reg);
}