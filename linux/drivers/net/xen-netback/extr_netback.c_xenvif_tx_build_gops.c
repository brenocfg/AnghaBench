#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_16__ ;
typedef  struct TYPE_20__   TYPE_15__ ;
typedef  struct TYPE_19__   TYPE_14__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
typedef  int /*<<< orphan*/  txreq ;
struct TYPE_21__ {scalar_t__ req_cons; TYPE_9__* sring; } ;
struct xenvif_queue {scalar_t__ remaining_credit; size_t* pending_ring; struct gnttab_map_grant_ref* tx_map_ops; struct gnttab_map_grant_ref* tx_copy_ops; TYPE_16__ tx; int /*<<< orphan*/  tx_queue; int /*<<< orphan*/  pending_cons; TYPE_8__* pending_tx_info; TYPE_10__* vif; } ;
struct xen_netif_tx_request {scalar_t__ size; int flags; scalar_t__ offset; int /*<<< orphan*/  gref; } ;
struct TYPE_23__ {int type; scalar_t__ value; } ;
struct TYPE_22__ {int /*<<< orphan*/  addr; } ;
struct TYPE_24__ {TYPE_2__ hash; TYPE_1__ mcast; } ;
struct xen_netif_extra_info {TYPE_3__ u; scalar_t__ type; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct TYPE_27__ {int /*<<< orphan*/  gmfn; } ;
struct TYPE_28__ {int offset; int /*<<< orphan*/  domid; TYPE_6__ u; } ;
struct TYPE_25__ {int /*<<< orphan*/  ref; } ;
struct TYPE_26__ {int offset; int /*<<< orphan*/  domid; TYPE_4__ u; } ;
struct gnttab_map_grant_ref {unsigned int len; int /*<<< orphan*/  flags; TYPE_7__ dest; TYPE_5__ source; } ;
typedef  size_t pending_ring_idx_t ;
typedef  int /*<<< orphan*/  extras ;
typedef  enum pkt_hash_types { ____Placeholder_pkt_hash_types } pkt_hash_types ;
struct TYPE_30__ {scalar_t__ req_prod; } ;
struct TYPE_29__ {unsigned int extra_count; int /*<<< orphan*/  req; } ;
struct TYPE_20__ {size_t pending_idx; } ;
struct TYPE_19__ {int nr_frags; int /*<<< orphan*/ * frags; } ;
struct TYPE_18__ {int /*<<< orphan*/  domid; int /*<<< orphan*/  dev; } ;
typedef  void* RING_IDX ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct gnttab_map_grant_ref*) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DOMID_SELF ; 
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  GNTCOPY_source_gref ; 
 size_t INVALID_PENDING_IDX ; 
 unsigned int MAX_SKB_FRAGS ; 
 int PKT_HASH_TYPE_L3 ; 
 int PKT_HASH_TYPE_L4 ; 
 int PKT_HASH_TYPE_NONE ; 
 int /*<<< orphan*/  RING_COPY_REQUEST (TYPE_16__*,void*,struct xen_netif_tx_request*) ; 
 int RING_HAS_UNCONSUMED_REQUESTS (TYPE_16__*) ; 
 TYPE_15__* XENVIF_TX_CB (struct sk_buff*) ; 
 unsigned int XEN_NETBACK_TX_COPY_LEN ; 
 int XEN_NETBK_LEGACY_SLOTS_MAX ; 
 int XEN_NETIF_EXTRA_TYPE_GSO ; 
 int XEN_NETIF_EXTRA_TYPE_HASH ; 
 int /*<<< orphan*/  XEN_NETIF_EXTRA_TYPE_MAX ; 
 int XEN_NETIF_EXTRA_TYPE_MCAST_ADD ; 
 int XEN_NETIF_EXTRA_TYPE_MCAST_DEL ; 
 int /*<<< orphan*/  XEN_NETIF_RSP_ERROR ; 
 int /*<<< orphan*/  XEN_NETIF_RSP_OKAY ; 
 scalar_t__ XEN_NETIF_TX_RING_SIZE ; 
 int XEN_NETTXF_extra_info ; 
 int XEN_PAGE_MASK ; 
 scalar_t__ XEN_PAGE_SIZE ; 
