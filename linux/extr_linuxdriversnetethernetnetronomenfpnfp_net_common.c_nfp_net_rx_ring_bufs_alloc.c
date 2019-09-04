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
struct nfp_net_rx_ring {int cnt; struct nfp_net_rx_buf* rxbufs; } ;
struct nfp_net_rx_buf {int /*<<< orphan*/  frag; int /*<<< orphan*/  dma_addr; } ;
struct nfp_net_dp {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  nfp_net_rx_alloc_one (struct nfp_net_dp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_net_rx_ring_bufs_free (struct nfp_net_dp*,struct nfp_net_rx_ring*) ; 

__attribute__((used)) static int
nfp_net_rx_ring_bufs_alloc(struct nfp_net_dp *dp,
			   struct nfp_net_rx_ring *rx_ring)
{
	struct nfp_net_rx_buf *rxbufs;
	unsigned int i;

	rxbufs = rx_ring->rxbufs;

	for (i = 0; i < rx_ring->cnt - 1; i++) {
		rxbufs[i].frag = nfp_net_rx_alloc_one(dp, &rxbufs[i].dma_addr);
		if (!rxbufs[i].frag) {
			nfp_net_rx_ring_bufs_free(dp, rx_ring);
			return -ENOMEM;
		}
	}

	return 0;
}