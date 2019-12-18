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
struct xenvif_queue {int /*<<< orphan*/  rx; int /*<<< orphan*/  vif; int /*<<< orphan*/  tx; } ;
struct xen_netif_tx_sring {int dummy; } ;
typedef  struct xen_netif_tx_sring xen_netif_rx_sring ;
typedef  int /*<<< orphan*/  grant_ref_t ;

/* Variables and functions */
 int /*<<< orphan*/  BACK_RING_INIT (int /*<<< orphan*/ *,struct xen_netif_tx_sring*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  XEN_PAGE_SIZE ; 
 int xenbus_map_ring_valloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,void**) ; 
 int /*<<< orphan*/  xenvif_to_xenbus_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenvif_unmap_frontend_data_rings (struct xenvif_queue*) ; 

int xenvif_map_frontend_data_rings(struct xenvif_queue *queue,
				   grant_ref_t tx_ring_ref,
				   grant_ref_t rx_ring_ref)
{
	void *addr;
	struct xen_netif_tx_sring *txs;
	struct xen_netif_rx_sring *rxs;

	int err = -ENOMEM;

	err = xenbus_map_ring_valloc(xenvif_to_xenbus_device(queue->vif),
				     &tx_ring_ref, 1, &addr);
	if (err)
		goto err;

	txs = (struct xen_netif_tx_sring *)addr;
	BACK_RING_INIT(&queue->tx, txs, XEN_PAGE_SIZE);

	err = xenbus_map_ring_valloc(xenvif_to_xenbus_device(queue->vif),
				     &rx_ring_ref, 1, &addr);
	if (err)
		goto err;

	rxs = (struct xen_netif_rx_sring *)addr;
	BACK_RING_INIT(&queue->rx, rxs, XEN_PAGE_SIZE);

	return 0;

err:
	xenvif_unmap_frontend_data_rings(queue);
	return err;
}