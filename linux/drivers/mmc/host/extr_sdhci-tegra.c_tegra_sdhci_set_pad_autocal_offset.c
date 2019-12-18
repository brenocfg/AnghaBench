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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDHCI_AUTO_CAL_PDPU_OFFSET_MASK ; 
 int /*<<< orphan*/  SDHCI_TEGRA_AUTO_CAL_CONFIG ; 
 int /*<<< orphan*/  sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_sdhci_set_pad_autocal_offset(struct sdhci_host *host,
					       u16 pdpu)
{
	u32 reg;

	reg = sdhci_readl(host, SDHCI_TEGRA_AUTO_CAL_CONFIG);
	reg &= ~SDHCI_AUTO_CAL_PDPU_OFFSET_MASK;
	reg |= pdpu;
	sdhci_writel(host, reg, SDHCI_TEGRA_AUTO_CAL_CONFIG);
}