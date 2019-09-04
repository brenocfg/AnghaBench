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
struct xgene_dma_chan {scalar_t__ id; int /*<<< orphan*/  dev; int /*<<< orphan*/  pdma; } ;
struct dma_device {void* pq_align; void* max_pq; int /*<<< orphan*/  device_prep_dma_pq; int /*<<< orphan*/  cap_mask; void* xor_align; void* max_xor; int /*<<< orphan*/  device_prep_dma_xor; int /*<<< orphan*/  device_tx_status; int /*<<< orphan*/  device_issue_pending; int /*<<< orphan*/  device_free_chan_resources; int /*<<< orphan*/  device_alloc_chan_resources; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 void* DMAENGINE_ALIGN_64_BYTES ; 
 int /*<<< orphan*/  DMA_PQ ; 
 int /*<<< orphan*/  DMA_XOR ; 
 void* XGENE_DMA_MAX_XOR_SRC ; 
 scalar_t__ XGENE_DMA_PQ_CHANNEL ; 
 scalar_t__ XGENE_DMA_XOR_CHANNEL ; 
 int /*<<< orphan*/  dma_cap_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_cap_zero (int /*<<< orphan*/ ) ; 
 scalar_t__ dma_has_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_pq_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgene_dma_alloc_chan_resources ; 
 int /*<<< orphan*/  xgene_dma_free_chan_resources ; 
 int /*<<< orphan*/  xgene_dma_issue_pending ; 
 int /*<<< orphan*/  xgene_dma_prep_pq ; 
 int /*<<< orphan*/  xgene_dma_prep_xor ; 
 int /*<<< orphan*/  xgene_dma_tx_status ; 

__attribute__((used)) static void xgene_dma_set_caps(struct xgene_dma_chan *chan,
			       struct dma_device *dma_dev)
{
	/* Initialize DMA device capability mask */
	dma_cap_zero(dma_dev->cap_mask);

	/* Set DMA device capability */

	/* Basically here, the X-Gene SoC DMA engine channel 0 supports XOR
	 * and channel 1 supports XOR, PQ both. First thing here is we have
	 * mechanism in hw to enable/disable PQ/XOR supports on channel 1,
	 * we can make sure this by reading SoC Efuse register.
	 * Second thing, we have hw errata that if we run channel 0 and
	 * channel 1 simultaneously with executing XOR and PQ request,
	 * suddenly DMA engine hangs, So here we enable XOR on channel 0 only
	 * if XOR and PQ supports on channel 1 is disabled.
	 */
	if ((chan->id == XGENE_DMA_PQ_CHANNEL) &&
	    is_pq_enabled(chan->pdma)) {
		dma_cap_set(DMA_PQ, dma_dev->cap_mask);
		dma_cap_set(DMA_XOR, dma_dev->cap_mask);
	} else if ((chan->id == XGENE_DMA_XOR_CHANNEL) &&
		   !is_pq_enabled(chan->pdma)) {
		dma_cap_set(DMA_XOR, dma_dev->cap_mask);
	}

	/* Set base and prep routines */
	dma_dev->dev = chan->dev;
	dma_dev->device_alloc_chan_resources = xgene_dma_alloc_chan_resources;
	dma_dev->device_free_chan_resources = xgene_dma_free_chan_resources;
	dma_dev->device_issue_pending = xgene_dma_issue_pending;
	dma_dev->device_tx_status = xgene_dma_tx_status;

	if (dma_has_cap(DMA_XOR, dma_dev->cap_mask)) {
		dma_dev->device_prep_dma_xor = xgene_dma_prep_xor;
		dma_dev->max_xor = XGENE_DMA_MAX_XOR_SRC;
		dma_dev->xor_align = DMAENGINE_ALIGN_64_BYTES;
	}

	if (dma_has_cap(DMA_PQ, dma_dev->cap_mask)) {
		dma_dev->device_prep_dma_pq = xgene_dma_prep_pq;
		dma_dev->max_pq = XGENE_DMA_MAX_XOR_SRC;
		dma_dev->pq_align = DMAENGINE_ALIGN_64_BYTES;
	}
}