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

/* Variables and functions */
 int SDHCI_AUTO_CAL_ENABLE ; 
 int SDHCI_AUTO_CAL_START ; 
 int /*<<< orphan*/  SDHCI_TEGRA_AUTO_CAL_CONFIG ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_sdhci_pad_autocalib(struct sdhci_host *host)
{
	u32 val;

	mdelay(1);

	val = sdhci_readl(host, SDHCI_TEGRA_AUTO_CAL_CONFIG);
	val |= SDHCI_AUTO_CAL_ENABLE | SDHCI_AUTO_CAL_START;
	sdhci_writel(host,val, SDHCI_TEGRA_AUTO_CAL_CONFIG);
}