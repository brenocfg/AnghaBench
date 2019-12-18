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
struct nfp_net_dp {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  frag; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfp_net_rx_give_one (struct nfp_net_dp*,struct nfp_net_rx_ring*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfp_net_rx_ring_fill_freelist(struct nfp_net_dp *dp,
			      struct nfp_net_rx_ring *rx_ring)
{
	unsigned int i;

	for (i = 0; i < rx_ring->cnt - 1; i++)
		nfp_net_rx_give_one(dp, rx_ring, rx_ring->rxbufs[i].frag,
				    rx_ring->rxbufs[i].dma_addr);
}