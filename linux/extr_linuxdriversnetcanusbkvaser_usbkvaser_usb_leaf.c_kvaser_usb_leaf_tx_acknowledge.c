#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct sk_buff {int dummy; } ;
struct net_device_stats {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct kvaser_usb_tx_urb_context {size_t echo_index; scalar_t__ dlc; } ;
struct TYPE_15__ {int /*<<< orphan*/  restarts; } ;
struct TYPE_16__ {scalar_t__ state; TYPE_4__ can_stats; scalar_t__ restart_ms; } ;
struct kvaser_usb_net_priv {int /*<<< orphan*/  tx_contexts_lock; TYPE_6__* netdev; int /*<<< orphan*/  active_tx_contexts; TYPE_5__ can; struct kvaser_usb_tx_urb_context* tx_contexts; } ;
struct kvaser_usb {size_t nchannels; size_t max_tx_urbs; struct kvaser_usb_net_priv** nets; TYPE_3__* intf; } ;
struct TYPE_12__ {size_t channel; size_t tid; } ;
struct TYPE_13__ {TYPE_1__ tx_acknowledge_header; } ;
struct kvaser_cmd {TYPE_2__ u; } ;
struct can_frame {scalar_t__ can_dlc; int /*<<< orphan*/  can_id; } ;
struct TYPE_17__ {struct net_device_stats stats; } ;
struct TYPE_14__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_ERR_RESTARTED ; 
 scalar_t__ CAN_STATE_BUS_OFF ; 
 scalar_t__ CAN_STATE_ERROR_ACTIVE ; 
 struct sk_buff* alloc_can_err_skb (TYPE_6__*,struct can_frame**) ; 
 int /*<<< orphan*/  can_get_echo_skb (TYPE_6__*,size_t) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  netdev_err (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  netif_carrier_on (TYPE_6__*) ; 
 int /*<<< orphan*/  netif_device_present (TYPE_6__*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_wake_queue (TYPE_6__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void kvaser_usb_leaf_tx_acknowledge(const struct kvaser_usb *dev,
					   const struct kvaser_cmd *cmd)
{
	struct net_device_stats *stats;
	struct kvaser_usb_tx_urb_context *context;
	struct kvaser_usb_net_priv *priv;
	unsigned long flags;
	u8 channel, tid;

	channel = cmd->u.tx_acknowledge_header.channel;
	tid = cmd->u.tx_acknowledge_header.tid;

	if (channel >= dev->nchannels) {
		dev_err(&dev->intf->dev,
			"Invalid channel number (%d)\n", channel);
		return;
	}

	priv = dev->nets[channel];

	if (!netif_device_present(priv->netdev))
		return;

	stats = &priv->netdev->stats;

	context = &priv->tx_contexts[tid % dev->max_tx_urbs];

	/* Sometimes the state change doesn't come after a bus-off event */
	if (priv->can.restart_ms && priv->can.state >= CAN_STATE_BUS_OFF) {
		struct sk_buff *skb;
		struct can_frame *cf;

		skb = alloc_can_err_skb(priv->netdev, &cf);
		if (skb) {
			cf->can_id |= CAN_ERR_RESTARTED;

			stats->rx_packets++;
			stats->rx_bytes += cf->can_dlc;
			netif_rx(skb);
		} else {
			netdev_err(priv->netdev,
				   "No memory left for err_skb\n");
		}

		priv->can.can_stats.restarts++;
		netif_carrier_on(priv->netdev);

		priv->can.state = CAN_STATE_ERROR_ACTIVE;
	}

	stats->tx_packets++;
	stats->tx_bytes += context->dlc;

	spin_lock_irqsave(&priv->tx_contexts_lock, flags);

	can_get_echo_skb(priv->netdev, context->echo_index);
	context->echo_index = dev->max_tx_urbs;
	--priv->active_tx_contexts;
	netif_wake_queue(priv->netdev);

	spin_unlock_irqrestore(&priv->tx_contexts_lock, flags);
}