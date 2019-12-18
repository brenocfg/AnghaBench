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
typedef  size_t u8 ;
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct rcar_can_priv {TYPE_3__* ndev; TYPE_2__* regs; } ;
struct net_device_stats {int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_dropped; } ;
struct can_frame {int can_id; size_t can_dlc; void** data; } ;
struct TYPE_7__ {struct net_device_stats stats; } ;
struct TYPE_6__ {TYPE_1__* mb; } ;
struct TYPE_5__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  dlc; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int CAN_EFF_FLAG ; 
 int CAN_EFF_MASK ; 
 int /*<<< orphan*/  CAN_LED_EVENT_RX ; 
 int CAN_RTR_FLAG ; 
 int CAN_SFF_MASK ; 
 int RCAR_CAN_IDE ; 
 int RCAR_CAN_RTR ; 
 size_t RCAR_CAN_RX_FIFO_MBX ; 
 int RCAR_CAN_SID_SHIFT ; 
 struct sk_buff* alloc_can_skb (TYPE_3__*,struct can_frame**) ; 
 int /*<<< orphan*/  can_led_event (TYPE_3__*,int /*<<< orphan*/ ) ; 
 size_t get_can_dlc (size_t) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 void* readb (int /*<<< orphan*/ *) ; 
 int readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rcar_can_rx_pkt(struct rcar_can_priv *priv)
{
	struct net_device_stats *stats = &priv->ndev->stats;
	struct can_frame *cf;
	struct sk_buff *skb;
	u32 data;
	u8 dlc;

	skb = alloc_can_skb(priv->ndev, &cf);
	if (!skb) {
		stats->rx_dropped++;
		return;
	}

	data = readl(&priv->regs->mb[RCAR_CAN_RX_FIFO_MBX].id);
	if (data & RCAR_CAN_IDE)
		cf->can_id = (data & CAN_EFF_MASK) | CAN_EFF_FLAG;
	else
		cf->can_id = (data >> RCAR_CAN_SID_SHIFT) & CAN_SFF_MASK;

	dlc = readb(&priv->regs->mb[RCAR_CAN_RX_FIFO_MBX].dlc);
	cf->can_dlc = get_can_dlc(dlc);
	if (data & RCAR_CAN_RTR) {
		cf->can_id |= CAN_RTR_FLAG;
	} else {
		for (dlc = 0; dlc < cf->can_dlc; dlc++)
			cf->data[dlc] =
			readb(&priv->regs->mb[RCAR_CAN_RX_FIFO_MBX].data[dlc]);
	}

	can_led_event(priv->ndev, CAN_LED_EVENT_RX);

	stats->rx_bytes += cf->can_dlc;
	stats->rx_packets++;
	netif_receive_skb(skb);
}