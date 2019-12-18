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
struct xenbus_device {int dummy; } ;
struct xen_netif_tx_sring {int dummy; } ;
typedef  struct xen_netif_tx_sring xen_netif_rx_sring ;
struct TYPE_2__ {int /*<<< orphan*/ * sring; } ;
struct netfront_queue {void* tx_ring_ref; void* rx_ring_ref; TYPE_1__ rx; TYPE_1__ tx; } ;
typedef  void* grant_ref_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FRONT_RING_INIT (TYPE_1__*,struct xen_netif_tx_sring*,int /*<<< orphan*/ ) ; 
 int GFP_NOIO ; 
 void* GRANT_INVALID_REF ; 
 int /*<<< orphan*/  SHARED_RING_INIT (struct xen_netif_tx_sring*) ; 
 int /*<<< orphan*/  XEN_PAGE_SIZE ; 
 int __GFP_HIGH ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 scalar_t__ get_zeroed_page (int) ; 
 int /*<<< orphan*/  gnttab_end_foreign_access_ref (void*,int /*<<< orphan*/ ) ; 
 int setup_netfront_single (struct netfront_queue*) ; 
 int setup_netfront_split (struct netfront_queue*) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (struct xenbus_device*,int,char*) ; 
 int xenbus_grant_ring (struct xenbus_device*,struct xen_netif_tx_sring*,int,void**) ; 

__attribute__((used)) static int setup_netfront(struct xenbus_device *dev,
			struct netfront_queue *queue, unsigned int feature_split_evtchn)
{
	struct xen_netif_tx_sring *txs;
	struct xen_netif_rx_sring *rxs;
	grant_ref_t gref;
	int err;

	queue->tx_ring_ref = GRANT_INVALID_REF;
	queue->rx_ring_ref = GRANT_INVALID_REF;
	queue->rx.sring = NULL;
	queue->tx.sring = NULL;

	txs = (struct xen_netif_tx_sring *)get_zeroed_page(GFP_NOIO | __GFP_HIGH);
	if (!txs) {
		err = -ENOMEM;
		xenbus_dev_fatal(dev, err, "allocating tx ring page");
		goto fail;
	}
	SHARED_RING_INIT(txs);
	FRONT_RING_INIT(&queue->tx, txs, XEN_PAGE_SIZE);

	err = xenbus_grant_ring(dev, txs, 1, &gref);
	if (err < 0)
		goto grant_tx_ring_fail;
	queue->tx_ring_ref = gref;

	rxs = (struct xen_netif_rx_sring *)get_zeroed_page(GFP_NOIO | __GFP_HIGH);
	if (!rxs) {
		err = -ENOMEM;
		xenbus_dev_fatal(dev, err, "allocating rx ring page");
		goto alloc_rx_ring_fail;
	}
	SHARED_RING_INIT(rxs);
	FRONT_RING_INIT(&queue->rx, rxs, XEN_PAGE_SIZE);

	err = xenbus_grant_ring(dev, rxs, 1, &gref);
	if (err < 0)
		goto grant_rx_ring_fail;
	queue->rx_ring_ref = gref;

	if (feature_split_evtchn)
		err = setup_netfront_split(queue);
	/* setup single event channel if
	 *  a) feature-split-event-channels == 0
	 *  b) feature-split-event-channels == 1 but failed to setup
	 */
	if (!feature_split_evtchn || (feature_split_evtchn && err))
		err = setup_netfront_single(queue);

	if (err)
		goto alloc_evtchn_fail;

	return 0;

	/* If we fail to setup netfront, it is safe to just revoke access to
	 * granted pages because backend is not accessing it at this point.
	 */
alloc_evtchn_fail:
	gnttab_end_foreign_access_ref(queue->rx_ring_ref, 0);
grant_rx_ring_fail:
	free_page((unsigned long)rxs);
alloc_rx_ring_fail:
	gnttab_end_foreign_access_ref(queue->tx_ring_ref, 0);
grant_tx_ring_fail:
	free_page((unsigned long)txs);
fail:
	return err;
}