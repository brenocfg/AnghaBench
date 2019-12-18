#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct emac_ring_header {scalar_t__ used; scalar_t__ size; scalar_t__ dma_addr; int /*<<< orphan*/ * v_addr; } ;
struct emac_adapter {TYPE_2__* netdev; struct emac_ring_header ring_header; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device* parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (struct device*,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  emac_rx_q_bufs_free (struct emac_adapter*) ; 
 int /*<<< orphan*/  emac_tx_q_bufs_free (struct emac_adapter*) ; 

void emac_mac_rx_tx_rings_free_all(struct emac_adapter *adpt)
{
	struct emac_ring_header *ring_header = &adpt->ring_header;
	struct device *dev = adpt->netdev->dev.parent;

	emac_tx_q_bufs_free(adpt);
	emac_rx_q_bufs_free(adpt);

	dma_free_coherent(dev, ring_header->size,
			  ring_header->v_addr, ring_header->dma_addr);

	ring_header->v_addr   = NULL;
	ring_header->dma_addr = 0;
	ring_header->size     = 0;
	ring_header->used     = 0;
}