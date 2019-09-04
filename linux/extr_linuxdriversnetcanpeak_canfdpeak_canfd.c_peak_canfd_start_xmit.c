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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ data; } ;
struct pucan_tx_msg {int client; int /*<<< orphan*/  d; int /*<<< orphan*/  channel_dlc; void* flags; void* can_id; void* type; void* size; } ;
struct TYPE_2__ {int ctrlmode; int echo_skb_max; int /*<<< orphan*/ * echo_skb; } ;
struct peak_canfd_priv {int echo_idx; int /*<<< orphan*/  (* write_tx_msg ) (struct peak_canfd_priv*,struct pucan_tx_msg*) ;int /*<<< orphan*/  echo_lock; TYPE_1__ can; int /*<<< orphan*/  index; struct pucan_tx_msg* (* alloc_tx_msg ) (struct peak_canfd_priv*,int /*<<< orphan*/ ,int*) ;} ;
struct net_device_stats {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {struct net_device_stats stats; } ;
struct canfd_frame {int can_id; int flags; scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (scalar_t__,int) ; 
 int CANFD_BRS ; 
 int CANFD_ESI ; 
 int CANFD_MAX_DLEN ; 
 int CAN_CTRLMODE_FD ; 
 int CAN_CTRLMODE_LOOPBACK ; 
 int CAN_EFF_FLAG ; 
 int CAN_EFF_MASK ; 
 int CAN_MAX_DLEN ; 
 int CAN_RTR_FLAG ; 
 int CAN_SFF_MASK ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  PUCAN_MSG_BITRATE_SWITCH ; 
 int /*<<< orphan*/  PUCAN_MSG_CAN_TX ; 
 int /*<<< orphan*/  PUCAN_MSG_CHANNEL_DLC (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  PUCAN_MSG_ERROR_STATE_IND ; 
 int /*<<< orphan*/  PUCAN_MSG_EXT_DATA_LEN ; 
 int /*<<< orphan*/  PUCAN_MSG_EXT_ID ; 
 int /*<<< orphan*/  PUCAN_MSG_LOOPED_BACK ; 
 int /*<<< orphan*/  PUCAN_MSG_RTR ; 
 int /*<<< orphan*/  PUCAN_MSG_SELF_RECEIVE ; 
 scalar_t__ can_dropped_invalid_skb (struct net_device*,struct sk_buff*) ; 
 scalar_t__ can_is_canfd_skb (struct sk_buff*) ; 
 scalar_t__ can_len2dlc (scalar_t__) ; 
 int /*<<< orphan*/  can_put_echo_skb (struct sk_buff*,struct net_device*,int) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct peak_canfd_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct pucan_tx_msg* stub1 (struct peak_canfd_priv*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub2 (struct peak_canfd_priv*,struct pucan_tx_msg*) ; 

__attribute__((used)) static netdev_tx_t peak_canfd_start_xmit(struct sk_buff *skb,
					 struct net_device *ndev)
{
	struct peak_canfd_priv *priv = netdev_priv(ndev);
	struct net_device_stats *stats = &ndev->stats;
	struct canfd_frame *cf = (struct canfd_frame *)skb->data;
	struct pucan_tx_msg *msg;
	u16 msg_size, msg_flags;
	unsigned long flags;
	bool should_stop_tx_queue;
	int room_left;
	u8 can_dlc;

	if (can_dropped_invalid_skb(ndev, skb))
		return NETDEV_TX_OK;

	msg_size = ALIGN(sizeof(*msg) + cf->len, 4);
	msg = priv->alloc_tx_msg(priv, msg_size, &room_left);

	/* should never happen except under bus-off condition and (auto-)restart
	 * mechanism
	 */
	if (!msg) {
		stats->tx_dropped++;
		netif_stop_queue(ndev);
		return NETDEV_TX_BUSY;
	}

	msg->size = cpu_to_le16(msg_size);
	msg->type = cpu_to_le16(PUCAN_MSG_CAN_TX);
	msg_flags = 0;

	if (cf->can_id & CAN_EFF_FLAG) {
		msg_flags |= PUCAN_MSG_EXT_ID;
		msg->can_id = cpu_to_le32(cf->can_id & CAN_EFF_MASK);
	} else {
		msg->can_id = cpu_to_le32(cf->can_id & CAN_SFF_MASK);
	}

	if (can_is_canfd_skb(skb)) {
		/* CAN FD frame format */
		can_dlc = can_len2dlc(cf->len);

		msg_flags |= PUCAN_MSG_EXT_DATA_LEN;

		if (cf->flags & CANFD_BRS)
			msg_flags |= PUCAN_MSG_BITRATE_SWITCH;

		if (cf->flags & CANFD_ESI)
			msg_flags |= PUCAN_MSG_ERROR_STATE_IND;
	} else {
		/* CAN 2.0 frame format */
		can_dlc = cf->len;

		if (cf->can_id & CAN_RTR_FLAG)
			msg_flags |= PUCAN_MSG_RTR;
	}

	/* always ask loopback for echo management */
	msg_flags |= PUCAN_MSG_LOOPED_BACK;

	/* set driver specific bit to differentiate with application loopback */
	if (priv->can.ctrlmode & CAN_CTRLMODE_LOOPBACK)
		msg_flags |= PUCAN_MSG_SELF_RECEIVE;

	msg->flags = cpu_to_le16(msg_flags);
	msg->channel_dlc = PUCAN_MSG_CHANNEL_DLC(priv->index, can_dlc);
	memcpy(msg->d, cf->data, cf->len);

	/* struct msg client field is used as an index in the echo skbs ring */
	msg->client = priv->echo_idx;

	spin_lock_irqsave(&priv->echo_lock, flags);

	/* prepare and save echo skb in internal slot */
	can_put_echo_skb(skb, ndev, priv->echo_idx);

	/* move echo index to the next slot */
	priv->echo_idx = (priv->echo_idx + 1) % priv->can.echo_skb_max;

	/* if next slot is not free, stop network queue (no slot free in echo
	 * skb ring means that the controller did not write these frames on
	 * the bus: no need to continue).
	 */
	should_stop_tx_queue = !!(priv->can.echo_skb[priv->echo_idx]);

	/* stop network tx queue if not enough room to save one more msg too */
	if (priv->can.ctrlmode & CAN_CTRLMODE_FD)
		should_stop_tx_queue |= (room_left <
					(sizeof(*msg) + CANFD_MAX_DLEN));
	else
		should_stop_tx_queue |= (room_left <
					(sizeof(*msg) + CAN_MAX_DLEN));

	if (should_stop_tx_queue)
		netif_stop_queue(ndev);

	spin_unlock_irqrestore(&priv->echo_lock, flags);

	/* write the skb on the interface */
	priv->write_tx_msg(priv, msg);

	return NETDEV_TX_OK;
}