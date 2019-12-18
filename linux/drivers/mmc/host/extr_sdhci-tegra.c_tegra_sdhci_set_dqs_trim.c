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
typedef  int u32 ;
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 int SDHCI_TEGRA_CAP_OVERRIDES_DQS_TRIM_MASK ; 
 int SDHCI_TEGRA_CAP_OVERRIDES_DQS_TRIM_SHIFT ; 
 int /*<<< orphan*/  SDHCI_TEGRA_VENDOR_CAP_OVERRIDES ; 
 int sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_sdhci_set_dqs_trim(struct sdhci_host *host, u8 trim)
{
	u32 val;

	val = sdhci_readl(host, SDHCI_TEGRA_VENDOR_CAP_OVERRIDES);
	val &= ~SDHCI_TEGRA_CAP_OVERRIDES_DQS_TRIM_MASK;
	val |= trim << SDHCI_TEGRA_CAP_OVERRIDES_DQS_TRIM_SHIFT;
	sdhci_writel(host, val, SDHCI_TEGRA_VENDOR_CAP_OVERRIDES);
}