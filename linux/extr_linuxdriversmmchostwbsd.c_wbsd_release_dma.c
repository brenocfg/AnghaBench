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
struct wbsd_host {int dma; scalar_t__ dma_addr; int /*<<< orphan*/ * dma_buffer; int /*<<< orphan*/  mmc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  WBSD_DMA_SIZE ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_dma (int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmc_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wbsd_release_dma(struct wbsd_host *host)
{
	/*
	 * host->dma_addr is valid here iff host->dma_buffer is not NULL.
	 */
	if (host->dma_buffer) {
		dma_unmap_single(mmc_dev(host->mmc), host->dma_addr,
			WBSD_DMA_SIZE, DMA_BIDIRECTIONAL);
		kfree(host->dma_buffer);
	}
	if (host->dma >= 0)
		free_dma(host->dma);

	host->dma = -1;
	host->dma_buffer = NULL;
	host->dma_addr = 0;
}