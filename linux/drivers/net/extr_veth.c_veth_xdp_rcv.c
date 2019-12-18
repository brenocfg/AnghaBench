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
struct xdp_frame {scalar_t__ len; } ;
struct veth_xdp_tx_bq {int dummy; } ;
struct TYPE_2__ {int xdp_packets; int xdp_bytes; int xdp_drops; int /*<<< orphan*/  syncp; } ;
struct veth_rq {TYPE_1__ stats; int /*<<< orphan*/  xdp_napi; int /*<<< orphan*/  xdp_ring; } ;
struct sk_buff {scalar_t__ len; } ;

/* Variables and functions */
 void* __ptr_ring_consume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ veth_is_xdp_frame (void*) ; 
 struct xdp_frame* veth_ptr_to_xdp (void*) ; 
 struct sk_buff* veth_xdp_rcv_one (struct veth_rq*,struct xdp_frame*,unsigned int*,struct veth_xdp_tx_bq*) ; 
 struct sk_buff* veth_xdp_rcv_skb (struct veth_rq*,struct sk_buff*,unsigned int*,struct veth_xdp_tx_bq*) ; 

__attribute__((used)) static int veth_xdp_rcv(struct veth_rq *rq, int budget, unsigned int *xdp_xmit,
			struct veth_xdp_tx_bq *bq)
{
	int i, done = 0, drops = 0, bytes = 0;

	for (i = 0; i < budget; i++) {
		void *ptr = __ptr_ring_consume(&rq->xdp_ring);
		unsigned int xdp_xmit_one = 0;
		struct sk_buff *skb;

		if (!ptr)
			break;

		if (veth_is_xdp_frame(ptr)) {
			struct xdp_frame *frame = veth_ptr_to_xdp(ptr);

			bytes += frame->len;
			skb = veth_xdp_rcv_one(rq, frame, &xdp_xmit_one, bq);
		} else {
			skb = ptr;
			bytes += skb->len;
			skb = veth_xdp_rcv_skb(rq, skb, &xdp_xmit_one, bq);
		}
		*xdp_xmit |= xdp_xmit_one;

		if (skb)
			napi_gro_receive(&rq->xdp_napi, skb);
		else if (!xdp_xmit_one)
			drops++;

		done++;
	}

	u64_stats_update_begin(&rq->stats.syncp);
	rq->stats.xdp_packets += done;
	rq->stats.xdp_bytes += bytes;
	rq->stats.xdp_drops += drops;
	u64_stats_update_end(&rq->stats.syncp);

	return done;
}