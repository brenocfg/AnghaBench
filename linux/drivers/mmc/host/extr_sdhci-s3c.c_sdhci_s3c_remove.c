#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sdhci_s3c {int /*<<< orphan*/  clk_io; TYPE_1__* pdata; scalar_t__ ext_cd_irq; } ;
struct sdhci_host {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ cd_type; } ;

/* Variables and functions */
 scalar_t__ S3C_SDHCI_CD_INTERNAL ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct sdhci_s3c*) ; 
 struct sdhci_host* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdhci_free_host (struct sdhci_host*) ; 
 struct sdhci_s3c* sdhci_priv (struct sdhci_host*) ; 
 int /*<<< orphan*/  sdhci_remove_host (struct sdhci_host*,int) ; 

__attribute__((used)) static int sdhci_s3c_remove(struct platform_device *pdev)
{
	struct sdhci_host *host =  platform_get_drvdata(pdev);
	struct sdhci_s3c *sc = sdhci_priv(host);

	if (sc->ext_cd_irq)
		free_irq(sc->ext_cd_irq, sc);

#ifdef CONFIG_PM
	if (sc->pdata->cd_type != S3C_SDHCI_CD_INTERNAL)
		clk_prepare_enable(sc->clk_io);
#endif
	sdhci_remove_host(host, 1);

	pm_runtime_dont_use_autosuspend(&pdev->dev);
	pm_runtime_disable(&pdev->dev);

	clk_disable_unprepare(sc->clk_io);

	sdhci_free_host(host);

	return 0;
}