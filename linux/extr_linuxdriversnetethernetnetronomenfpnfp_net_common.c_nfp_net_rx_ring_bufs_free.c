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
struct nfp_net_rx_ring {int cnt; TYPE_1__* rxbufs; } ;
struct nfp_net_dp {int /*<<< orphan*/  xdp_prog; } ;
struct TYPE_2__ {int /*<<< orphan*/ * frag; scalar_t__ dma_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfp_net_dma_unmap_rx (struct nfp_net_dp*,scalar_t__) ; 
 int /*<<< orphan*/  nfp_net_free_frag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfp_net_rx_ring_bufs_free(struct nfp_net_dp *dp,
			  struct nfp_net_rx_ring *rx_ring)
{
	unsigned int i;

	for (i = 0; i < rx_ring->cnt - 1; i++) {
		/* NULL skb can only happen when initial filling of the ring
		 * fails to allocate enough buffers and calls here to free
		 * already allocated ones.
		 */
		if (!rx_ring->rxbufs[i].frag)
			continue;

		nfp_net_dma_unmap_rx(dp, rx_ring->rxbufs[i].dma_addr);
		nfp_net_free_frag(rx_ring->rxbufs[i].frag, dp->xdp_prog);
		rx_ring->rxbufs[i].dma_addr = 0;
		rx_ring->rxbufs[i].frag = NULL;
	}
}