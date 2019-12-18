#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct net_device_stats {int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct esd_usb2_net_priv {TYPE_3__* netdev; } ;
struct TYPE_5__ {int dlc; int /*<<< orphan*/ * data; int /*<<< orphan*/  id; } ;
struct TYPE_6__ {TYPE_1__ rx; } ;
struct esd_usb2_msg {TYPE_2__ msg; } ;
struct can_frame {int can_id; int can_dlc; int /*<<< orphan*/ * data; } ;
struct TYPE_7__ {struct net_device_stats stats; } ;

/* Variables and functions */
 int CAN_EFF_FLAG ; 
 int CAN_RTR_FLAG ; 
 int ESD_EVENT ; 
 int ESD_EXTID ; 
 int ESD_IDMASK ; 
 int ESD_RTR ; 
 struct sk_buff* alloc_can_skb (TYPE_3__*,struct can_frame**) ; 
 int /*<<< orphan*/  esd_usb2_rx_event (struct esd_usb2_net_priv*,struct esd_usb2_msg*) ; 
 int get_can_dlc (int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_device_present (TYPE_3__*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 

__attribute__((used)) static void esd_usb2_rx_can_msg(struct esd_usb2_net_priv *priv,
				struct esd_usb2_msg *msg)
{
	struct net_device_stats *stats = &priv->netdev->stats;
	struct can_frame *cf;
	struct sk_buff *skb;
	int i;
	u32 id;

	if (!netif_device_present(priv->netdev))
		return;

	id = le32_to_cpu(msg->msg.rx.id);

	if (id & ESD_EVENT) {
		esd_usb2_rx_event(priv, msg);
	} else {
		skb = alloc_can_skb(priv->netdev, &cf);
		if (skb == NULL) {
			stats->rx_dropped++;
			return;
		}

		cf->can_id = id & ESD_IDMASK;
		cf->can_dlc = get_can_dlc(msg->msg.rx.dlc & ~ESD_RTR);

		if (id & ESD_EXTID)
			cf->can_id |= CAN_EFF_FLAG;

		if (msg->msg.rx.dlc & ESD_RTR) {
			cf->can_id |= CAN_RTR_FLAG;
		} else {
			for (i = 0; i < cf->can_dlc; i++)
				cf->data[i] = msg->msg.rx.data[i];
		}

		stats->rx_packets++;
		stats->rx_bytes += cf->can_dlc;
		netif_rx(skb);
	}

	return;
}