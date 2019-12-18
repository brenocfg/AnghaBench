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
typedef  int u32 ;
struct xdp_frame {unsigned int len; } ;
struct TYPE_2__ {int /*<<< orphan*/  producer_lock; } ;
struct veth_rq {TYPE_1__ xdp_ring; int /*<<< orphan*/  xdp_prog; } ;
struct veth_priv {int /*<<< orphan*/  dropped; struct veth_rq* rq; int /*<<< orphan*/  peer; } ;
struct net_device {unsigned int mtu; unsigned int hard_header_len; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 unsigned int VLAN_HLEN ; 
 int XDP_XMIT_FLAGS_MASK ; 
 int XDP_XMIT_FLUSH ; 
 scalar_t__ __ptr_ring_produce (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  __veth_xdp_flush (struct veth_rq*) ; 
 int /*<<< orphan*/  atomic64_add (int,int /*<<< orphan*/ *) ; 
 scalar_t__ likely (int) ; 
 struct veth_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rcu_access_pointer (int /*<<< orphan*/ ) ; 
 struct net_device* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 size_t veth_select_rxq (struct net_device*) ; 
 void* veth_xdp_to_ptr (struct xdp_frame*) ; 
 int /*<<< orphan*/  xdp_return_frame_rx_napi (struct xdp_frame*) ; 

__attribute__((used)) static int veth_xdp_xmit(struct net_device *dev, int n,
			 struct xdp_frame **frames, u32 flags)
{
	struct veth_priv *rcv_priv, *priv = netdev_priv(dev);
	struct net_device *rcv;
	int i, ret, drops = n;
	unsigned int max_len;
	struct veth_rq *rq;

	if (unlikely(flags & ~XDP_XMIT_FLAGS_MASK)) {
		ret = -EINVAL;
		goto drop;
	}

	rcv = rcu_dereference(priv->peer);
	if (unlikely(!rcv)) {
		ret = -ENXIO;
		goto drop;
	}

	rcv_priv = netdev_priv(rcv);
	rq = &rcv_priv->rq[veth_select_rxq(rcv)];
	/* Non-NULL xdp_prog ensures that xdp_ring is initialized on receive
	 * side. This means an XDP program is loaded on the peer and the peer
	 * device is up.
	 */
	if (!rcu_access_pointer(rq->xdp_prog)) {
		ret = -ENXIO;
		goto drop;
	}

	drops = 0;
	max_len = rcv->mtu + rcv->hard_header_len + VLAN_HLEN;

	spin_lock(&rq->xdp_ring.producer_lock);
	for (i = 0; i < n; i++) {
		struct xdp_frame *frame = frames[i];
		void *ptr = veth_xdp_to_ptr(frame);

		if (unlikely(frame->len > max_len ||
			     __ptr_ring_produce(&rq->xdp_ring, ptr))) {
			xdp_return_frame_rx_napi(frame);
			drops++;
		}
	}
	spin_unlock(&rq->xdp_ring.producer_lock);

	if (flags & XDP_XMIT_FLUSH)
		__veth_xdp_flush(rq);

	if (likely(!drops))
		return n;

	ret = n - drops;
drop:
	atomic64_add(drops, &priv->dropped);

	return ret;
}