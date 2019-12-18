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
struct net_device {int dummy; } ;
struct ipoib_dev_priv {int dummy; } ;
struct ipoib_cm_rx {TYPE_1__* rx_ring; int /*<<< orphan*/  qp; } ;
struct ib_sge {int /*<<< orphan*/  addr; } ;
struct ib_recv_wr {int wr_id; } ;
struct TYPE_2__ {int /*<<< orphan*/ * skb; int /*<<< orphan*/ * mapping; } ;

/* Variables and functions */
 int IPOIB_CM_RX_SG ; 
 int IPOIB_OP_CM ; 
 int IPOIB_OP_RECV ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int ib_post_recv (int /*<<< orphan*/ ,struct ib_recv_wr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipoib_cm_dma_unmap_rx (struct ipoib_dev_priv*,int,int /*<<< orphan*/ *) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ipoib_cm_post_receive_nonsrq(struct net_device *dev,
					struct ipoib_cm_rx *rx,
					struct ib_recv_wr *wr,
					struct ib_sge *sge, int id)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);
	int i, ret;

	wr->wr_id = id | IPOIB_OP_CM | IPOIB_OP_RECV;

	for (i = 0; i < IPOIB_CM_RX_SG; ++i)
		sge[i].addr = rx->rx_ring[id].mapping[i];

	ret = ib_post_recv(rx->qp, wr, NULL);
	if (unlikely(ret)) {
		ipoib_warn(priv, "post recv failed for buf %d (%d)\n", id, ret);
		ipoib_cm_dma_unmap_rx(priv, IPOIB_CM_RX_SG - 1,
				      rx->rx_ring[id].mapping);
		dev_kfree_skb_any(rx->rx_ring[id].skb);
		rx->rx_ring[id].skb = NULL;
	}

	return ret;
}