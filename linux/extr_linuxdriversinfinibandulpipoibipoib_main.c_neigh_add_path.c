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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct rdma_netdev {int /*<<< orphan*/  (* send ) (struct net_device*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {TYPE_2__ stats; } ;
struct ipoib_path {int /*<<< orphan*/  query; TYPE_1__* ah; int /*<<< orphan*/  neigh_list; } ;
struct ipoib_neigh {int /*<<< orphan*/  queue; int /*<<< orphan*/  daddr; TYPE_1__* ah; int /*<<< orphan*/  list; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  ah; int /*<<< orphan*/  last_send; int /*<<< orphan*/  ref; scalar_t__ valid; } ;

/* Variables and functions */
 scalar_t__ IPOIB_MAX_PATH_REC_QUEUE ; 
 int /*<<< orphan*/  IPOIB_QPN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __path_add (struct net_device*,struct ipoib_path*) ; 
 struct ipoib_path* __path_find (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  ipoib_cm_create_tx (struct net_device*,struct ipoib_path*,struct ipoib_neigh*) ; 
 scalar_t__ ipoib_cm_enabled (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_cm_get (struct ipoib_neigh*) ; 
 int /*<<< orphan*/  ipoib_cm_set (struct ipoib_neigh*,int /*<<< orphan*/ ) ; 
 struct ipoib_neigh* ipoib_neigh_alloc (int /*<<< orphan*/ *,struct net_device*) ; 
 int /*<<< orphan*/  ipoib_neigh_free (struct ipoib_neigh*) ; 
 int /*<<< orphan*/  ipoib_neigh_put (struct ipoib_neigh*) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,scalar_t__) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct rdma_netdev* netdev_priv (struct net_device*) ; 
 struct ipoib_path* path_rec_create (struct net_device*,int /*<<< orphan*/ *) ; 
 scalar_t__ path_rec_start (struct net_device*,struct ipoib_path*) ; 
 int /*<<< orphan*/  push_pseudo_header (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct ipoib_neigh *neigh_add_path(struct sk_buff *skb, u8 *daddr,
					  struct net_device *dev)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);
	struct rdma_netdev *rn = netdev_priv(dev);
	struct ipoib_path *path;
	struct ipoib_neigh *neigh;
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);
	neigh = ipoib_neigh_alloc(daddr, dev);
	if (!neigh) {
		spin_unlock_irqrestore(&priv->lock, flags);
		++dev->stats.tx_dropped;
		dev_kfree_skb_any(skb);
		return NULL;
	}

	/* To avoid race condition, make sure that the
	 * neigh will be added only once.
	 */
	if (unlikely(!list_empty(&neigh->list))) {
		spin_unlock_irqrestore(&priv->lock, flags);
		return neigh;
	}

	path = __path_find(dev, daddr + 4);
	if (!path) {
		path = path_rec_create(dev, daddr + 4);
		if (!path)
			goto err_path;

		__path_add(dev, path);
	}

	list_add_tail(&neigh->list, &path->neigh_list);

	if (path->ah && path->ah->valid) {
		kref_get(&path->ah->ref);
		neigh->ah = path->ah;

		if (ipoib_cm_enabled(dev, neigh->daddr)) {
			if (!ipoib_cm_get(neigh))
				ipoib_cm_set(neigh, ipoib_cm_create_tx(dev, path, neigh));
			if (!ipoib_cm_get(neigh)) {
				ipoib_neigh_free(neigh);
				goto err_drop;
			}
			if (skb_queue_len(&neigh->queue) <
			    IPOIB_MAX_PATH_REC_QUEUE) {
				push_pseudo_header(skb, neigh->daddr);
				__skb_queue_tail(&neigh->queue, skb);
			} else {
				ipoib_warn(priv, "queue length limit %d. Packet drop.\n",
					   skb_queue_len(&neigh->queue));
				goto err_drop;
			}
		} else {
			spin_unlock_irqrestore(&priv->lock, flags);
			path->ah->last_send = rn->send(dev, skb, path->ah->ah,
						       IPOIB_QPN(daddr));
			ipoib_neigh_put(neigh);
			return NULL;
		}
	} else {
		neigh->ah  = NULL;

		if (!path->query && path_rec_start(dev, path))
			goto err_path;
		if (skb_queue_len(&neigh->queue) < IPOIB_MAX_PATH_REC_QUEUE) {
			push_pseudo_header(skb, neigh->daddr);
			__skb_queue_tail(&neigh->queue, skb);
		} else {
			goto err_drop;
		}
	}

	spin_unlock_irqrestore(&priv->lock, flags);
	ipoib_neigh_put(neigh);
	return NULL;

err_path:
	ipoib_neigh_free(neigh);
err_drop:
	++dev->stats.tx_dropped;
	dev_kfree_skb_any(skb);

	spin_unlock_irqrestore(&priv->lock, flags);
	ipoib_neigh_put(neigh);

	return NULL;
}