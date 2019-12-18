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
struct xcan_priv {int (* read_reg ) (struct xcan_priv*,int) ;} ;
struct sk_buff {int dummy; } ;
struct net_device_stats {int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_dropped; } ;
struct net_device {struct net_device_stats stats; } ;
struct canfd_frame {int len; int can_id; int data; } ;
struct can_frame {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int CAN_EFF_FLAG ; 
 int CAN_RTR_FLAG ; 
 int XCANFD_DW_BYTES ; 
 int XCANFD_FRAME_DW_OFFSET (int) ; 
 int XCAN_DLCR_DLC_MASK ; 
 int XCAN_DLCR_DLC_SHIFT ; 
 int XCAN_DLCR_EDL_MASK ; 
 int XCAN_FRAME_DLC_OFFSET (int) ; 
 int XCAN_FRAME_ID_OFFSET (int) ; 
 int XCAN_IDR_ID1_MASK ; 
 int XCAN_IDR_ID1_SHIFT ; 
 int XCAN_IDR_ID2_MASK ; 
 int XCAN_IDR_ID2_SHIFT ; 
 int XCAN_IDR_IDE_MASK ; 
 int XCAN_IDR_RTR_MASK ; 
 int XCAN_IDR_SRR_MASK ; 
 struct sk_buff* alloc_can_skb (struct net_device*,struct can_frame**) ; 
 struct sk_buff* alloc_canfd_skb (struct net_device*,struct canfd_frame**) ; 
 int can_dlc2len (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int get_can_dlc (int) ; 
 struct xcan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int stub1 (struct xcan_priv*,int) ; 
 int stub2 (struct xcan_priv*,int) ; 
 int stub3 (struct xcan_priv*,int) ; 
 int stub4 (struct xcan_priv*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int xcanfd_rx(struct net_device *ndev, int frame_base)
{
	struct xcan_priv *priv = netdev_priv(ndev);
	struct net_device_stats *stats = &ndev->stats;
	struct canfd_frame *cf;
	struct sk_buff *skb;
	u32 id_xcan, dlc, data[2] = {0, 0}, dwindex = 0, i, dw_offset;

	id_xcan = priv->read_reg(priv, XCAN_FRAME_ID_OFFSET(frame_base));
	dlc = priv->read_reg(priv, XCAN_FRAME_DLC_OFFSET(frame_base));
	if (dlc & XCAN_DLCR_EDL_MASK)
		skb = alloc_canfd_skb(ndev, &cf);
	else
		skb = alloc_can_skb(ndev, (struct can_frame **)&cf);

	if (unlikely(!skb)) {
		stats->rx_dropped++;
		return 0;
	}

	/* Change Xilinx CANFD data length format to socketCAN data
	 * format
	 */
	if (dlc & XCAN_DLCR_EDL_MASK)
		cf->len = can_dlc2len((dlc & XCAN_DLCR_DLC_MASK) >>
				  XCAN_DLCR_DLC_SHIFT);
	else
		cf->len = get_can_dlc((dlc & XCAN_DLCR_DLC_MASK) >>
					  XCAN_DLCR_DLC_SHIFT);

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
		if (!(dlc & XCAN_DLCR_EDL_MASK) && (id_xcan &
					XCAN_IDR_SRR_MASK))
			cf->can_id |= CAN_RTR_FLAG;
	}

	/* Check the frame received is FD or not*/
	if (dlc & XCAN_DLCR_EDL_MASK) {
		for (i = 0; i < cf->len; i += 4) {
			dw_offset = XCANFD_FRAME_DW_OFFSET(frame_base) +
					(dwindex * XCANFD_DW_BYTES);
			data[0] = priv->read_reg(priv, dw_offset);
			*(__be32 *)(cf->data + i) = cpu_to_be32(data[0]);
			dwindex++;
		}
	} else {
		for (i = 0; i < cf->len; i += 4) {
			dw_offset = XCANFD_FRAME_DW_OFFSET(frame_base);
			data[0] = priv->read_reg(priv, dw_offset + i);
			*(__be32 *)(cf->data + i) = cpu_to_be32(data[0]);
		}
	}
	stats->rx_bytes += cf->len;
	stats->rx_packets++;
	netif_receive_skb(skb);

	return 1;
}