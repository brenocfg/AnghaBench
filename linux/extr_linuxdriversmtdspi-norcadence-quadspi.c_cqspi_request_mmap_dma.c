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
struct cqspi_st {int /*<<< orphan*/  rx_dma_complete; int /*<<< orphan*/ * rx_chan; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  dma_cap_mask_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MEMCPY ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dma_request_chan_by_mask (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cqspi_request_mmap_dma(struct cqspi_st *cqspi)
{
	dma_cap_mask_t mask;

	dma_cap_zero(mask);
	dma_cap_set(DMA_MEMCPY, mask);

	cqspi->rx_chan = dma_request_chan_by_mask(&mask);
	if (IS_ERR(cqspi->rx_chan)) {
		dev_err(&cqspi->pdev->dev, "No Rx DMA available\n");
		cqspi->rx_chan = NULL;
	}
	init_completion(&cqspi->rx_dma_complete);
}