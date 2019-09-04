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
struct i40e_ring {int /*<<< orphan*/ * desc; int /*<<< orphan*/  dma; int /*<<< orphan*/  size; int /*<<< orphan*/  dev; int /*<<< orphan*/ * rx_bi; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40evf_clean_rx_ring (struct i40e_ring*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void i40evf_free_rx_resources(struct i40e_ring *rx_ring)
{
	i40evf_clean_rx_ring(rx_ring);
	kfree(rx_ring->rx_bi);
	rx_ring->rx_bi = NULL;

	if (rx_ring->desc) {
		dma_free_coherent(rx_ring->dev, rx_ring->size,
				  rx_ring->desc, rx_ring->dma);
		rx_ring->desc = NULL;
	}
}