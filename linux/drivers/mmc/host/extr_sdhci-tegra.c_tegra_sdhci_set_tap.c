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
struct sdhci_tegra_soc_data {int nvquirks; } ;
struct sdhci_tegra {struct sdhci_tegra_soc_data* soc_data; } ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_host {int dummy; } ;

/* Variables and functions */
 int NVQUIRK_DIS_CARD_CLK_CONFIG_TAP ; 
 unsigned int SDHCI_CLOCK_CTRL_TAP_MASK ; 
 unsigned int SDHCI_CLOCK_CTRL_TAP_SHIFT ; 
 int SDHCI_RESET_CMD ; 
 int SDHCI_RESET_DATA ; 
 int /*<<< orphan*/  SDHCI_TEGRA_VENDOR_CLOCK_CTRL ; 
 struct sdhci_tegra* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 unsigned int sdhci_readl (struct sdhci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_reset (struct sdhci_host*,int) ; 
 int /*<<< orphan*/  sdhci_writel (struct sdhci_host*,unsigned int,int /*<<< orphan*/ ) ; 
 int tegra_sdhci_configure_card_clk (struct sdhci_host*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void tegra_sdhci_set_tap(struct sdhci_host *host, unsigned int tap)
{
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_tegra *tegra_host = sdhci_pltfm_priv(pltfm_host);
	const struct sdhci_tegra_soc_data *soc_data = tegra_host->soc_data;
	bool card_clk_enabled = false;
	u32 reg;

	/*
	 * Touching the tap values is a bit tricky on some SoC generations.
	 * The quirk enables a workaround for a glitch that sometimes occurs if
	 * the tap values are changed.
	 */

	if (soc_data->nvquirks & NVQUIRK_DIS_CARD_CLK_CONFIG_TAP)
		card_clk_enabled = tegra_sdhci_configure_card_clk(host, false);

	reg = sdhci_readl(host, SDHCI_TEGRA_VENDOR_CLOCK_CTRL);
	reg &= ~SDHCI_CLOCK_CTRL_TAP_MASK;
	reg |= tap << SDHCI_CLOCK_CTRL_TAP_SHIFT;
	sdhci_writel(host, reg, SDHCI_TEGRA_VENDOR_CLOCK_CTRL);

	if (soc_data->nvquirks & NVQUIRK_DIS_CARD_CLK_CONFIG_TAP &&
	    card_clk_enabled) {
		udelay(1);
		sdhci_reset(host, SDHCI_RESET_CMD | SDHCI_RESET_DATA);
		tegra_sdhci_configure_card_clk(host, card_clk_enabled);
	}
}