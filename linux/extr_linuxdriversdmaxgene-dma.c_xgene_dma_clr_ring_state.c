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
typedef  int /*<<< orphan*/  u32 ;
struct xgene_dma_ring {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int XGENE_DMA_RING_NUM_CONFIG ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgene_dma_wr_ring_state (struct xgene_dma_ring*) ; 

__attribute__((used)) static void xgene_dma_clr_ring_state(struct xgene_dma_ring *ring)
{
	memset(ring->state, 0, sizeof(u32) * XGENE_DMA_RING_NUM_CONFIG);
	xgene_dma_wr_ring_state(ring);
}