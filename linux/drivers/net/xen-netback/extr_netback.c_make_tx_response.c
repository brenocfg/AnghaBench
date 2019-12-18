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
struct TYPE_2__ {scalar_t__ rsp_prod_pvt; } ;
struct xenvif_queue {TYPE_1__ tx; } ;
struct xen_netif_tx_response {int /*<<< orphan*/  status; int /*<<< orphan*/  id; } ;
struct xen_netif_tx_request {int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  s8 ;
typedef  scalar_t__ RING_IDX ;

/* Variables and functions */
 struct xen_netif_tx_response* RING_GET_RESPONSE (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  XEN_NETIF_RSP_NULL ; 

__attribute__((used)) static void make_tx_response(struct xenvif_queue *queue,
			     struct xen_netif_tx_request *txp,
			     unsigned int extra_count,
			     s8       st)
{
	RING_IDX i = queue->tx.rsp_prod_pvt;
	struct xen_netif_tx_response *resp;

	resp = RING_GET_RESPONSE(&queue->tx, i);
	resp->id     = txp->id;
	resp->status = st;

	while (extra_count-- != 0)
		RING_GET_RESPONSE(&queue->tx, ++i)->status = XEN_NETIF_RSP_NULL;

	queue->tx.rsp_prod_pvt = ++i;
}