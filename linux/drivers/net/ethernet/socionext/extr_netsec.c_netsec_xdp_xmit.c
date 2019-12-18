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
typedef  int u32 ;
struct xdp_frame {int dummy; } ;
struct netsec_priv {struct netsec_desc_ring* desc_ring; } ;
struct netsec_desc_ring {scalar_t__ xdp_xmit; int /*<<< orphan*/  lock; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t NETSEC_RING_TX ; 
 int NETSEC_XDP_TX ; 
 int XDP_XMIT_FLAGS_MASK ; 
 int XDP_XMIT_FLUSH ; 
 struct netsec_priv* netdev_priv (struct net_device*) ; 
 int netsec_xdp_queue_one (struct netsec_priv*,struct xdp_frame*,int) ; 
 int /*<<< orphan*/  netsec_xdp_ring_tx_db (struct netsec_priv*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xdp_return_frame_rx_napi (struct xdp_frame*) ; 

__attribute__((used)) static int netsec_xdp_xmit(struct net_device *ndev, int n,
			   struct xdp_frame **frames, u32 flags)
{
	struct netsec_priv *priv = netdev_priv(ndev);
	struct netsec_desc_ring *tx_ring = &priv->desc_ring[NETSEC_RING_TX];
	int drops = 0;
	int i;

	if (unlikely(flags & ~XDP_XMIT_FLAGS_MASK))
		return -EINVAL;

	spin_lock(&tx_ring->lock);
	for (i = 0; i < n; i++) {
		struct xdp_frame *xdpf = frames[i];
		int err;

		err = netsec_xdp_queue_one(priv, xdpf, true);
		if (err != NETSEC_XDP_TX) {
			xdp_return_frame_rx_napi(xdpf);
			drops++;
		} else {
			tx_ring->xdp_xmit++;
		}
	}
	spin_unlock(&tx_ring->lock);

	if (unlikely(flags & XDP_XMIT_FLUSH)) {
		netsec_xdp_ring_tx_db(priv, tx_ring->xdp_xmit);
		tx_ring->xdp_xmit = 0;
	}

	return n - drops;
}