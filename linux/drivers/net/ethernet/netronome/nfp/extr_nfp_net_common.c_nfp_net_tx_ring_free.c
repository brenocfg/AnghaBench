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
struct nfp_net_tx_ring {int /*<<< orphan*/  size; int /*<<< orphan*/  dma; int /*<<< orphan*/ * txds; int /*<<< orphan*/ * txbufs; scalar_t__ cnt; struct nfp_net_r_vector* r_vec; } ;
struct nfp_net_r_vector {TYPE_1__* nfp_net; } ;
struct nfp_net_dp {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct nfp_net_dp dp; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nfp_net_tx_ring_free(struct nfp_net_tx_ring *tx_ring)
{
	struct nfp_net_r_vector *r_vec = tx_ring->r_vec;
	struct nfp_net_dp *dp = &r_vec->nfp_net->dp;

	kvfree(tx_ring->txbufs);

	if (tx_ring->txds)
		dma_free_coherent(dp->dev, tx_ring->size,
				  tx_ring->txds, tx_ring->dma);

	tx_ring->cnt = 0;
	tx_ring->txbufs = NULL;
	tx_ring->txds = NULL;
	tx_ring->dma = 0;
	tx_ring->size = 0;
}