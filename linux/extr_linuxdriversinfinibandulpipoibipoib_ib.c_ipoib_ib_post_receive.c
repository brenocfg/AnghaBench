#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_6__ {int wr_id; } ;
struct ipoib_dev_priv {TYPE_2__* rx_ring; TYPE_3__ rx_wr; int /*<<< orphan*/  qp; TYPE_1__* rx_sge; } ;
struct TYPE_5__ {int /*<<< orphan*/ * skb; int /*<<< orphan*/ * mapping; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int IPOIB_OP_RECV ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int ib_post_recv (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_ud_dma_unmap_rx (struct ipoib_dev_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ipoib_ib_post_receive(struct net_device *dev, int id)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);
	int ret;

	priv->rx_wr.wr_id   = id | IPOIB_OP_RECV;
	priv->rx_sge[0].addr = priv->rx_ring[id].mapping[0];
	priv->rx_sge[1].addr = priv->rx_ring[id].mapping[1];


	ret = ib_post_recv(priv->qp, &priv->rx_wr, NULL);
	if (unlikely(ret)) {
		ipoib_warn(priv, "receive failed for buf %d (%d)\n", id, ret);
		ipoib_ud_dma_unmap_rx(priv, priv->rx_ring[id].mapping);
		dev_kfree_skb_any(priv->rx_ring[id].skb);
		priv->rx_ring[id].skb = NULL;
	}

	return ret;
}