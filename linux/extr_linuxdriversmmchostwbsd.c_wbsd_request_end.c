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
struct wbsd_host {scalar_t__ dma; int /*<<< orphan*/  lock; int /*<<< orphan*/  mmc; int /*<<< orphan*/ * mrq; } ;
struct mmc_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WBSD_IDX_DMA ; 
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  clear_dma_ff (scalar_t__) ; 
 int /*<<< orphan*/  disable_dma (scalar_t__) ; 
 int /*<<< orphan*/  mmc_request_done (int /*<<< orphan*/ ,struct mmc_request*) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wbsd_write_index (struct wbsd_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wbsd_request_end(struct wbsd_host *host, struct mmc_request *mrq)
{
	unsigned long dmaflags;

	if (host->dma >= 0) {
		/*
		 * Release ISA DMA controller.
		 */
		dmaflags = claim_dma_lock();
		disable_dma(host->dma);
		clear_dma_ff(host->dma);
		release_dma_lock(dmaflags);

		/*
		 * Disable DMA on host.
		 */
		wbsd_write_index(host, WBSD_IDX_DMA, 0);
	}

	host->mrq = NULL;

	/*
	 * MMC layer might call back into the driver so first unlock.
	 */
	spin_unlock(&host->lock);
	mmc_request_done(host->mmc, mrq);
	spin_lock(&host->lock);
}