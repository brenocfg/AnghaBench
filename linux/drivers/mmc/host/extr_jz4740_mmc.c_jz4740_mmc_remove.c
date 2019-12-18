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
struct jz4740_mmc_host {int /*<<< orphan*/  mmc; scalar_t__ use_dma; int /*<<< orphan*/  irq; int /*<<< orphan*/  timeout_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct jz4740_mmc_host*) ; 
 int /*<<< orphan*/  jz4740_mmc_release_dma_channels (struct jz4740_mmc_host*) ; 
 int /*<<< orphan*/  jz4740_mmc_reset (struct jz4740_mmc_host*) ; 
 int /*<<< orphan*/  jz4740_mmc_set_irq_enabled (struct jz4740_mmc_host*,int,int) ; 
 int /*<<< orphan*/  mmc_free_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmc_remove_host (int /*<<< orphan*/ ) ; 
 struct jz4740_mmc_host* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int jz4740_mmc_remove(struct platform_device *pdev)
{
	struct jz4740_mmc_host *host = platform_get_drvdata(pdev);

	del_timer_sync(&host->timeout_timer);
	jz4740_mmc_set_irq_enabled(host, 0xff, false);
	jz4740_mmc_reset(host);

	mmc_remove_host(host->mmc);

	free_irq(host->irq, host);

	if (host->use_dma)
		jz4740_mmc_release_dma_channels(host);

	mmc_free_host(host->mmc);

	return 0;
}