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
struct mmc_host {int dummy; } ;
struct bcm2835_host {int /*<<< orphan*/ * dma_chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm2835_reset_internal (struct bcm2835_host*) ; 
 int /*<<< orphan*/  dmaengine_terminate_sync (int /*<<< orphan*/ *) ; 
 struct bcm2835_host* mmc_priv (struct mmc_host*) ; 

__attribute__((used)) static void bcm2835_reset(struct mmc_host *mmc)
{
	struct bcm2835_host *host = mmc_priv(mmc);

	if (host->dma_chan)
		dmaengine_terminate_sync(host->dma_chan);
	host->dma_chan = NULL;
	bcm2835_reset_internal(host);
}