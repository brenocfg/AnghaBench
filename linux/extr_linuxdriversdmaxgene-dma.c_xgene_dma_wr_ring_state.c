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
struct xgene_dma_ring {TYPE_1__* pdma; int /*<<< orphan*/ * state; int /*<<< orphan*/  num; } ;
struct TYPE_2__ {scalar_t__ csr_ring; } ;

/* Variables and functions */
 int XGENE_DMA_RING_NUM_CONFIG ; 
 scalar_t__ XGENE_DMA_RING_STATE ; 
 scalar_t__ XGENE_DMA_RING_STATE_WR_BASE ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void xgene_dma_wr_ring_state(struct xgene_dma_ring *ring)
{
	int i;

	iowrite32(ring->num, ring->pdma->csr_ring + XGENE_DMA_RING_STATE);

	for (i = 0; i < XGENE_DMA_RING_NUM_CONFIG; i++)
		iowrite32(ring->state[i], ring->pdma->csr_ring +
			  XGENE_DMA_RING_STATE_WR_BASE + (i * 4));
}