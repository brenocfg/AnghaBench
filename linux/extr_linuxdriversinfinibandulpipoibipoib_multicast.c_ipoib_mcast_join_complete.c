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
struct TYPE_6__ {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {TYPE_3__ stats; } ;
struct TYPE_4__ {int /*<<< orphan*/  raw; } ;
struct TYPE_5__ {TYPE_1__ mgid; } ;
struct ipoib_mcast {int backoff; int logcount; int /*<<< orphan*/  done; int /*<<< orphan*/  flags; struct ib_sa_multicast* mc; int /*<<< orphan*/  pkt_queue; TYPE_2__ mcmember; int /*<<< orphan*/  delay_until; struct net_device* dev; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  carrier_on_task; int /*<<< orphan*/  wq; struct ipoib_mcast* broadcast; } ;
struct ib_sa_multicast {int /*<<< orphan*/  rec; struct ipoib_mcast* context; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int ENETRESET ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  IPOIB_MCAST_FLAG_BUSY ; 
 int /*<<< orphan*/  IPOIB_MCAST_FLAG_SENDONLY ; 
 int /*<<< orphan*/  __ipoib_mcast_schedule_join_thread (struct ipoib_dev_priv*,struct ipoib_mcast*,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_dbg_mcast (struct ipoib_dev_priv*,char*,char*,int /*<<< orphan*/ ,int) ; 
 int ipoib_mcast_join_finish (struct ipoib_mcast*,int /*<<< orphan*/ *) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  netif_tx_lock_bh (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_unlock_bh (struct net_device*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipoib_mcast_join_complete(int status,
				     struct ib_sa_multicast *multicast)
{
	struct ipoib_mcast *mcast = multicast->context;
	struct net_device *dev = mcast->dev;
	struct ipoib_dev_priv *priv = ipoib_priv(dev);

	ipoib_dbg_mcast(priv, "%sjoin completion for %pI6 (status %d)\n",
			test_bit(IPOIB_MCAST_FLAG_SENDONLY, &mcast->flags) ?
			"sendonly " : "",
			mcast->mcmember.mgid.raw, status);

	/* We trap for port events ourselves. */
	if (status == -ENETRESET) {
		status = 0;
		goto out;
	}

	if (!status)
		status = ipoib_mcast_join_finish(mcast, &multicast->rec);

	if (!status) {
		mcast->backoff = 1;
		mcast->delay_until = jiffies;

		/*
		 * Defer carrier on work to priv->wq to avoid a
		 * deadlock on rtnl_lock here.  Requeue our multicast
		 * work too, which will end up happening right after
		 * our carrier on task work and will allow us to
		 * send out all of the non-broadcast joins
		 */
		if (mcast == priv->broadcast) {
			spin_lock_irq(&priv->lock);
			queue_work(priv->wq, &priv->carrier_on_task);
			__ipoib_mcast_schedule_join_thread(priv, NULL, 0);
			goto out_locked;
		}
	} else {
		bool silent_fail =
		    test_bit(IPOIB_MCAST_FLAG_SENDONLY, &mcast->flags) &&
		    status == -EINVAL;

		if (mcast->logcount < 20) {
			if (status == -ETIMEDOUT || status == -EAGAIN ||
			    silent_fail) {
				ipoib_dbg_mcast(priv, "%smulticast join failed for %pI6, status %d\n",
						test_bit(IPOIB_MCAST_FLAG_SENDONLY, &mcast->flags) ? "sendonly " : "",
						mcast->mcmember.mgid.raw, status);
			} else {
				ipoib_warn(priv, "%smulticast join failed for %pI6, status %d\n",
						test_bit(IPOIB_MCAST_FLAG_SENDONLY, &mcast->flags) ? "sendonly " : "",
					   mcast->mcmember.mgid.raw, status);
			}

			if (!silent_fail)
				mcast->logcount++;
		}

		if (test_bit(IPOIB_MCAST_FLAG_SENDONLY, &mcast->flags) &&
		    mcast->backoff >= 2) {
			/*
			 * We only retry sendonly joins once before we drop
			 * the packet and quit trying to deal with the
			 * group.  However, we leave the group in the
			 * mcast list as an unjoined group.  If we want to
			 * try joining again, we simply queue up a packet
			 * and restart the join thread.  The empty queue
			 * is why the join thread ignores this group.
			 */
			mcast->backoff = 1;
			netif_tx_lock_bh(dev);
			while (!skb_queue_empty(&mcast->pkt_queue)) {
				++dev->stats.tx_dropped;
				dev_kfree_skb_any(skb_dequeue(&mcast->pkt_queue));
			}
			netif_tx_unlock_bh(dev);
		} else {
			spin_lock_irq(&priv->lock);
			/* Requeue this join task with a backoff delay */
			__ipoib_mcast_schedule_join_thread(priv, mcast, 1);
			goto out_locked;
		}
	}
out:
	spin_lock_irq(&priv->lock);
out_locked:
	/*
	 * Make sure to set mcast->mc before we clear the busy flag to avoid
	 * racing with code that checks for BUSY before checking mcast->mc
	 */
	if (status)
		mcast->mc = NULL;
	else
		mcast->mc = multicast;
	clear_bit(IPOIB_MCAST_FLAG_BUSY, &mcast->flags);
	spin_unlock_irq(&priv->lock);
	complete(&mcast->done);

	return status;
}