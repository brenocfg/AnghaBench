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
struct sdhci_host {scalar_t__ ioaddr; } ;
struct platform_device {int dummy; } ;
struct f_sdhost_priv {int /*<<< orphan*/  clk; int /*<<< orphan*/  clk_iface; } ;

/* Variables and functions */
 scalar_t__ SDHCI_INT_STATUS ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct sdhci_host* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  sdhci_free_host (struct sdhci_host*) ; 
 struct f_sdhost_priv* sdhci_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_remove_host (struct sdhci_host*,int) ; 

__attribute__((used)) static int sdhci_f_sdh30_remove(struct platform_device *pdev)
{
	struct sdhci_host *host = platform_get_drvdata(pdev);
	struct f_sdhost_priv *priv = sdhci_priv(host);

	sdhci_remove_host(host, readl(host->ioaddr + SDHCI_INT_STATUS) ==
			  0xffffffff);

	clk_disable_unprepare(priv->clk_iface);
	clk_disable_unprepare(priv->clk);

	sdhci_free_host(host);
	platform_set_drvdata(pdev, NULL);

	return 0;
}