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
struct net_device_stats {int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; } ;
struct net_device {struct net_device_stats stats; } ;
struct ifi_canfd_priv {scalar_t__ base; } ;
struct canfd_frame {int len; int can_id; scalar_t__ data; int /*<<< orphan*/  flags; } ;
struct can_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CANFD_BRS ; 
 int /*<<< orphan*/  CANFD_ESI ; 
 int CAN_EFF_FLAG ; 
 int CAN_RTR_FLAG ; 
 scalar_t__ IFI_CANFD_INTERRUPT ; 
 int IFI_CANFD_INTERRUPT_RXFIFO_NEMPTY ; 
 int IFI_CANFD_INTERRUPT_RXFIFO_NEMPTY_PER ; 
 scalar_t__ IFI_CANFD_RXFIFO_DATA ; 
 scalar_t__ IFI_CANFD_RXFIFO_DLC ; 
 int IFI_CANFD_RXFIFO_DLC_BRS ; 
 int IFI_CANFD_RXFIFO_DLC_DLC_MASK ; 
 int IFI_CANFD_RXFIFO_DLC_DLC_OFFSET ; 
 int IFI_CANFD_RXFIFO_DLC_EDL ; 
 int IFI_CANFD_RXFIFO_DLC_ESI ; 
 int IFI_CANFD_RXFIFO_DLC_RTR ; 
 scalar_t__ IFI_CANFD_RXFIFO_ID ; 
 int IFI_CANFD_RXFIFO_ID_IDE ; 
 int IFI_CANFD_RXFIFO_ID_ID_OFFSET ; 
 int IFI_CANFD_RXFIFO_ID_ID_STD_MASK ; 
 int IFI_CANFD_RXFIFO_ID_ID_XTD_MASK ; 
 int IFI_CANFD_RXFIFO_ID_ID_XTD_OFFSET ; 
 int IFI_CANFD_RXFIFO_ID_ID_XTD_WIDTH ; 
 scalar_t__ IFI_CANFD_RXSTCMD ; 
 int const IFI_CANFD_RXSTCMD_REMOVE_MSG ; 
 struct sk_buff* alloc_can_skb (struct net_device*,struct can_frame**) ; 
 struct sk_buff* alloc_canfd_skb (struct net_device*,struct canfd_frame**) ; 
 int can_dlc2len (int) ; 
 int get_can_dlc (int) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 struct ifi_canfd_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int const,scalar_t__) ; 

__attribute__((used)) static void ifi_canfd_read_fifo(struct net_device *ndev)
{
	struct net_device_stats *stats = &ndev->stats;
	struct ifi_canfd_priv *priv = netdev_priv(ndev);
	struct canfd_frame *cf;
	struct sk_buff *skb;
	const u32 rx_irq_mask = IFI_CANFD_INTERRUPT_RXFIFO_NEMPTY |
				IFI_CANFD_INTERRUPT_RXFIFO_NEMPTY_PER;
	u32 rxdlc, rxid;
	u32 dlc, id;
	int i;

	rxdlc = readl(priv->base + IFI_CANFD_RXFIFO_DLC);
	if (rxdlc & IFI_CANFD_RXFIFO_DLC_EDL)
		skb = alloc_canfd_skb(ndev, &cf);
	else
		skb = alloc_can_skb(ndev, (struct can_frame **)&cf);

	if (!skb) {
		stats->rx_dropped++;
		return;
	}

	dlc = (rxdlc >> IFI_CANFD_RXFIFO_DLC_DLC_OFFSET) &
	      IFI_CANFD_RXFIFO_DLC_DLC_MASK;
	if (rxdlc & IFI_CANFD_RXFIFO_DLC_EDL)
		cf->len = can_dlc2len(dlc);
	else
		cf->len = get_can_dlc(dlc);

	rxid = readl(priv->base + IFI_CANFD_RXFIFO_ID);
	id = (rxid >> IFI_CANFD_RXFIFO_ID_ID_OFFSET);
	if (id & IFI_CANFD_RXFIFO_ID_IDE) {
		id &= IFI_CANFD_RXFIFO_ID_ID_XTD_MASK;
		/*
		 * In case the Extended ID frame is received, the standard
		 * and extended part of the ID are swapped in the register,
		 * so swap them back to obtain the correct ID.
		 */
		id = (id >> IFI_CANFD_RXFIFO_ID_ID_XTD_OFFSET) |
		     ((id & IFI_CANFD_RXFIFO_ID_ID_STD_MASK) <<
		       IFI_CANFD_RXFIFO_ID_ID_XTD_WIDTH);
		id |= CAN_EFF_FLAG;
	} else {
		id &= IFI_CANFD_RXFIFO_ID_ID_STD_MASK;
	}
	cf->can_id = id;

	if (rxdlc & IFI_CANFD_RXFIFO_DLC_ESI) {
		cf->flags |= CANFD_ESI;
		netdev_dbg(ndev, "ESI Error\n");
	}

	if (!(rxdlc & IFI_CANFD_RXFIFO_DLC_EDL) &&
	    (rxdlc & IFI_CANFD_RXFIFO_DLC_RTR)) {
		cf->can_id |= CAN_RTR_FLAG;
	} else {
		if (rxdlc & IFI_CANFD_RXFIFO_DLC_BRS)
			cf->flags |= CANFD_BRS;

		for (i = 0; i < cf->len; i += 4) {
			*(u32 *)(cf->data + i) =
				readl(priv->base + IFI_CANFD_RXFIFO_DATA + i);
		}
	}

	/* Remove the packet from FIFO */
	writel(IFI_CANFD_RXSTCMD_REMOVE_MSG, priv->base + IFI_CANFD_RXSTCMD);
	writel(rx_irq_mask, priv->base + IFI_CANFD_INTERRUPT);

	stats->rx_packets++;
	stats->rx_bytes += cf->len;

	netif_receive_skb(skb);
}