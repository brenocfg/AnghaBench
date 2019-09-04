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
struct xcan_priv {int (* read_reg ) (struct xcan_priv*,int /*<<< orphan*/ ) ;} ;
struct sk_buff {int dummy; } ;
struct net_device_stats {int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct net_device {struct net_device_stats stats; } ;
struct can_frame {int can_dlc; int can_id; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int CAN_EFF_FLAG ; 
 int CAN_RTR_FLAG ; 
 int XCAN_DLCR_DLC_SHIFT ; 
 int /*<<< orphan*/  XCAN_FRAME_DLC_OFFSET (int) ; 
 int /*<<< orphan*/  XCAN_FRAME_DW1_OFFSET (int) ; 
 int /*<<< orphan*/  XCAN_FRAME_DW2_OFFSET (int) ; 
 int /*<<< orphan*/  XCAN_FRAME_ID_OFFSET (int) ; 
 int XCAN_IDR_ID1_MASK ; 
 int XCAN_IDR_ID1_SHIFT ; 
 int XCAN_IDR_ID2_MASK ; 
 int XCAN_IDR_ID2_SHIFT ; 
 int XCAN_IDR_IDE_MASK ; 
 int XCAN_IDR_RTR_MASK ; 
 int XCAN_IDR_SRR_MASK ; 
 struct sk_buff* alloc_can_skb (struct net_device*,struct can_frame**) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int get_can_dlc (int) ; 
 struct xcan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int stub1 (struct xcan_priv*,int /*<<< orphan*/ ) ; 
 int stub2 (struct xcan_priv*,int /*<<< orphan*/ ) ; 
 int stub3 (struct xcan_priv*,int /*<<< orphan*/ ) ; 
 int stub4 (struct xcan_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int xcan_rx(struct net_device *ndev, int frame_base)
{
	struct xcan_priv *priv = netdev_priv(ndev);
	struct net_device_stats *stats = &ndev->stats;
	struct can_frame *cf;
	struct sk_buff *skb;
	u32 id_xcan, dlc, data[2] = {0, 0};

	skb = alloc_can_skb(ndev, &cf);
	if (unlikely(!skb)) {
		stats->rx_dropped++;
		return 0;
	}

	/* Read a frame from Xilinx zynq CANPS */
	id_xcan = priv->read_reg(priv, XCAN_FRAME_ID_OFFSET(frame_base));
	dlc = priv->read_reg(priv, XCAN_FRAME_DLC_OFFSET(frame_base)) >>
				   XCAN_DLCR_DLC_SHIFT;

	/* Change Xilinx CAN data length format to socketCAN data format */
	cf->can_dlc = get_can_dlc(dlc);

	/* Change Xilinx CAN ID format to socketCAN ID format */
	if (id_xcan & XCAN_IDR_IDE_MASK) {
		/* The received frame is an Extended format frame */
		cf->can_id = (id_xcan & XCAN_IDR_ID1_MASK) >> 3;
		cf->can_id |= (id_xcan & XCAN_IDR_ID2_MASK) >>
				XCAN_IDR_ID2_SHIFT;
		cf->can_id |= CAN_EFF_FLAG;
		if (id_xcan & XCAN_IDR_RTR_MASK)
			cf->can_id |= CAN_RTR_FLAG;
	} else {
		/* The received frame is a standard format frame */
		cf->can_id = (id_xcan & XCAN_IDR_ID1_MASK) >>
				XCAN_IDR_ID1_SHIFT;
		if (id_xcan & XCAN_IDR_SRR_MASK)
			cf->can_id |= CAN_RTR_FLAG;
	}

	/* DW1/DW2 must always be read to remove message from RXFIFO */
	data[0] = priv->read_reg(priv, XCAN_FRAME_DW1_OFFSET(frame_base));
	data[1] = priv->read_reg(priv, XCAN_FRAME_DW2_OFFSET(frame_base));

	if (!(cf->can_id & CAN_RTR_FLAG)) {
		/* Change Xilinx CAN data format to socketCAN data format */
		if (cf->can_dlc > 0)
			*(__be32 *)(cf->data) = cpu_to_be32(data[0]);
		if (cf->can_dlc > 4)
			*(__be32 *)(cf->data + 4) = cpu_to_be32(data[1]);
	}

	stats->rx_bytes += cf->can_dlc;
	stats->rx_packets++;
	netif_receive_skb(skb);

	return 1;
}