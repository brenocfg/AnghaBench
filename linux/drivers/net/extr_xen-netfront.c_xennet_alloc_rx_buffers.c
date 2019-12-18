#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct xen_netif_rx_request {unsigned short id; void* gref; } ;
struct sk_buff {int dummy; } ;
struct page {int dummy; } ;
struct TYPE_9__ {scalar_t__ req_prod_pvt; scalar_t__ rsp_cons; } ;
struct netfront_queue {int /*<<< orphan*/  rx_irq; TYPE_4__ rx; int /*<<< orphan*/  rx_refill_timer; TYPE_2__* info; void** grant_rx_ref; int /*<<< orphan*/  gref_rx_head; struct sk_buff** rx_skbs; } ;
typedef  void* grant_ref_t ;
struct TYPE_8__ {int /*<<< orphan*/ * frags; } ;
struct TYPE_7__ {TYPE_1__* xbdev; int /*<<< orphan*/  netdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  otherend_id; } ;
typedef  scalar_t__ RING_IDX ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (struct sk_buff*) ; 
 int ENOMEM ; 
 int HZ ; 
 int /*<<< orphan*/  IS_ERR_VALUE (unsigned long) ; 
 scalar_t__ NET_RX_RING_SIZE ; 
 scalar_t__ NET_RX_SLOTS_MIN ; 
 struct xen_netif_rx_request* RING_GET_REQUEST (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  RING_PUSH_REQUESTS_AND_CHECK_NOTIFY (TYPE_4__*,int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 void* gnttab_claim_grant_reference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gnttab_page_grant_foreign_access_ref_one (void*,int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notify_remote_via_irq (int /*<<< orphan*/ ) ; 
 struct page* skb_frag_page (int /*<<< orphan*/ *) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 
 struct sk_buff* xennet_alloc_one_rx_buffer (struct netfront_queue*) ; 
 unsigned short xennet_rxidx (scalar_t__) ; 

__attribute__((used)) static void xennet_alloc_rx_buffers(struct netfront_queue *queue)
{
	RING_IDX req_prod = queue->rx.req_prod_pvt;
	int notify;
	int err = 0;

	if (unlikely(!netif_carrier_ok(queue->info->netdev)))
		return;

	for (req_prod = queue->rx.req_prod_pvt;
	     req_prod - queue->rx.rsp_cons < NET_RX_RING_SIZE;
	     req_prod++) {
		struct sk_buff *skb;
		unsigned short id;
		grant_ref_t ref;
		struct page *page;
		struct xen_netif_rx_request *req;

		skb = xennet_alloc_one_rx_buffer(queue);
		if (!skb) {
			err = -ENOMEM;
			break;
		}

		id = xennet_rxidx(req_prod);

		BUG_ON(queue->rx_skbs[id]);
		queue->rx_skbs[id] = skb;

		ref = gnttab_claim_grant_reference(&queue->gref_rx_head);
		WARN_ON_ONCE(IS_ERR_VALUE((unsigned long)(int)ref));
		queue->grant_rx_ref[id] = ref;

		page = skb_frag_page(&skb_shinfo(skb)->frags[0]);

		req = RING_GET_REQUEST(&queue->rx, req_prod);
		gnttab_page_grant_foreign_access_ref_one(ref,
							 queue->info->xbdev->otherend_id,
							 page,
							 0);
		req->id = id;
		req->gref = ref;
	}

	queue->rx.req_prod_pvt = req_prod;

	/* Try again later if there are not enough requests or skb allocation
	 * failed.
	 * Enough requests is quantified as the sum of newly created slots and
	 * the unconsumed slots at the backend.
	 */
	if (req_prod - queue->rx.rsp_cons < NET_RX_SLOTS_MIN ||
	    unlikely(err)) {
		mod_timer(&queue->rx_refill_timer, jiffies + (HZ/10));
		return;
	}

	RING_PUSH_REQUESTS_AND_CHECK_NOTIFY(&queue->rx, notify);
	if (notify)
		notify_remote_via_irq(queue->rx_irq);
}