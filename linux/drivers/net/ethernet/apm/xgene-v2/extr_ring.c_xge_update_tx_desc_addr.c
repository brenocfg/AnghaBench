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
struct xge_pdata {struct xge_desc_ring* tx_ring; } ;
struct xge_desc_ring {scalar_t__ tail; scalar_t__ head; int /*<<< orphan*/  dma_addr; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMATXDESCH ; 
 int /*<<< orphan*/  DMATXDESCL ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xge_wr_csr (struct xge_pdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void xge_update_tx_desc_addr(struct xge_pdata *pdata)
{
	struct xge_desc_ring *ring = pdata->tx_ring;
	dma_addr_t dma_addr = ring->dma_addr;

	xge_wr_csr(pdata, DMATXDESCL, dma_addr);
	xge_wr_csr(pdata, DMATXDESCH, upper_32_bits(dma_addr));

	ring->head = 0;
	ring->tail = 0;
}