#define  _XEN_NETIF_CTRL_HASH_TYPE_IPV4 131 
#define  _XEN_NETIF_CTRL_HASH_TYPE_IPV4_TCP 130 
#define  _XEN_NETIF_CTRL_HASH_TYPE_IPV6 129 
#define  _XEN_NETIF_CTRL_HASH_TYPE_IPV6_TCP 128 
 int /*<<< orphan*/  __skb_put (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  frag_set_pending_idx (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  make_tx_response (struct xenvif_queue*,struct xen_netif_tx_request*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct xen_netif_tx_request*,int) ; 
 int /*<<< orphan*/  memset (struct xen_netif_extra_info*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,...) ; 
 int offset_in_page (int /*<<< orphan*/ ) ; 
 size_t pending_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_tx_responses (struct xenvif_queue*) ; 
 int /*<<< orphan*/  rmb () ; 
 int skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_set_hash (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 TYPE_14__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ tx_credit_exceeded (struct xenvif_queue*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  virt_to_gfn (int /*<<< orphan*/ ) ; 
 struct sk_buff* xenvif_alloc_skb (unsigned int) ; 
 int xenvif_count_requests (struct xenvif_queue*,struct xen_netif_tx_request*,unsigned int,struct xen_netif_tx_request*,int) ; 
 int /*<<< orphan*/  xenvif_fatal_tx_err (TYPE_10__*) ; 
 int xenvif_get_extras (struct xenvif_queue*,struct xen_netif_extra_info*,unsigned int*,int) ; 
 struct gnttab_map_grant_ref* xenvif_get_requests (struct xenvif_queue*,struct sk_buff*,struct xen_netif_tx_request*,struct gnttab_map_grant_ref*,unsigned int,struct sk_buff*) ; 
 int xenvif_mcast_add (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenvif_mcast_del (TYPE_10__*,int /*<<< orphan*/ ) ; 
 scalar_t__ xenvif_set_skb_gso (TYPE_10__*,struct sk_buff*,struct xen_netif_extra_info*) ; 
 int /*<<< orphan*/  xenvif_tx_create_map_op (struct xenvif_queue*,size_t,struct xen_netif_tx_request*,unsigned int,struct gnttab_map_grant_ref*) ; 
 int /*<<< orphan*/  xenvif_tx_err (struct xenvif_queue*,struct xen_netif_tx_request*,unsigned int,void*) ; 

__attribute__((used)) static void xenvif_tx_build_gops(struct xenvif_queue *queue,
				     int budget,
				     unsigned *copy_ops,
				     unsigned *map_ops)
{
	struct gnttab_map_grant_ref *gop = queue->tx_map_ops;
	struct sk_buff *skb, *nskb;
	int ret;
	unsigned int frag_overflow;

	while (skb_queue_len(&queue->tx_queue) < budget) {
		struct xen_netif_tx_request txreq;
		struct xen_netif_tx_request txfrags[XEN_NETBK_LEGACY_SLOTS_MAX];
		struct xen_netif_extra_info extras[XEN_NETIF_EXTRA_TYPE_MAX-1];
		unsigned int extra_count;
		u16 pending_idx;
		RING_IDX idx;
		int work_to_do;
		unsigned int data_len;
		pending_ring_idx_t index;

		if (queue->tx.sring->req_prod - queue->tx.req_cons >
		    XEN_NETIF_TX_RING_SIZE) {
			netdev_err(queue->vif->dev,
				   "Impossible number of requests. "
				   "req_prod %d, req_cons %d, size %ld\n",
				   queue->tx.sring->req_prod, queue->tx.req_cons,
				   XEN_NETIF_TX_RING_SIZE);
			xenvif_fatal_tx_err(queue->vif);
			break;
		}

		work_to_do = RING_HAS_UNCONSUMED_REQUESTS(&queue->tx);
		if (!work_to_do)
			break;

		idx = queue->tx.req_cons;
		rmb(); /* Ensure that we see the request before we copy it. */
		RING_COPY_REQUEST(&queue->tx, idx, &txreq);

		/* Credit-based scheduling. */
		if (txreq.size > queue->remaining_credit &&
		    tx_credit_exceeded(queue, txreq.size))
			break;

		queue->remaining_credit -= txreq.size;

		work_to_do--;
		queue->tx.req_cons = ++idx;

		memset(extras, 0, sizeof(extras));
		extra_count = 0;
		if (txreq.flags & XEN_NETTXF_extra_info) {
			work_to_do = xenvif_get_extras(queue, extras,
						       &extra_count,
						       work_to_do);
			idx = queue->tx.req_cons;
			if (unlikely(work_to_do < 0))
				break;
		}

		if (extras[XEN_NETIF_EXTRA_TYPE_MCAST_ADD - 1].type) {
			struct xen_netif_extra_info *extra;

			extra = &extras[XEN_NETIF_EXTRA_TYPE_MCAST_ADD - 1];
			ret = xenvif_mcast_add(queue->vif, extra->u.mcast.addr);

			make_tx_response(queue, &txreq, extra_count,
					 (ret == 0) ?
					 XEN_NETIF_RSP_OKAY :
					 XEN_NETIF_RSP_ERROR);
			push_tx_responses(queue);
			continue;
		}

		if (extras[XEN_NETIF_EXTRA_TYPE_MCAST_DEL - 1].type) {
			struct xen_netif_extra_info *extra;

			extra = &extras[XEN_NETIF_EXTRA_TYPE_MCAST_DEL - 1];
			xenvif_mcast_del(queue->vif, extra->u.mcast.addr);

			make_tx_response(queue, &txreq, extra_count,
					 XEN_NETIF_RSP_OKAY);
			push_tx_responses(queue);
			continue;
		}

		ret = xenvif_count_requests(queue, &txreq, extra_count,
					    txfrags, work_to_do);
		if (unlikely(ret < 0))
			break;

		idx += ret;

		if (unlikely(txreq.size < ETH_HLEN)) {
			netdev_dbg(queue->vif->dev,
				   "Bad packet size: %d\n", txreq.size);
			xenvif_tx_err(queue, &txreq, extra_count, idx);
			break;
		}

		/* No crossing a page as the payload mustn't fragment. */
		if (unlikely((txreq.offset + txreq.size) > XEN_PAGE_SIZE)) {
			netdev_err(queue->vif->dev,
				   "txreq.offset: %u, size: %u, end: %lu\n",
				   txreq.offset, txreq.size,
				   (unsigned long)(txreq.offset&~XEN_PAGE_MASK) + txreq.size);
			xenvif_fatal_tx_err(queue->vif);
			break;
		}

		index = pending_index(queue->pending_cons);
		pending_idx = queue->pending_ring[index];

		data_len = (txreq.size > XEN_NETBACK_TX_COPY_LEN &&
			    ret < XEN_NETBK_LEGACY_SLOTS_MAX) ?
			XEN_NETBACK_TX_COPY_LEN : txreq.size;

		skb = xenvif_alloc_skb(data_len);
		if (unlikely(skb == NULL)) {
			netdev_dbg(queue->vif->dev,
				   "Can't allocate a skb in start_xmit.\n");
			xenvif_tx_err(queue, &txreq, extra_count, idx);
			break;
		}

		skb_shinfo(skb)->nr_frags = ret;
		if (data_len < txreq.size)
			skb_shinfo(skb)->nr_frags++;
		/* At this point shinfo->nr_frags is in fact the number of
		 * slots, which can be as large as XEN_NETBK_LEGACY_SLOTS_MAX.
		 */
		frag_overflow = 0;
		nskb = NULL;
		if (skb_shinfo(skb)->nr_frags > MAX_SKB_FRAGS) {
			frag_overflow = skb_shinfo(skb)->nr_frags - MAX_SKB_FRAGS;
			BUG_ON(frag_overflow > MAX_SKB_FRAGS);
			skb_shinfo(skb)->nr_frags = MAX_SKB_FRAGS;
			nskb = xenvif_alloc_skb(0);
			if (unlikely(nskb == NULL)) {
				skb_shinfo(skb)->nr_frags = 0;
				kfree_skb(skb);
				xenvif_tx_err(queue, &txreq, extra_count, idx);
				if (net_ratelimit())
					netdev_err(queue->vif->dev,
						   "Can't allocate the frag_list skb.\n");
				break;
			}
		}

		if (extras[XEN_NETIF_EXTRA_TYPE_GSO - 1].type) {
			struct xen_netif_extra_info *gso;
			gso = &extras[XEN_NETIF_EXTRA_TYPE_GSO - 1];

			if (xenvif_set_skb_gso(queue->vif, skb, gso)) {
				/* Failure in xenvif_set_skb_gso is fatal. */
				skb_shinfo(skb)->nr_frags = 0;
				kfree_skb(skb);
				kfree_skb(nskb);
				break;
			}
		}

		if (extras[XEN_NETIF_EXTRA_TYPE_HASH - 1].type) {
			struct xen_netif_extra_info *extra;
			enum pkt_hash_types type = PKT_HASH_TYPE_NONE;

			extra = &extras[XEN_NETIF_EXTRA_TYPE_HASH - 1];

			switch (extra->u.hash.type) {
			case _XEN_NETIF_CTRL_HASH_TYPE_IPV4:
			case _XEN_NETIF_CTRL_HASH_TYPE_IPV6:
				type = PKT_HASH_TYPE_L3;
				break;

			case _XEN_NETIF_CTRL_HASH_TYPE_IPV4_TCP:
			case _XEN_NETIF_CTRL_HASH_TYPE_IPV6_TCP:
				type = PKT_HASH_TYPE_L4;
				break;

			default:
				break;
			}

			if (type != PKT_HASH_TYPE_NONE)
				skb_set_hash(skb,
					     *(u32 *)extra->u.hash.value,
					     type);
		}

		XENVIF_TX_CB(skb)->pending_idx = pending_idx;

		__skb_put(skb, data_len);
		queue->tx_copy_ops[*copy_ops].source.u.ref = txreq.gref;
		queue->tx_copy_ops[*copy_ops].source.domid = queue->vif->domid;
		queue->tx_copy_ops[*copy_ops].source.offset = txreq.offset;

		queue->tx_copy_ops[*copy_ops].dest.u.gmfn =
			virt_to_gfn(skb->data);
		queue->tx_copy_ops[*copy_ops].dest.domid = DOMID_SELF;
		queue->tx_copy_ops[*copy_ops].dest.offset =
			offset_in_page(skb->data) & ~XEN_PAGE_MASK;

		queue->tx_copy_ops[*copy_ops].len = data_len;
		queue->tx_copy_ops[*copy_ops].flags = GNTCOPY_source_gref;

		(*copy_ops)++;

		if (data_len < txreq.size) {
			frag_set_pending_idx(&skb_shinfo(skb)->frags[0],
					     pending_idx);
			xenvif_tx_create_map_op(queue, pending_idx, &txreq,
						extra_count, gop);
			gop++;
		} else {
			frag_set_pending_idx(&skb_shinfo(skb)->frags[0],
					     INVALID_PENDING_IDX);
			memcpy(&queue->pending_tx_info[pending_idx].req,
			       &txreq, sizeof(txreq));
			queue->pending_tx_info[pending_idx].extra_count =
				extra_count;
		}

		queue->pending_cons++;

		gop = xenvif_get_requests(queue, skb, txfrags, gop,
				          frag_overflow, nskb);

		__skb_queue_tail(&queue->tx_queue, skb);

		queue->tx.req_cons = idx;

		if (((gop-queue->tx_map_ops) >= ARRAY_SIZE(queue->tx_map_ops)) ||
		    (*copy_ops >= ARRAY_SIZE(queue->tx_copy_ops)))
			break;
	}

	(*map_ops) = gop - queue->tx_map_ops;
	return;
}