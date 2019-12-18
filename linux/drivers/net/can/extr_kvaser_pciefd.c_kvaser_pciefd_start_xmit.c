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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct kvaser_pciefd_tx_packet {scalar_t__ data; int /*<<< orphan*/ * header; } ;
struct TYPE_2__ {int echo_skb_max; scalar_t__* echo_skb; } ;
struct kvaser_pciefd_can {int echo_idx; int /*<<< orphan*/  echo_lock; TYPE_1__ can; scalar_t__ reg_base; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 scalar_t__ KVASER_PCIEFD_CAN_TX_MAX_COUNT ; 
 scalar_t__ KVASER_PCIEFD_KCAN_FIFO_LAST_REG ; 
 scalar_t__ KVASER_PCIEFD_KCAN_FIFO_REG ; 
 scalar_t__ KVASER_PCIEFD_KCAN_TX_NPACKETS_REG ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ can_dropped_invalid_skb (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  can_put_echo_skb (struct sk_buff*,struct net_device*,int) ; 
 scalar_t__ ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  iowrite32_rep (scalar_t__,scalar_t__,int) ; 
 int kvaser_pciefd_prepare_tx_packet (struct kvaser_pciefd_tx_packet*,struct kvaser_pciefd_can*,struct sk_buff*) ; 
 struct kvaser_pciefd_can* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static netdev_tx_t kvaser_pciefd_start_xmit(struct sk_buff *skb,
					    struct net_device *netdev)
{
	struct kvaser_pciefd_can *can = netdev_priv(netdev);
	unsigned long irq_flags;
	struct kvaser_pciefd_tx_packet packet;
	int nwords;
	u8 count;

	if (can_dropped_invalid_skb(netdev, skb))
		return NETDEV_TX_OK;

	nwords = kvaser_pciefd_prepare_tx_packet(&packet, can, skb);

	spin_lock_irqsave(&can->echo_lock, irq_flags);

	/* Prepare and save echo skb in internal slot */
	can_put_echo_skb(skb, netdev, can->echo_idx);

	/* Move echo index to the next slot */
	can->echo_idx = (can->echo_idx + 1) % can->can.echo_skb_max;

	/* Write header to fifo */
	iowrite32(packet.header[0],
		  can->reg_base + KVASER_PCIEFD_KCAN_FIFO_REG);
	iowrite32(packet.header[1],
		  can->reg_base + KVASER_PCIEFD_KCAN_FIFO_REG);

	if (nwords) {
		u32 data_last = ((u32 *)packet.data)[nwords - 1];

		/* Write data to fifo, except last word */
		iowrite32_rep(can->reg_base +
			      KVASER_PCIEFD_KCAN_FIFO_REG, packet.data,
			      nwords - 1);
		/* Write last word to end of fifo */
		__raw_writel(data_last, can->reg_base +
			     KVASER_PCIEFD_KCAN_FIFO_LAST_REG);
	} else {
		/* Complete write to fifo */
		__raw_writel(0, can->reg_base +
			     KVASER_PCIEFD_KCAN_FIFO_LAST_REG);
	}

	count = ioread32(can->reg_base + KVASER_PCIEFD_KCAN_TX_NPACKETS_REG);
	/* No room for a new message, stop the queue until at least one
	 * successful transmit
	 */
	if (count >= KVASER_PCIEFD_CAN_TX_MAX_COUNT ||
	    can->can.echo_skb[can->echo_idx])
		netif_stop_queue(netdev);

	spin_unlock_irqrestore(&can->echo_lock, irq_flags);

	return NETDEV_TX_OK;
}