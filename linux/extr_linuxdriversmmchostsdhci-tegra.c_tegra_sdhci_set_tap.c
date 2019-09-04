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
typedef  unsigned int u32 ;
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 unsigned int SDHCI_CLOCK_CTRL_TAP_MASK ; 
 unsigned int SDHCI_CLOCK_CTRL_TAP_SHIFT ; 
 int /*<<< orphan*/  SDHCI_TEGRA_VENDOR_CLOCK_CTRL ; 
 unsigned int sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_sdhci_set_tap(struct sdhci_host *host, unsigned int tap)
{
	u32 reg;

	reg = sdhci_readl(host, SDHCI_TEGRA_VENDOR_CLOCK_CTRL);
	reg &= ~SDHCI_CLOCK_CTRL_TAP_MASK;
	reg |= tap << SDHCI_CLOCK_CTRL_TAP_SHIFT;
	sdhci_writel(host, reg, SDHCI_TEGRA_VENDOR_CLOCK_CTRL);
}