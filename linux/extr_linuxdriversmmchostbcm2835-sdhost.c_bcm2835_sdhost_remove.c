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
struct platform_device {int dummy; } ;
struct bcm2835_host {int /*<<< orphan*/  mmc; int /*<<< orphan*/  finish_tasklet; int /*<<< orphan*/  timer; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm2835_sdhost_set_power (struct bcm2835_host*,int) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct bcm2835_host*) ; 
 int /*<<< orphan*/  mmc_free_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_remove_host (int /*<<< orphan*/ ) ; 
 struct bcm2835_host* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm2835_sdhost_remove(struct platform_device *pdev)
{
	struct bcm2835_host *host = platform_get_drvdata(pdev);

	pr_debug("bcm2835_sdhost_remove\n");

	mmc_remove_host(host->mmc);

	bcm2835_sdhost_set_power(host, false);

	free_irq(host->irq, host);

	del_timer_sync(&host->timer);

	tasklet_kill(&host->finish_tasklet);

	mmc_free_host(host->mmc);
	platform_set_drvdata(pdev, NULL);

	pr_debug("bcm2835_sdhost_remove - OK\n");
	return 0;
}