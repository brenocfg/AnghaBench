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
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct net_device_stats {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct net_device {struct net_device_stats stats; } ;
struct can_frame {int can_dlc; int can_id; int* data; } ;
struct c_can_priv {int (* read_reg32 ) (struct c_can_priv*,int) ;scalar_t__ type; int (* read_reg ) (struct c_can_priv*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ARB1_REG ; 
 scalar_t__ BOSCH_D_CAN ; 
 int CAN_EFF_FLAG ; 
 int CAN_EFF_MASK ; 
 int CAN_RTR_FLAG ; 
 int CAN_SFF_MASK ; 
 int C_CAN_IFACE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DATA1_REG ; 
 int ENOMEM ; 
 int IF_ARB_MSGXTD ; 
 int IF_ARB_TRANSMIT ; 
 struct sk_buff* alloc_can_skb (struct net_device*,struct can_frame**) ; 
 int get_can_dlc (int) ; 
 struct c_can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int stub1 (struct c_can_priv*,int) ; 
 int stub2 (struct c_can_priv*,int) ; 
 int stub3 (struct c_can_priv*,int) ; 

__attribute__((used)) static int c_can_read_msg_object(struct net_device *dev, int iface, u32 ctrl)
{
	struct net_device_stats *stats = &dev->stats;
	struct c_can_priv *priv = netdev_priv(dev);
	struct can_frame *frame;
	struct sk_buff *skb;
	u32 arb, data;

	skb = alloc_can_skb(dev, &frame);
	if (!skb) {
		stats->rx_dropped++;
		return -ENOMEM;
	}

	frame->can_dlc = get_can_dlc(ctrl & 0x0F);

	arb = priv->read_reg32(priv, C_CAN_IFACE(ARB1_REG, iface));

	if (arb & IF_ARB_MSGXTD)
		frame->can_id = (arb & CAN_EFF_MASK) | CAN_EFF_FLAG;
	else
		frame->can_id = (arb >> 18) & CAN_SFF_MASK;

	if (arb & IF_ARB_TRANSMIT) {
		frame->can_id |= CAN_RTR_FLAG;
	} else {
		int i, dreg = C_CAN_IFACE(DATA1_REG, iface);

		if (priv->type == BOSCH_D_CAN) {
			for (i = 0; i < frame->can_dlc; i += 4, dreg += 2) {
				data = priv->read_reg32(priv, dreg);
				frame->data[i] = data;
				frame->data[i + 1] = data >> 8;
				frame->data[i + 2] = data >> 16;
				frame->data[i + 3] = data >> 24;
			}
		} else {
			for (i = 0; i < frame->can_dlc; i += 2, dreg++) {
				data = priv->read_reg(priv, dreg);
				frame->data[i] = data;
				frame->data[i + 1] = data >> 8;
			}
		}
	}

	stats->rx_packets++;
	stats->rx_bytes += frame->can_dlc;

	netif_receive_skb(skb);
	return 0;
}