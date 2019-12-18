#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  size_t u8 ;
struct sk_buff {int dummy; } ;
struct net_device_stats {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct kvaser_usb_net_priv {TYPE_11__* netdev; } ;
struct TYPE_19__ {int family; } ;
struct TYPE_20__ {TYPE_5__ leaf; } ;
struct kvaser_usb {size_t nchannels; TYPE_6__ card_data; struct kvaser_usb_net_priv** nets; TYPE_1__* intf; } ;
struct TYPE_23__ {size_t channel; int flag; } ;
struct TYPE_21__ {size_t const dlc; int flags; size_t const data; int /*<<< orphan*/  id; } ;
struct TYPE_16__ {size_t* data; } ;
struct TYPE_22__ {TYPE_7__ log_message; TYPE_2__ rx_can; } ;
struct TYPE_17__ {size_t* data; } ;
struct TYPE_18__ {TYPE_3__ rx_can; } ;
struct TYPE_13__ {TYPE_9__ rx_can_header; TYPE_8__ leaf; TYPE_4__ usbcan; } ;
struct kvaser_cmd {scalar_t__ id; TYPE_10__ u; } ;
struct can_frame {int can_id; void* can_dlc; int /*<<< orphan*/  data; } ;
struct TYPE_15__ {int /*<<< orphan*/  dev; } ;
struct TYPE_14__ {struct net_device_stats stats; } ;

/* Variables and functions */
 int CAN_EFF_FLAG ; 
 int CAN_EFF_MASK ; 
 int CAN_RTR_FLAG ; 
 int CAN_SFF_MASK ; 
 scalar_t__ CMD_LEAF_LOG_MESSAGE ; 
 scalar_t__ CMD_RX_EXT_MESSAGE ; 
 int KVASER_EXTENDED_FRAME ; 
#define  KVASER_LEAF 129 
#define  KVASER_USBCAN 128 
 int MSG_FLAG_ERROR_FRAME ; 
 int MSG_FLAG_NERR ; 
 int MSG_FLAG_OVERRUN ; 
 int MSG_FLAG_REMOTE_FRAME ; 
 struct sk_buff* alloc_can_skb (TYPE_11__*,struct can_frame**) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,size_t) ; 
 void* get_can_dlc (size_t const) ; 
 int /*<<< orphan*/  kvaser_usb_leaf_leaf_rx_error (struct kvaser_usb const*,struct kvaser_cmd const*) ; 
 int /*<<< orphan*/  kvaser_usb_leaf_rx_can_err (struct kvaser_usb_net_priv*,struct kvaser_cmd const*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,size_t const*,void*) ; 
 int /*<<< orphan*/  netdev_warn (TYPE_11__*,char*,int) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 

__attribute__((used)) static void kvaser_usb_leaf_rx_can_msg(const struct kvaser_usb *dev,
				       const struct kvaser_cmd *cmd)
{
	struct kvaser_usb_net_priv *priv;
	struct can_frame *cf;
	struct sk_buff *skb;
	struct net_device_stats *stats;
	u8 channel = cmd->u.rx_can_header.channel;
	const u8 *rx_data = NULL;	/* GCC */

	if (channel >= dev->nchannels) {
		dev_err(&dev->intf->dev,
			"Invalid channel number (%d)\n", channel);
		return;
	}

	priv = dev->nets[channel];
	stats = &priv->netdev->stats;

	if ((cmd->u.rx_can_header.flag & MSG_FLAG_ERROR_FRAME) &&
	    (dev->card_data.leaf.family == KVASER_LEAF &&
	     cmd->id == CMD_LEAF_LOG_MESSAGE)) {
		kvaser_usb_leaf_leaf_rx_error(dev, cmd);
		return;
	} else if (cmd->u.rx_can_header.flag & (MSG_FLAG_ERROR_FRAME |
						MSG_FLAG_NERR |
						MSG_FLAG_OVERRUN)) {
		kvaser_usb_leaf_rx_can_err(priv, cmd);
		return;
	} else if (cmd->u.rx_can_header.flag & ~MSG_FLAG_REMOTE_FRAME) {
		netdev_warn(priv->netdev,
			    "Unhandled frame (flags: 0x%02x)\n",
			    cmd->u.rx_can_header.flag);
		return;
	}

	switch (dev->card_data.leaf.family) {
	case KVASER_LEAF:
		rx_data = cmd->u.leaf.rx_can.data;
		break;
	case KVASER_USBCAN:
		rx_data = cmd->u.usbcan.rx_can.data;
		break;
	}

	skb = alloc_can_skb(priv->netdev, &cf);
	if (!skb) {
		stats->rx_dropped++;
		return;
	}

	if (dev->card_data.leaf.family == KVASER_LEAF && cmd->id ==
	    CMD_LEAF_LOG_MESSAGE) {
		cf->can_id = le32_to_cpu(cmd->u.leaf.log_message.id);
		if (cf->can_id & KVASER_EXTENDED_FRAME)
			cf->can_id &= CAN_EFF_MASK | CAN_EFF_FLAG;
		else
			cf->can_id &= CAN_SFF_MASK;

		cf->can_dlc = get_can_dlc(cmd->u.leaf.log_message.dlc);

		if (cmd->u.leaf.log_message.flags & MSG_FLAG_REMOTE_FRAME)
			cf->can_id |= CAN_RTR_FLAG;
		else
			memcpy(cf->data, &cmd->u.leaf.log_message.data,
			       cf->can_dlc);
	} else {
		cf->can_id = ((rx_data[0] & 0x1f) << 6) | (rx_data[1] & 0x3f);

		if (cmd->id == CMD_RX_EXT_MESSAGE) {
			cf->can_id <<= 18;
			cf->can_id |= ((rx_data[2] & 0x0f) << 14) |
				      ((rx_data[3] & 0xff) << 6) |
				      (rx_data[4] & 0x3f);
			cf->can_id |= CAN_EFF_FLAG;
		}

		cf->can_dlc = get_can_dlc(rx_data[5]);

		if (cmd->u.rx_can_header.flag & MSG_FLAG_REMOTE_FRAME)
			cf->can_id |= CAN_RTR_FLAG;
		else
			memcpy(cf->data, &rx_data[6], cf->can_dlc);
	}

	stats->rx_packets++;
	stats->rx_bytes += cf->can_dlc;
	netif_rx(skb);
}