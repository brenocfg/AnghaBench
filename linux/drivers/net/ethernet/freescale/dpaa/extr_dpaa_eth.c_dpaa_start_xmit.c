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
struct sk_buff {int dummy; } ;
struct rtnl_link_stats64 {int /*<<< orphan*/  tx_errors; } ;
struct qm_fd {int /*<<< orphan*/  cmd; } ;
struct netdev_queue {int /*<<< orphan*/  trans_start; } ;
struct net_device {int dummy; } ;
struct dpaa_priv {scalar_t__ tx_tstamp; int /*<<< orphan*/  tx_headroom; int /*<<< orphan*/  percpu_priv; } ;
struct dpaa_percpu_priv {int /*<<< orphan*/  tx_frag_skbuffs; struct rtnl_link_stats64 stats; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_2__ {scalar_t__ nr_frags; int tx_flags; } ;

/* Variables and functions */
 scalar_t__ DPAA_SGT_MAX_ENTRIES ; 
 int /*<<< orphan*/  FM_FD_CMD_UPD ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int SKBTX_HW_TSTAMP ; 
 int SKBTX_IN_PROGRESS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ __skb_linearize (struct sk_buff*) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dpaa_cleanup_tx_fd (struct dpaa_priv*,struct qm_fd*) ; 
 scalar_t__ dpaa_xmit (struct dpaa_priv*,struct rtnl_link_stats64*,int const,struct qm_fd*) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ likely (int) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int const) ; 
 struct dpaa_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  qm_fd_clear_fd (struct qm_fd*) ; 
 scalar_t__ skb_cow_head (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int skb_get_queue_mapping (struct sk_buff*) ; 
 int skb_is_nonlinear (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int skb_to_contig_fd (struct dpaa_priv*,struct sk_buff*,struct qm_fd*,int*) ; 
 int skb_to_sg_fd (struct dpaa_priv*,struct sk_buff*,struct qm_fd*) ; 
 struct dpaa_percpu_priv* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static netdev_tx_t
dpaa_start_xmit(struct sk_buff *skb, struct net_device *net_dev)
{
	const int queue_mapping = skb_get_queue_mapping(skb);
	bool nonlinear = skb_is_nonlinear(skb);
	struct rtnl_link_stats64 *percpu_stats;
	struct dpaa_percpu_priv *percpu_priv;
	struct netdev_queue *txq;
	struct dpaa_priv *priv;
	struct qm_fd fd;
	int offset = 0;
	int err = 0;

	priv = netdev_priv(net_dev);
	percpu_priv = this_cpu_ptr(priv->percpu_priv);
	percpu_stats = &percpu_priv->stats;

	qm_fd_clear_fd(&fd);

	if (!nonlinear) {
		/* We're going to store the skb backpointer at the beginning
		 * of the data buffer, so we need a privately owned skb
		 *
		 * We've made sure skb is not shared in dev->priv_flags,
		 * we need to verify the skb head is not cloned
		 */
		if (skb_cow_head(skb, priv->tx_headroom))
			goto enomem;

		WARN_ON(skb_is_nonlinear(skb));
	}

	/* MAX_SKB_FRAGS is equal or larger than our dpaa_SGT_MAX_ENTRIES;
	 * make sure we don't feed FMan with more fragments than it supports.
	 */
	if (unlikely(nonlinear &&
		     (skb_shinfo(skb)->nr_frags >= DPAA_SGT_MAX_ENTRIES))) {
		/* If the egress skb contains more fragments than we support
		 * we have no choice but to linearize it ourselves.
		 */
		if (__skb_linearize(skb))
			goto enomem;

		nonlinear = skb_is_nonlinear(skb);
	}

	if (nonlinear) {
		/* Just create a S/G fd based on the skb */
		err = skb_to_sg_fd(priv, skb, &fd);
		percpu_priv->tx_frag_skbuffs++;
	} else {
		/* Create a contig FD from this skb */
		err = skb_to_contig_fd(priv, skb, &fd, &offset);
	}
	if (unlikely(err < 0))
		goto skb_to_fd_failed;

	txq = netdev_get_tx_queue(net_dev, queue_mapping);

	/* LLTX requires to do our own update of trans_start */
	txq->trans_start = jiffies;

	if (priv->tx_tstamp && skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP) {
		fd.cmd |= cpu_to_be32(FM_FD_CMD_UPD);
		skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
	}

	if (likely(dpaa_xmit(priv, percpu_stats, queue_mapping, &fd) == 0))
		return NETDEV_TX_OK;

	dpaa_cleanup_tx_fd(priv, &fd);
skb_to_fd_failed:
enomem:
	percpu_stats->tx_errors++;
	dev_kfree_skb(skb);
	return NETDEV_TX_OK;
}