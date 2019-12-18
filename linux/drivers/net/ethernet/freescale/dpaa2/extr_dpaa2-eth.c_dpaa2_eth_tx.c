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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  size_t u16 ;
struct sk_buff {scalar_t__ len; scalar_t__ sk; } ;
struct rtnl_link_stats64 {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_dropped; } ;
struct netdev_queue {int dummy; } ;
struct net_device {scalar_t__ num_tc; } ;
struct dpaa2_fd {int dummy; } ;
struct dpaa2_eth_priv {int (* enqueue ) (struct dpaa2_eth_priv*,struct dpaa2_eth_fq*,struct dpaa2_fd*,scalar_t__) ;struct dpaa2_eth_fq* fq; int /*<<< orphan*/  percpu_extras; int /*<<< orphan*/  percpu_stats; } ;
struct dpaa2_eth_fq {int dummy; } ;
struct dpaa2_eth_drv_stats {int tx_portal_busy; int /*<<< orphan*/  tx_sg_bytes; int /*<<< orphan*/  tx_sg_frames; int /*<<< orphan*/  tx_reallocs; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
typedef  int /*<<< orphan*/  fd ;

/* Variables and functions */
 int DPAA2_ETH_ENQUEUE_RETRIES ; 
 int EBUSY ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int build_sg_fd (struct dpaa2_eth_priv*,struct sk_buff*,struct dpaa2_fd*) ; 
 int build_single_fd (struct dpaa2_eth_priv*,struct sk_buff*,struct dpaa2_fd*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 unsigned int dpaa2_eth_needed_headroom (struct dpaa2_eth_priv*,struct sk_buff*) ; 
 size_t dpaa2_eth_queue_count (struct dpaa2_eth_priv*) ; 
 scalar_t__ dpaa2_fd_get_len (struct dpaa2_fd*) ; 
 int /*<<< orphan*/  free_tx_fd (struct dpaa2_eth_priv*,struct dpaa2_eth_fq*,struct dpaa2_fd*,int) ; 
 int /*<<< orphan*/  memset (struct dpaa2_fd*,int /*<<< orphan*/ ,int) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,size_t) ; 
 struct dpaa2_eth_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_tx_completed_queue (struct netdev_queue*,int,scalar_t__) ; 
 int /*<<< orphan*/  netdev_tx_sent_queue (struct netdev_queue*,scalar_t__) ; 
 scalar_t__ netdev_txq_to_tc (struct net_device*,size_t) ; 
 size_t skb_get_queue_mapping (struct sk_buff*) ; 
 unsigned int skb_headroom (struct sk_buff*) ; 
 scalar_t__ skb_is_nonlinear (struct sk_buff*) ; 
 struct sk_buff* skb_realloc_headroom (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  skb_set_owner_w (struct sk_buff*,scalar_t__) ; 
 struct sk_buff* skb_unshare (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int stub1 (struct dpaa2_eth_priv*,struct dpaa2_eth_fq*,struct dpaa2_fd*,scalar_t__) ; 
 void* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_dpaa2_tx_fd (struct net_device*,struct dpaa2_fd*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static netdev_tx_t dpaa2_eth_tx(struct sk_buff *skb, struct net_device *net_dev)
{
	struct dpaa2_eth_priv *priv = netdev_priv(net_dev);
	struct dpaa2_fd fd;
	struct rtnl_link_stats64 *percpu_stats;
	struct dpaa2_eth_drv_stats *percpu_extras;
	struct dpaa2_eth_fq *fq;
	struct netdev_queue *nq;
	u16 queue_mapping;
	unsigned int needed_headroom;
	u32 fd_len;
	u8 prio = 0;
	int err, i;

	percpu_stats = this_cpu_ptr(priv->percpu_stats);
	percpu_extras = this_cpu_ptr(priv->percpu_extras);

	needed_headroom = dpaa2_eth_needed_headroom(priv, skb);
	if (skb_headroom(skb) < needed_headroom) {
		struct sk_buff *ns;

		ns = skb_realloc_headroom(skb, needed_headroom);
		if (unlikely(!ns)) {
			percpu_stats->tx_dropped++;
			goto err_alloc_headroom;
		}
		percpu_extras->tx_reallocs++;

		if (skb->sk)
			skb_set_owner_w(ns, skb->sk);

		dev_kfree_skb(skb);
		skb = ns;
	}

	/* We'll be holding a back-reference to the skb until Tx Confirmation;
	 * we don't want that overwritten by a concurrent Tx with a cloned skb.
	 */
	skb = skb_unshare(skb, GFP_ATOMIC);
	if (unlikely(!skb)) {
		/* skb_unshare() has already freed the skb */
		percpu_stats->tx_dropped++;
		return NETDEV_TX_OK;
	}

	/* Setup the FD fields */
	memset(&fd, 0, sizeof(fd));

	if (skb_is_nonlinear(skb)) {
		err = build_sg_fd(priv, skb, &fd);
		percpu_extras->tx_sg_frames++;
		percpu_extras->tx_sg_bytes += skb->len;
	} else {
		err = build_single_fd(priv, skb, &fd);
	}

	if (unlikely(err)) {
		percpu_stats->tx_dropped++;
		goto err_build_fd;
	}

	/* Tracing point */
	trace_dpaa2_tx_fd(net_dev, &fd);

	/* TxConf FQ selection relies on queue id from the stack.
	 * In case of a forwarded frame from another DPNI interface, we choose
	 * a queue affined to the same core that processed the Rx frame
	 */
	queue_mapping = skb_get_queue_mapping(skb);

	if (net_dev->num_tc) {
		prio = netdev_txq_to_tc(net_dev, queue_mapping);
		/* Hardware interprets priority level 0 as being the highest,
		 * so we need to do a reverse mapping to the netdev tc index
		 */
		prio = net_dev->num_tc - prio - 1;
		/* We have only one FQ array entry for all Tx hardware queues
		 * with the same flow id (but different priority levels)
		 */
		queue_mapping %= dpaa2_eth_queue_count(priv);
	}
	fq = &priv->fq[queue_mapping];

	fd_len = dpaa2_fd_get_len(&fd);
	nq = netdev_get_tx_queue(net_dev, queue_mapping);
	netdev_tx_sent_queue(nq, fd_len);

	/* Everything that happens after this enqueues might race with
	 * the Tx confirmation callback for this frame
	 */
	for (i = 0; i < DPAA2_ETH_ENQUEUE_RETRIES; i++) {
		err = priv->enqueue(priv, fq, &fd, prio);
		if (err != -EBUSY)
			break;
	}
	percpu_extras->tx_portal_busy += i;
	if (unlikely(err < 0)) {
		percpu_stats->tx_errors++;
		/* Clean up everything, including freeing the skb */
		free_tx_fd(priv, fq, &fd, false);
		netdev_tx_completed_queue(nq, 1, fd_len);
	} else {
		percpu_stats->tx_packets++;
		percpu_stats->tx_bytes += fd_len;
	}

	return NETDEV_TX_OK;

err_build_fd:
err_alloc_headroom:
	dev_kfree_skb(skb);

	return NETDEV_TX_OK;
}