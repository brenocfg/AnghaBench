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
typedef  scalar_t__ u32 ;
struct sdhci_host {scalar_t__ ioaddr; } ;
struct platform_device {int dummy; } ;
struct pic32_sdhci_priv {int /*<<< orphan*/  sys_clk; int /*<<< orphan*/  base_clk; } ;

/* Variables and functions */
 scalar_t__ SDHCI_INT_STATUS ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct sdhci_host* platform_get_drvdata (struct platform_device*) ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  sdhci_pltfm_free (struct platform_device*) ; 
 struct pic32_sdhci_priv* sdhci_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_remove_host (struct sdhci_host*,int) ; 

__attribute__((used)) static int pic32_sdhci_remove(struct platform_device *pdev)
{
	struct sdhci_host *host = platform_get_drvdata(pdev);
	struct pic32_sdhci_priv *sdhci_pdata = sdhci_priv(host);
	u32 scratch;

	scratch = readl(host->ioaddr + SDHCI_INT_STATUS);
	sdhci_remove_host(host, scratch == (u32)~0);
	clk_disable_unprepare(sdhci_pdata->base_clk);
	clk_disable_unprepare(sdhci_pdata->sys_clk);
	sdhci_pltfm_free(pdev);

	return 0;
}