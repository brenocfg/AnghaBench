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
struct spear_sdhci {int /*<<< orphan*/  clk; } ;
struct sdhci_host {scalar_t__ ioaddr; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ SDHCI_INT_STATUS ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct sdhci_host* platform_get_drvdata (struct platform_device*) ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  sdhci_free_host (struct sdhci_host*) ; 
 struct spear_sdhci* sdhci_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_remove_host (struct sdhci_host*,int) ; 

__attribute__((used)) static int sdhci_remove(struct platform_device *pdev)
{
	struct sdhci_host *host = platform_get_drvdata(pdev);
	struct spear_sdhci *sdhci = sdhci_priv(host);
	int dead = 0;
	u32 scratch;

	scratch = readl(host->ioaddr + SDHCI_INT_STATUS);
	if (scratch == (u32)-1)
		dead = 1;

	sdhci_remove_host(host, dead);
	clk_disable_unprepare(sdhci->clk);
	sdhci_free_host(host);

	return 0;
}