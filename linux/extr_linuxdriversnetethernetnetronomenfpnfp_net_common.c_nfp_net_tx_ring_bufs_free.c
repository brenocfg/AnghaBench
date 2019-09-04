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
struct nfp_net_tx_ring {unsigned int cnt; TYPE_1__* txbufs; int /*<<< orphan*/  is_xdp; } ;
struct nfp_net_dp {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  frag; int /*<<< orphan*/  dma_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_net_dma_unmap_rx (struct nfp_net_dp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfp_net_tx_ring_bufs_free(struct nfp_net_dp *dp,
			  struct nfp_net_tx_ring *tx_ring)
{
	unsigned int i;

	if (!tx_ring->is_xdp)
		return;

	for (i = 0; i < tx_ring->cnt; i++) {
		if (!tx_ring->txbufs[i].frag)
			return;

		nfp_net_dma_unmap_rx(dp, tx_ring->txbufs[i].dma_addr);
		__free_page(virt_to_page(tx_ring->txbufs[i].frag));
	}
}