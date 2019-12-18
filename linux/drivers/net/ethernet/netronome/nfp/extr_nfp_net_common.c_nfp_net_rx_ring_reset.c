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
struct nfp_net_rx_ring {scalar_t__ wr_p; scalar_t__ rd_p; int cnt; int /*<<< orphan*/  size; int /*<<< orphan*/  rxds; TYPE_1__* rxbufs; } ;
struct TYPE_2__ {int /*<<< orphan*/ * frag; scalar_t__ dma_addr; } ;

/* Variables and functions */
 unsigned int D_IDX (struct nfp_net_rx_ring*,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nfp_net_rx_ring_reset(struct nfp_net_rx_ring *rx_ring)
{
	unsigned int wr_idx, last_idx;

	/* wr_p == rd_p means ring was never fed FL bufs.  RX rings are always
	 * kept at cnt - 1 FL bufs.
	 */
	if (rx_ring->wr_p == 0 && rx_ring->rd_p == 0)
		return;

	/* Move the empty entry to the end of the list */
	wr_idx = D_IDX(rx_ring, rx_ring->wr_p);
	last_idx = rx_ring->cnt - 1;
	rx_ring->rxbufs[wr_idx].dma_addr = rx_ring->rxbufs[last_idx].dma_addr;
	rx_ring->rxbufs[wr_idx].frag = rx_ring->rxbufs[last_idx].frag;
	rx_ring->rxbufs[last_idx].dma_addr = 0;
	rx_ring->rxbufs[last_idx].frag = NULL;

	memset(rx_ring->rxds, 0, rx_ring->size);
	rx_ring->wr_p = 0;
	rx_ring->rd_p = 0;
}