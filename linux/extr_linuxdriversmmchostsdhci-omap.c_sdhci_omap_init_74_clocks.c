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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_omap_host {scalar_t__ power_mode; } ;
struct sdhci_host {int /*<<< orphan*/  irq; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int CON_INIT ; 
 int INT_CC_EN ; 
 scalar_t__ MMC_POWER_ON ; 
 int /*<<< orphan*/  SDHCI_OMAP_CMD ; 
 int /*<<< orphan*/  SDHCI_OMAP_CON ; 
 int /*<<< orphan*/  SDHCI_OMAP_STAT ; 
 int /*<<< orphan*/  SDHCI_OMAP_TIMEOUT ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_add_ms (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ktime_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int sdhci_omap_readl (struct sdhci_omap_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_omap_writel (struct sdhci_omap_host*,int /*<<< orphan*/ ,int) ; 
 struct sdhci_omap_host* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void sdhci_omap_init_74_clocks(struct sdhci_host *host, u8 power_mode)
{
	u32 reg;
	ktime_t timeout;
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_omap_host *omap_host = sdhci_pltfm_priv(pltfm_host);

	if (omap_host->power_mode == power_mode)
		return;

	if (power_mode != MMC_POWER_ON)
		return;

	disable_irq(host->irq);

	reg = sdhci_omap_readl(omap_host, SDHCI_OMAP_CON);
	reg |= CON_INIT;
	sdhci_omap_writel(omap_host, SDHCI_OMAP_CON, reg);
	sdhci_omap_writel(omap_host, SDHCI_OMAP_CMD, 0x0);

	/* wait 1ms */
	timeout = ktime_add_ms(ktime_get(), SDHCI_OMAP_TIMEOUT);
	while (1) {
		bool timedout = ktime_after(ktime_get(), timeout);

		if (sdhci_omap_readl(omap_host, SDHCI_OMAP_STAT) & INT_CC_EN)
			break;
		if (WARN_ON(timedout))
			return;
		usleep_range(5, 10);
	}

	reg = sdhci_omap_readl(omap_host, SDHCI_OMAP_CON);
	reg &= ~CON_INIT;
	sdhci_omap_writel(omap_host, SDHCI_OMAP_CON, reg);
	sdhci_omap_writel(omap_host, SDHCI_OMAP_STAT, INT_CC_EN);

	enable_irq(host->irq);
}