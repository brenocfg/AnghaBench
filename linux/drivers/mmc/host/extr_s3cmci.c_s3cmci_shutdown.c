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
struct s3cmci_host {scalar_t__ irq_cd; int /*<<< orphan*/  clk; } ;
struct platform_device {int dummy; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct s3cmci_host*) ; 
 struct s3cmci_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_remove_host (struct mmc_host*) ; 
 struct mmc_host* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  s3cmci_cpufreq_deregister (struct s3cmci_host*) ; 
 int /*<<< orphan*/  s3cmci_debugfs_remove (struct s3cmci_host*) ; 

__attribute__((used)) static void s3cmci_shutdown(struct platform_device *pdev)
{
	struct mmc_host	*mmc = platform_get_drvdata(pdev);
	struct s3cmci_host *host = mmc_priv(mmc);

	if (host->irq_cd >= 0)
		free_irq(host->irq_cd, host);

	s3cmci_debugfs_remove(host);
	s3cmci_cpufreq_deregister(host);
	mmc_remove_host(mmc);
	clk_disable_unprepare(host->clk);
}