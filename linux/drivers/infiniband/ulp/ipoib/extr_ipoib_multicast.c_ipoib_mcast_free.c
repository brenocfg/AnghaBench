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
struct TYPE_4__ {int tx_dropped; } ;
struct net_device {TYPE_1__ stats; } ;
struct TYPE_5__ {int /*<<< orphan*/  raw; } ;
struct TYPE_6__ {TYPE_2__ mgid; } ;
struct ipoib_mcast {int /*<<< orphan*/  pkt_queue; scalar_t__ ah; TYPE_3__ mcmember; struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_dbg_mcast (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_del_neighs_by_gid (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_put_ah (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct ipoib_mcast*) ; 
 int /*<<< orphan*/  netif_tx_lock_bh (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_unlock_bh (struct net_device*) ; 
 int /*<<< orphan*/  skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipoib_mcast_free(struct ipoib_mcast *mcast)
{
	struct net_device *dev = mcast->dev;
	int tx_dropped = 0;

	ipoib_dbg_mcast(ipoib_priv(dev), "deleting multicast group %pI6\n",
			mcast->mcmember.mgid.raw);

	/* remove all neigh connected to this mcast */
	ipoib_del_neighs_by_gid(dev, mcast->mcmember.mgid.raw);

	if (mcast->ah)
		ipoib_put_ah(mcast->ah);

	while (!skb_queue_empty(&mcast->pkt_queue)) {
		++tx_dropped;
		dev_kfree_skb_any(skb_dequeue(&mcast->pkt_queue));
	}

	netif_tx_lock_bh(dev);
	dev->stats.tx_dropped += tx_dropped;
	netif_tx_unlock_bh(dev);

	kfree(mcast);
}