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
struct sk_buff {scalar_t__ data; } ;
struct net_device_stats {int tx_bytes; } ;
struct net_device {struct net_device_stats stats; } ;
struct can_frame {int can_id; int can_dlc; scalar_t__ data; } ;
struct at91_priv {int tx_next; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_IER ; 
 int /*<<< orphan*/  AT91_MB_MODE_DISABLED ; 
 int /*<<< orphan*/  AT91_MB_MODE_TX ; 
 int /*<<< orphan*/  AT91_MCR (unsigned int) ; 
 int AT91_MCR_MRTR ; 
 int AT91_MCR_MTCR ; 
 int /*<<< orphan*/  AT91_MDH (unsigned int) ; 
 int /*<<< orphan*/  AT91_MDL (unsigned int) ; 
 int /*<<< orphan*/  AT91_MID (unsigned int) ; 
 int /*<<< orphan*/  AT91_MSR (unsigned int) ; 
 int AT91_MSR_MRDY ; 
 int CAN_RTR_FLAG ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int at91_can_id_to_reg_mid (int) ; 
 int at91_read (struct at91_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_write (struct at91_priv*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ can_dropped_invalid_skb (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  can_put_echo_skb (struct sk_buff*,struct net_device*,scalar_t__) ; 
 scalar_t__ get_mb_tx_first (struct at91_priv*) ; 
 int get_next_mask (struct at91_priv*) ; 
 unsigned int get_tx_next_mb (struct at91_priv*) ; 
 unsigned int get_tx_next_prio (struct at91_priv*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct at91_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  set_mb_mode (struct at91_priv*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mb_mode_prio (struct at91_priv*,unsigned int,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static netdev_tx_t at91_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct at91_priv *priv = netdev_priv(dev);
	struct net_device_stats *stats = &dev->stats;
	struct can_frame *cf = (struct can_frame *)skb->data;
	unsigned int mb, prio;
	u32 reg_mid, reg_mcr;

	if (can_dropped_invalid_skb(dev, skb))
		return NETDEV_TX_OK;

	mb = get_tx_next_mb(priv);
	prio = get_tx_next_prio(priv);

	if (unlikely(!(at91_read(priv, AT91_MSR(mb)) & AT91_MSR_MRDY))) {
		netif_stop_queue(dev);

		netdev_err(dev, "BUG! TX buffer full when queue awake!\n");
		return NETDEV_TX_BUSY;
	}
	reg_mid = at91_can_id_to_reg_mid(cf->can_id);
	reg_mcr = ((cf->can_id & CAN_RTR_FLAG) ? AT91_MCR_MRTR : 0) |
		(cf->can_dlc << 16) | AT91_MCR_MTCR;

	/* disable MB while writing ID (see datasheet) */
	set_mb_mode(priv, mb, AT91_MB_MODE_DISABLED);
	at91_write(priv, AT91_MID(mb), reg_mid);
	set_mb_mode_prio(priv, mb, AT91_MB_MODE_TX, prio);

	at91_write(priv, AT91_MDL(mb), *(u32 *)(cf->data + 0));
	at91_write(priv, AT91_MDH(mb), *(u32 *)(cf->data + 4));

	/* This triggers transmission */
	at91_write(priv, AT91_MCR(mb), reg_mcr);

	stats->tx_bytes += cf->can_dlc;

	/* _NOTE_: subtract AT91_MB_TX_FIRST offset from mb! */
	can_put_echo_skb(skb, dev, mb - get_mb_tx_first(priv));

	/*
	 * we have to stop the queue and deliver all messages in case
	 * of a prio+mb counter wrap around. This is the case if
	 * tx_next buffer prio and mailbox equals 0.
	 *
	 * also stop the queue if next buffer is still in use
	 * (== not ready)
	 */
	priv->tx_next++;
	if (!(at91_read(priv, AT91_MSR(get_tx_next_mb(priv))) &
	      AT91_MSR_MRDY) ||
	    (priv->tx_next & get_next_mask(priv)) == 0)
		netif_stop_queue(dev);

	/* Enable interrupt for this mailbox */
	at91_write(priv, AT91_IER, 1 << mb);

	return NETDEV_TX_OK;
}