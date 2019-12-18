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
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDHCI_TEGRA_SDMEM_COMP_PADCTRL ; 
 int /*<<< orphan*/  SDHCI_TEGRA_SDMEM_COMP_PADCTRL_E_INPUT_E_PWRD ; 
 int /*<<< orphan*/  sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void tegra_sdhci_configure_cal_pad(struct sdhci_host *host, bool enable)
{
	u32 val;

	/*
	 * Enable or disable the additional I/O pad used by the drive strength
	 * calibration process.
	 */
	val = sdhci_readl(host, SDHCI_TEGRA_SDMEM_COMP_PADCTRL);

	if (enable)
		val |= SDHCI_TEGRA_SDMEM_COMP_PADCTRL_E_INPUT_E_PWRD;
	else
		val &= ~SDHCI_TEGRA_SDMEM_COMP_PADCTRL_E_INPUT_E_PWRD;

	sdhci_writel(host, val, SDHCI_TEGRA_SDMEM_COMP_PADCTRL);

	if (enable)
		usleep_range(1, 2);
}