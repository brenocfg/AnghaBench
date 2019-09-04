#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ti_hecc_priv {scalar_t__ rx_next; TYPE_1__* ndev; int /*<<< orphan*/  mbx_lock; } ;
struct sk_buff {int dummy; } ;
struct net_device_stats {int rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct can_frame {int can_id; int can_dlc; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {struct net_device_stats stats; } ;

/* Variables and functions */
 int BIT (int) ; 
 int CAN_EFF_FLAG ; 
 int CAN_EFF_MASK ; 
 int /*<<< orphan*/  CAN_LED_EVENT_RX ; 
 int CAN_RTR_FLAG ; 
 int CAN_SFF_MASK ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HECC_CANMCF ; 
 int HECC_CANMCF_RTR ; 
 int /*<<< orphan*/  HECC_CANMDH ; 
 int /*<<< orphan*/  HECC_CANMDL ; 
 int /*<<< orphan*/  HECC_CANME ; 
 int /*<<< orphan*/  HECC_CANMID ; 
 int HECC_CANMID_IDE ; 
 int /*<<< orphan*/  HECC_CANRMP ; 
 scalar_t__ HECC_RX_BUFFER_MBOX ; 
 struct sk_buff* alloc_can_skb (TYPE_1__*,struct can_frame**) ; 
 int /*<<< orphan*/  can_led_event (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int get_can_dlc (int) ; 
 int /*<<< orphan*/  hecc_clear_bit (struct ti_hecc_priv*,int /*<<< orphan*/ ,int) ; 
 int hecc_read_mbx (struct ti_hecc_priv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hecc_set_bit (struct ti_hecc_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hecc_write (struct ti_hecc_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 scalar_t__ printk_ratelimit () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ti_hecc_rx_pkt(struct ti_hecc_priv *priv, int mbxno)
{
	struct net_device_stats *stats = &priv->ndev->stats;
	struct can_frame *cf;
	struct sk_buff *skb;
	u32 data, mbx_mask;
	unsigned long flags;

	skb = alloc_can_skb(priv->ndev, &cf);
	if (!skb) {
		if (printk_ratelimit())
			netdev_err(priv->ndev,
				"ti_hecc_rx_pkt: alloc_can_skb() failed\n");
		return -ENOMEM;
	}

	mbx_mask = BIT(mbxno);
	data = hecc_read_mbx(priv, mbxno, HECC_CANMID);
	if (data & HECC_CANMID_IDE)
		cf->can_id = (data & CAN_EFF_MASK) | CAN_EFF_FLAG;
	else
		cf->can_id = (data >> 18) & CAN_SFF_MASK;
	data = hecc_read_mbx(priv, mbxno, HECC_CANMCF);
	if (data & HECC_CANMCF_RTR)
		cf->can_id |= CAN_RTR_FLAG;
	cf->can_dlc = get_can_dlc(data & 0xF);
	data = hecc_read_mbx(priv, mbxno, HECC_CANMDL);
	*(__be32 *)(cf->data) = cpu_to_be32(data);
	if (cf->can_dlc > 4) {
		data = hecc_read_mbx(priv, mbxno, HECC_CANMDH);
		*(__be32 *)(cf->data + 4) = cpu_to_be32(data);
	}
	spin_lock_irqsave(&priv->mbx_lock, flags);
	hecc_clear_bit(priv, HECC_CANME, mbx_mask);
	hecc_write(priv, HECC_CANRMP, mbx_mask);
	/* enable mailbox only if it is part of rx buffer mailboxes */
	if (priv->rx_next < HECC_RX_BUFFER_MBOX)
		hecc_set_bit(priv, HECC_CANME, mbx_mask);
	spin_unlock_irqrestore(&priv->mbx_lock, flags);

	stats->rx_bytes += cf->can_dlc;
	can_led_event(priv->ndev, CAN_LED_EVENT_RX);
	netif_receive_skb(skb);
	stats->rx_packets++;

	return 0;
}