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
struct mmc_omap_host {int brs_received; int /*<<< orphan*/  dma_lock; scalar_t__ dma_done; int /*<<< orphan*/  dma_in_use; } ;
struct mmc_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_omap_xfer_done (struct mmc_omap_host*,struct mmc_data*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
mmc_omap_end_of_data(struct mmc_omap_host *host, struct mmc_data *data)
{
	unsigned long flags;
	int done;

	if (!host->dma_in_use) {
		mmc_omap_xfer_done(host, data);
		return;
	}
	done = 0;
	spin_lock_irqsave(&host->dma_lock, flags);
	if (host->dma_done)
		done = 1;
	else
		host->brs_received = 1;
	spin_unlock_irqrestore(&host->dma_lock, flags);
	if (done)
		mmc_omap_xfer_done(host, data);
}