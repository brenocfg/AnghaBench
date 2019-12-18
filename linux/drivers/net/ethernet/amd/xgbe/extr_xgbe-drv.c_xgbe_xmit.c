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
struct xgbe_packet_data {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rdesc_count; } ;
struct xgbe_ring {struct xgbe_packet_data packet_data; } ;
struct xgbe_desc_if {int /*<<< orphan*/  (* map_tx_skb ) (struct xgbe_channel*,struct sk_buff*) ;} ;
struct xgbe_hw_if {int /*<<< orphan*/  (* dev_xmit ) (struct xgbe_channel*) ;} ;
struct xgbe_prv_data {struct xgbe_channel** channel; struct xgbe_desc_if desc_if; struct xgbe_hw_if hw_if; } ;
struct xgbe_channel {struct xgbe_ring* tx_ring; int /*<<< orphan*/  queue_index; } ;
struct sk_buff {scalar_t__ len; size_t queue_mapping; } ;
struct netdev_queue {int dummy; } ;
struct net_device {int dummy; } ;
typedef  scalar_t__ netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPR (char*,scalar_t__) ; 
 scalar_t__ NETDEV_TX_OK ; 
 int /*<<< orphan*/  XGBE_TX_MAX_DESCS ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct xgbe_packet_data*,int /*<<< orphan*/ ,int) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int /*<<< orphan*/ ) ; 
 struct xgbe_prv_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_tx_sent_queue (struct netdev_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_err (struct xgbe_prv_data*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 scalar_t__ netif_msg_pktdata (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  stub1 (struct xgbe_channel*,struct sk_buff*) ; 
 int /*<<< orphan*/  stub2 (struct xgbe_channel*) ; 
 int /*<<< orphan*/  tx_err ; 
 scalar_t__ xgbe_maybe_stop_tx_queue (struct xgbe_channel*,struct xgbe_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xgbe_packet_info (struct xgbe_prv_data*,struct xgbe_ring*,struct sk_buff*,struct xgbe_packet_data*) ; 
 scalar_t__ xgbe_prep_tso (struct sk_buff*,struct xgbe_packet_data*) ; 
 int /*<<< orphan*/  xgbe_prep_tx_tstamp (struct xgbe_prv_data*,struct sk_buff*,struct xgbe_packet_data*) ; 
 int /*<<< orphan*/  xgbe_prep_vlan (struct sk_buff*,struct xgbe_packet_data*) ; 
 int /*<<< orphan*/  xgbe_print_pkt (struct net_device*,struct sk_buff*,int) ; 

__attribute__((used)) static netdev_tx_t xgbe_xmit(struct sk_buff *skb, struct net_device *netdev)
{
	struct xgbe_prv_data *pdata = netdev_priv(netdev);
	struct xgbe_hw_if *hw_if = &pdata->hw_if;
	struct xgbe_desc_if *desc_if = &pdata->desc_if;
	struct xgbe_channel *channel;
	struct xgbe_ring *ring;
	struct xgbe_packet_data *packet;
	struct netdev_queue *txq;
	netdev_tx_t ret;

	DBGPR("-->xgbe_xmit: skb->len = %d\n", skb->len);

	channel = pdata->channel[skb->queue_mapping];
	txq = netdev_get_tx_queue(netdev, channel->queue_index);
	ring = channel->tx_ring;
	packet = &ring->packet_data;

	ret = NETDEV_TX_OK;

	if (skb->len == 0) {
		netif_err(pdata, tx_err, netdev,
			  "empty skb received from stack\n");
		dev_kfree_skb_any(skb);
		goto tx_netdev_return;
	}

	/* Calculate preliminary packet info */
	memset(packet, 0, sizeof(*packet));
	xgbe_packet_info(pdata, ring, skb, packet);

	/* Check that there are enough descriptors available */
	ret = xgbe_maybe_stop_tx_queue(channel, ring, packet->rdesc_count);
	if (ret)
		goto tx_netdev_return;

	ret = xgbe_prep_tso(skb, packet);
	if (ret) {
		netif_err(pdata, tx_err, netdev,
			  "error processing TSO packet\n");
		dev_kfree_skb_any(skb);
		goto tx_netdev_return;
	}
	xgbe_prep_vlan(skb, packet);

	if (!desc_if->map_tx_skb(channel, skb)) {
		dev_kfree_skb_any(skb);
		goto tx_netdev_return;
	}

	xgbe_prep_tx_tstamp(pdata, skb, packet);

	/* Report on the actual number of bytes (to be) sent */
	netdev_tx_sent_queue(txq, packet->tx_bytes);

	/* Configure required descriptor fields for transmission */
	hw_if->dev_xmit(channel);

	if (netif_msg_pktdata(pdata))
		xgbe_print_pkt(netdev, skb, true);

	/* Stop the queue in advance if there may not be enough descriptors */
	xgbe_maybe_stop_tx_queue(channel, ring, XGBE_TX_MAX_DESCS);

	ret = NETDEV_TX_OK;

tx_netdev_return:
	return ret;
}