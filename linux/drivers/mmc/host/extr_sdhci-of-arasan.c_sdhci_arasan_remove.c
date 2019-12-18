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
struct sdhci_pltfm_host {int dummy; } ;
struct sdhci_host {int dummy; } ;
struct sdhci_arasan_data {int /*<<< orphan*/  phy; scalar_t__ is_phy_on; struct clk* clk_ahb; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct clk*) ; 
 int /*<<< orphan*/  phy_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_power_off (int /*<<< orphan*/ ) ; 
 struct sdhci_host* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sdhci_arasan_unregister_sdclk (int /*<<< orphan*/ *) ; 
 struct sdhci_arasan_data* sdhci_pltfm_priv (struct sdhci_pltfm_host*) ; 
 int sdhci_pltfm_unregister (struct platform_device*) ; 
 struct sdhci_pltfm_host* sdhci_priv (struct sdhci_host*) ; 

__attribute__((used)) static int sdhci_arasan_remove(struct platform_device *pdev)
{
	int ret;
	struct sdhci_host *host = platform_get_drvdata(pdev);
	struct sdhci_pltfm_host *pltfm_host = sdhci_priv(host);
	struct sdhci_arasan_data *sdhci_arasan = sdhci_pltfm_priv(pltfm_host);
	struct clk *clk_ahb = sdhci_arasan->clk_ahb;

	if (!IS_ERR(sdhci_arasan->phy)) {
		if (sdhci_arasan->is_phy_on)
			phy_power_off(sdhci_arasan->phy);
		phy_exit(sdhci_arasan->phy);
	}

	sdhci_arasan_unregister_sdclk(&pdev->dev);

	ret = sdhci_pltfm_unregister(pdev);

	clk_disable_unprepare(clk_ahb);

	return ret;
}