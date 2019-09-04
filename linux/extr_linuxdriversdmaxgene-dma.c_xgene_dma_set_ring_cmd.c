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
struct xgene_dma_ring {scalar_t__ cmd_base; scalar_t__ cmd; scalar_t__ num; TYPE_1__* pdma; } ;
struct TYPE_2__ {scalar_t__ csr_ring_cmd; } ;

/* Variables and functions */
 scalar_t__ XGENE_DMA_RING_CMD_BASE_OFFSET (scalar_t__) ; 
 scalar_t__ XGENE_DMA_RING_CMD_OFFSET ; 
 scalar_t__ XGENE_DMA_RING_NUM ; 

__attribute__((used)) static void xgene_dma_set_ring_cmd(struct xgene_dma_ring *ring)
{
	ring->cmd_base = ring->pdma->csr_ring_cmd +
				XGENE_DMA_RING_CMD_BASE_OFFSET((ring->num -
							  XGENE_DMA_RING_NUM));

	ring->cmd = ring->cmd_base + XGENE_DMA_RING_CMD_OFFSET;
}