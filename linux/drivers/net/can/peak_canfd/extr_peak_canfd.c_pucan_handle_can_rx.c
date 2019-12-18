#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct sk_buff {int dummy; } ;
struct pucan_rx_msg {int /*<<< orphan*/  d; int /*<<< orphan*/  can_id; int /*<<< orphan*/  client; int /*<<< orphan*/  flags; } ;
struct peak_canfd_priv {TYPE_1__* ndev; int /*<<< orphan*/  echo_lock; } ;
struct net_device_stats {int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; } ;
struct canfd_frame {scalar_t__ len; int /*<<< orphan*/  data; int /*<<< orphan*/  can_id; int /*<<< orphan*/  flags; } ;
struct can_frame {int dummy; } ;
struct TYPE_5__ {struct net_device_stats stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  CANFD_BRS ; 
 int /*<<< orphan*/  CANFD_ESI ; 
 int /*<<< orphan*/  CAN_EFF_FLAG ; 
 int /*<<< orphan*/  CAN_RTR_FLAG ; 
 int ENOMEM ; 
 int const PUCAN_MSG_BITRATE_SWITCH ; 
 int const PUCAN_MSG_ERROR_STATE_IND ; 
 int const PUCAN_MSG_EXT_DATA_LEN ; 
 int const PUCAN_MSG_EXT_ID ; 
 int const PUCAN_MSG_LOOPED_BACK ; 
 int const PUCAN_MSG_RTR ; 
 int const PUCAN_MSG_SELF_RECEIVE ; 
 struct sk_buff* alloc_can_skb (TYPE_1__*,struct can_frame**) ; 
 struct sk_buff* alloc_canfd_skb (TYPE_1__*,struct canfd_frame**) ; 
 scalar_t__ can_dlc2len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  can_get_echo_skb (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_can_dlc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_canfd_dlc (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_wake_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  pucan_msg_get_dlc (struct pucan_rx_msg*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int pucan_handle_can_rx(struct peak_canfd_priv *priv,
			       struct pucan_rx_msg *msg)
{
	struct net_device_stats *stats = &priv->ndev->stats;
	struct canfd_frame *cf;
	struct sk_buff *skb;
	const u16 rx_msg_flags = le16_to_cpu(msg->flags);
	u8 cf_len;

	if (rx_msg_flags & PUCAN_MSG_EXT_DATA_LEN)
		cf_len = can_dlc2len(get_canfd_dlc(pucan_msg_get_dlc(msg)));
	else
		cf_len = get_can_dlc(pucan_msg_get_dlc(msg));

	/* if this frame is an echo, */
	if ((rx_msg_flags & PUCAN_MSG_LOOPED_BACK) &&
	    !(rx_msg_flags & PUCAN_MSG_SELF_RECEIVE)) {
		unsigned long flags;

		spin_lock_irqsave(&priv->echo_lock, flags);
		can_get_echo_skb(priv->ndev, msg->client);

		/* count bytes of the echo instead of skb */
		stats->tx_bytes += cf_len;
		stats->tx_packets++;

		/* restart tx queue (a slot is free) */
		netif_wake_queue(priv->ndev);

		spin_unlock_irqrestore(&priv->echo_lock, flags);
		return 0;
	}

	/* otherwise, it should be pushed into rx fifo */
	if (rx_msg_flags & PUCAN_MSG_EXT_DATA_LEN) {
		/* CANFD frame case */
		skb = alloc_canfd_skb(priv->ndev, &cf);
		if (!skb)
			return -ENOMEM;

		if (rx_msg_flags & PUCAN_MSG_BITRATE_SWITCH)
			cf->flags |= CANFD_BRS;

		if (rx_msg_flags & PUCAN_MSG_ERROR_STATE_IND)
			cf->flags |= CANFD_ESI;
	} else {
		/* CAN 2.0 frame case */
		skb = alloc_can_skb(priv->ndev, (struct can_frame **)&cf);
		if (!skb)
			return -ENOMEM;
	}

	cf->can_id = le32_to_cpu(msg->can_id);
	cf->len = cf_len;

	if (rx_msg_flags & PUCAN_MSG_EXT_ID)
		cf->can_id |= CAN_EFF_FLAG;

	if (rx_msg_flags & PUCAN_MSG_RTR)
		cf->can_id |= CAN_RTR_FLAG;
	else
		memcpy(cf->data, msg->d, cf->len);

	stats->rx_bytes += cf->len;
	stats->rx_packets++;

	netif_rx(skb);

	return 0;
}