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
typedef  int /*<<< orphan*/  u32 ;
struct xdp_frame {int dummy; } ;
struct xdp_buff {int dummy; } ;
struct netsec_priv {struct netsec_desc_ring* desc_ring; } ;
struct netsec_desc_ring {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 size_t NETSEC_RING_TX ; 
 int /*<<< orphan*/  NETSEC_XDP_CONSUMED ; 
 struct xdp_frame* convert_to_xdp_frame (struct xdp_buff*) ; 
 int /*<<< orphan*/  netsec_xdp_queue_one (struct netsec_priv*,struct xdp_frame*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u32 netsec_xdp_xmit_back(struct netsec_priv *priv, struct xdp_buff *xdp)
{
	struct netsec_desc_ring *tx_ring = &priv->desc_ring[NETSEC_RING_TX];
	struct xdp_frame *xdpf = convert_to_xdp_frame(xdp);
	u32 ret;

	if (unlikely(!xdpf))
		return NETSEC_XDP_CONSUMED;

	spin_lock(&tx_ring->lock);
	ret = netsec_xdp_queue_one(priv, xdpf, false);
	spin_unlock(&tx_ring->lock);

	return ret;
}