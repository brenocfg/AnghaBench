#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {scalar_t__ len; scalar_t__ ip_summed; void* data; } ;
struct TYPE_7__ {int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_dropped; } ;
struct net_device {TYPE_3__ stats; } ;
struct ipoib_tx_buf {struct sk_buff* skb; } ;
struct TYPE_5__ {int /*<<< orphan*/  send_flags; } ;
struct TYPE_6__ {TYPE_1__ wr; } ;
struct ipoib_dev_priv {int max_send_sge; scalar_t__ mcast_mtu; int tx_head; int tx_tail; int /*<<< orphan*/  send_cq; TYPE_2__ tx_wr; int /*<<< orphan*/  ca; struct ipoib_tx_buf* tx_ring; } ;
struct ib_ah {int dummy; } ;
struct TYPE_8__ {unsigned int nr_frags; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int IB_CQ_NEXT_COMP ; 
 int IB_CQ_REPORT_MISSED_EVENTS ; 
 int /*<<< orphan*/  IB_SEND_IP_CSUM ; 
 scalar_t__ IPOIB_ENCAP_LEN ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ ib_req_notify_cq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ipoib_cm_skb_too_long (struct net_device*,struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  ipoib_dbg (struct ipoib_dev_priv*,char*) ; 
 int /*<<< orphan*/  ipoib_dbg_data (struct ipoib_dev_priv*,char*,scalar_t__,struct ib_ah*,int /*<<< orphan*/ ) ; 
 int ipoib_dma_map_tx (int /*<<< orphan*/ ,struct ipoib_tx_buf*) ; 
 int /*<<< orphan*/  ipoib_dma_unmap_tx (struct ipoib_dev_priv*,struct ipoib_tx_buf*) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int ipoib_sendq_size ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,...) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int post_send (struct ipoib_dev_priv*,int,struct ib_ah*,int /*<<< orphan*/ ,struct ipoib_tx_buf*,void*,int) ; 
 int /*<<< orphan*/  skb_dst_drop (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff*) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 scalar_t__ skb_linearize (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 TYPE_4__* skb_shinfo (struct sk_buff*) ; 
 int skb_transport_offset (struct sk_buff*) ; 
 int tcp_hdrlen (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

int ipoib_send(struct net_device *dev, struct sk_buff *skb,
	       struct ib_ah *address, u32 dqpn)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);
	struct ipoib_tx_buf *tx_req;
	int hlen, rc;
	void *phead;
	unsigned int usable_sge = priv->max_send_sge - !!skb_headlen(skb);

	if (skb_is_gso(skb)) {
		hlen = skb_transport_offset(skb) + tcp_hdrlen(skb);
		phead = skb->data;
		if (unlikely(!skb_pull(skb, hlen))) {
			ipoib_warn(priv, "linear data too small\n");
			++dev->stats.tx_dropped;
			++dev->stats.tx_errors;
			dev_kfree_skb_any(skb);
			return -1;
		}
	} else {
		if (unlikely(skb->len > priv->mcast_mtu + IPOIB_ENCAP_LEN)) {
			ipoib_warn(priv, "packet len %d (> %d) too long to send, dropping\n",
				   skb->len, priv->mcast_mtu + IPOIB_ENCAP_LEN);
			++dev->stats.tx_dropped;
			++dev->stats.tx_errors;
			ipoib_cm_skb_too_long(dev, skb, priv->mcast_mtu);
			return -1;
		}
		phead = NULL;
		hlen  = 0;
	}
	if (skb_shinfo(skb)->nr_frags > usable_sge) {
		if (skb_linearize(skb) < 0) {
			ipoib_warn(priv, "skb could not be linearized\n");
			++dev->stats.tx_dropped;
			++dev->stats.tx_errors;
			dev_kfree_skb_any(skb);
			return -1;
		}
		/* Does skb_linearize return ok without reducing nr_frags? */
		if (skb_shinfo(skb)->nr_frags > usable_sge) {
			ipoib_warn(priv, "too many frags after skb linearize\n");
			++dev->stats.tx_dropped;
			++dev->stats.tx_errors;
			dev_kfree_skb_any(skb);
			return -1;
		}
	}

	ipoib_dbg_data(priv,
		       "sending packet, length=%d address=%p dqpn=0x%06x\n",
		       skb->len, address, dqpn);

	/*
	 * We put the skb into the tx_ring _before_ we call post_send()
	 * because it's entirely possible that the completion handler will
	 * run before we execute anything after the post_send().  That
	 * means we have to make sure everything is properly recorded and
	 * our state is consistent before we call post_send().
	 */
	tx_req = &priv->tx_ring[priv->tx_head & (ipoib_sendq_size - 1)];
	tx_req->skb = skb;
	if (unlikely(ipoib_dma_map_tx(priv->ca, tx_req))) {
		++dev->stats.tx_errors;
		dev_kfree_skb_any(skb);
		return -1;
	}

	if (skb->ip_summed == CHECKSUM_PARTIAL)
		priv->tx_wr.wr.send_flags |= IB_SEND_IP_CSUM;
	else
		priv->tx_wr.wr.send_flags &= ~IB_SEND_IP_CSUM;
	/* increase the tx_head after send success, but use it for queue state */
	if (priv->tx_head - priv->tx_tail == ipoib_sendq_size - 1) {
		ipoib_dbg(priv, "TX ring full, stopping kernel net queue\n");
		netif_stop_queue(dev);
	}

	skb_orphan(skb);
	skb_dst_drop(skb);

	if (netif_queue_stopped(dev))
		if (ib_req_notify_cq(priv->send_cq, IB_CQ_NEXT_COMP |
				     IB_CQ_REPORT_MISSED_EVENTS) < 0)
			ipoib_warn(priv, "request notify on send CQ failed\n");

	rc = post_send(priv, priv->tx_head & (ipoib_sendq_size - 1),
		       address, dqpn, tx_req, phead, hlen);
	if (unlikely(rc)) {
		ipoib_warn(priv, "post_send failed, error %d\n", rc);
		++dev->stats.tx_errors;
		ipoib_dma_unmap_tx(priv, tx_req);
		dev_kfree_skb_any(skb);
		if (netif_queue_stopped(dev))
			netif_wake_queue(dev);
		rc = 0;
	} else {
		netif_trans_update(dev);

		rc = priv->tx_head;
		++priv->tx_head;
	}
	return rc;
}