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
struct nfp_net_rx_ring {int /*<<< orphan*/  size; int /*<<< orphan*/  dma; int /*<<< orphan*/ * rxds; int /*<<< orphan*/ * rxbufs; scalar_t__ cnt; int /*<<< orphan*/  xdp_rxq; struct nfp_net_r_vector* r_vec; } ;
struct nfp_net_r_vector {TYPE_1__* nfp_net; } ;
struct nfp_net_dp {int /*<<< orphan*/  dev; scalar_t__ netdev; } ;
struct TYPE_2__ {struct nfp_net_dp dp; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdp_rxq_info_unreg (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfp_net_rx_ring_free(struct nfp_net_rx_ring *rx_ring)
{
	struct nfp_net_r_vector *r_vec = rx_ring->r_vec;
	struct nfp_net_dp *dp = &r_vec->nfp_net->dp;

	if (dp->netdev)
		xdp_rxq_info_unreg(&rx_ring->xdp_rxq);
	kvfree(rx_ring->rxbufs);

	if (rx_ring->rxds)
		dma_free_coherent(dp->dev, rx_ring->size,
				  rx_ring->rxds, rx_ring->dma);

	rx_ring->cnt = 0;
	rx_ring->rxbufs = NULL;
	rx_ring->rxds = NULL;
	rx_ring->dma = 0;
	rx_ring->size = 0;
}