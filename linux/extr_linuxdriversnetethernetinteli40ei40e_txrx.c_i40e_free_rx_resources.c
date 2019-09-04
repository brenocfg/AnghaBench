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
struct i40e_ring {int /*<<< orphan*/ * desc; int /*<<< orphan*/  dma; int /*<<< orphan*/  size; int /*<<< orphan*/  dev; int /*<<< orphan*/ * rx_bi; int /*<<< orphan*/ * xdp_prog; int /*<<< orphan*/  xdp_rxq; TYPE_1__* vsi; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ I40E_VSI_MAIN ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_clean_rx_ring (struct i40e_ring*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdp_rxq_info_unreg (int /*<<< orphan*/ *) ; 

void i40e_free_rx_resources(struct i40e_ring *rx_ring)
{
	i40e_clean_rx_ring(rx_ring);
	if (rx_ring->vsi->type == I40E_VSI_MAIN)
		xdp_rxq_info_unreg(&rx_ring->xdp_rxq);
	rx_ring->xdp_prog = NULL;
	kfree(rx_ring->rx_bi);
	rx_ring->rx_bi = NULL;

	if (rx_ring->desc) {
		dma_free_coherent(rx_ring->dev, rx_ring->size,
				  rx_ring->desc, rx_ring->dma);
		rx_ring->desc = NULL;
	}
}