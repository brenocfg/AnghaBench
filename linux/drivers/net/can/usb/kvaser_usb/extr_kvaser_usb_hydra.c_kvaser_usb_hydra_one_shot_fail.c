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
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct net_device_stats {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  rx_dropped; } ;
struct net_device {struct net_device_stats stats; } ;
struct TYPE_5__ {int /*<<< orphan*/  arbitration_lost; } ;
struct TYPE_6__ {TYPE_2__ can_stats; } ;
struct kvaser_usb_net_priv {TYPE_3__ can; struct net_device* netdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct kvaser_cmd_ext {TYPE_1__ tx_ack; } ;
struct can_frame {scalar_t__ can_dlc; int /*<<< orphan*/  can_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_ERR_ACK ; 
 int /*<<< orphan*/  CAN_ERR_BUSERROR ; 
 int /*<<< orphan*/  CAN_ERR_LOSTARB ; 
 int KVASER_USB_HYDRA_CF_FLAG_ABL ; 
 int KVASER_USB_HYDRA_CF_FLAG_OSM_NACK ; 
 struct sk_buff* alloc_can_err_skb (struct net_device*,struct can_frame**) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 

__attribute__((used)) static void kvaser_usb_hydra_one_shot_fail(struct kvaser_usb_net_priv *priv,
					   const struct kvaser_cmd_ext *cmd)
{
	struct net_device *netdev = priv->netdev;
	struct net_device_stats *stats = &netdev->stats;
	struct can_frame *cf;
	struct sk_buff *skb;
	u32 flags;

	skb = alloc_can_err_skb(netdev, &cf);
	if (!skb) {
		stats->rx_dropped++;
		netdev_warn(netdev, "No memory left for err_skb\n");
		return;
	}

	cf->can_id |= CAN_ERR_BUSERROR;
	flags = le32_to_cpu(cmd->tx_ack.flags);

	if (flags & KVASER_USB_HYDRA_CF_FLAG_OSM_NACK)
		cf->can_id |= CAN_ERR_ACK;
	if (flags & KVASER_USB_HYDRA_CF_FLAG_ABL) {
		cf->can_id |= CAN_ERR_LOSTARB;
		priv->can.can_stats.arbitration_lost++;
	}

	stats->tx_errors++;
	stats->rx_packets++;
	stats->rx_bytes += cf->can_dlc;
	netif_rx(skb);
}