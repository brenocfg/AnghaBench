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
struct ixgbevf_ring {int /*<<< orphan*/ * desc; int /*<<< orphan*/  dma; int /*<<< orphan*/  size; int /*<<< orphan*/  dev; int /*<<< orphan*/ * rx_buffer_info; int /*<<< orphan*/  xdp_rxq; int /*<<< orphan*/ * xdp_prog; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbevf_clean_rx_ring (struct ixgbevf_ring*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdp_rxq_info_unreg (int /*<<< orphan*/ *) ; 

void ixgbevf_free_rx_resources(struct ixgbevf_ring *rx_ring)
{
	ixgbevf_clean_rx_ring(rx_ring);

	rx_ring->xdp_prog = NULL;
	xdp_rxq_info_unreg(&rx_ring->xdp_rxq);
	vfree(rx_ring->rx_buffer_info);
	rx_ring->rx_buffer_info = NULL;

	dma_free_coherent(rx_ring->dev, rx_ring->size, rx_ring->desc,
			  rx_ring->dma);

	rx_ring->desc = NULL;
}