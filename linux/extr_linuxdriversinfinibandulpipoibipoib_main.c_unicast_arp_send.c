#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct rdma_netdev {int /*<<< orphan*/  (* send ) (struct net_device*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {TYPE_2__ stats; } ;
struct ipoib_pseudo_header {scalar_t__ hwaddr; } ;
struct ipoib_path {TYPE_1__* ah; int /*<<< orphan*/  pathrec; int /*<<< orphan*/  queue; int /*<<< orphan*/  query; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  broadcast; } ;
struct TYPE_3__ {int /*<<< orphan*/  ah; int /*<<< orphan*/  last_send; int /*<<< orphan*/  valid; } ;

/* Variables and functions */
 scalar_t__ IPOIB_MAX_PATH_REC_QUEUE ; 
 int /*<<< orphan*/  IPOIB_QPN (scalar_t__) ; 
 int /*<<< orphan*/  __path_add (struct net_device*,struct ipoib_path*) ; 
 struct ipoib_path* __path_find (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  init_path_rec (struct ipoib_dev_priv*,struct ipoib_path*,scalar_t__) ; 
 int /*<<< orphan*/  ipoib_dbg (struct ipoib_dev_priv*,char*,int /*<<< orphan*/ ) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 struct rdma_netdev* netdev_priv (struct net_device*) ; 
 struct ipoib_path* path_rec_create (struct net_device*,scalar_t__) ; 
 scalar_t__ path_rec_start (struct net_device*,struct ipoib_path*) ; 
 int /*<<< orphan*/  push_pseudo_header (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  sa_path_get_dlid (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unicast_arp_send(struct sk_buff *skb, struct net_device *dev,
			     struct ipoib_pseudo_header *phdr)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);
	struct rdma_netdev *rn = netdev_priv(dev);
	struct ipoib_path *path;
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);

	/* no broadcast means that all paths are (going to be) not valid */
	if (!priv->broadcast)
		goto drop_and_unlock;

	path = __path_find(dev, phdr->hwaddr + 4);
	if (!path || !path->ah || !path->ah->valid) {
		if (!path) {
			path = path_rec_create(dev, phdr->hwaddr + 4);
			if (!path)
				goto drop_and_unlock;
			__path_add(dev, path);
		} else {
			/*
			 * make sure there are no changes in the existing
			 * path record
			 */
			init_path_rec(priv, path, phdr->hwaddr + 4);
		}
		if (!path->query && path_rec_start(dev, path)) {
			goto drop_and_unlock;
		}

		if (skb_queue_len(&path->queue) < IPOIB_MAX_PATH_REC_QUEUE) {
			push_pseudo_header(skb, phdr->hwaddr);
			__skb_queue_tail(&path->queue, skb);
			goto unlock;
		} else {
			goto drop_and_unlock;
		}
	}

	spin_unlock_irqrestore(&priv->lock, flags);
	ipoib_dbg(priv, "Send unicast ARP to %08x\n",
		  be32_to_cpu(sa_path_get_dlid(&path->pathrec)));
	path->ah->last_send = rn->send(dev, skb, path->ah->ah,
				       IPOIB_QPN(phdr->hwaddr));
	return;

drop_and_unlock:
	++dev->stats.tx_dropped;
	dev_kfree_skb_any(skb);
unlock:
	spin_unlock_irqrestore(&priv->lock, flags);
}