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
struct xircom_private {int transmit_used; scalar_t__* tx_buffer; int /*<<< orphan*/  lock; struct sk_buff** tx_skb; } ;
struct sk_buff {int len; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int NUMDESCRIPTORS ; 
 int* bufferoffsets ; 
 int cpu_to_le32 (int) ; 
 int /*<<< orphan*/  investigate_write_descriptor (struct net_device*,struct xircom_private*,int,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 struct xircom_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,scalar_t__*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trigger_transmit (struct xircom_private*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static netdev_tx_t xircom_start_xmit(struct sk_buff *skb,
					   struct net_device *dev)
{
	struct xircom_private *card;
	unsigned long flags;
	int nextdescriptor;
	int desc;

	card = netdev_priv(dev);
	spin_lock_irqsave(&card->lock,flags);

	/* First see if we can free some descriptors */
	for (desc=0;desc<NUMDESCRIPTORS;desc++)
		investigate_write_descriptor(dev,card,desc,bufferoffsets[desc]);


	nextdescriptor = (card->transmit_used +1) % (NUMDESCRIPTORS);
	desc = card->transmit_used;

	/* only send the packet if the descriptor is free */
	if (card->tx_buffer[4*desc]==0) {
			/* Copy the packet data; zero the memory first as the card
			   sometimes sends more than you ask it to. */

			memset(&card->tx_buffer[bufferoffsets[desc]/4],0,1536);
			skb_copy_from_linear_data(skb,
				  &(card->tx_buffer[bufferoffsets[desc] / 4]),
						  skb->len);
			/* FIXME: The specification tells us that the length we send HAS to be a multiple of
			   4 bytes. */

			card->tx_buffer[4*desc+1] = cpu_to_le32(skb->len);
			if (desc == NUMDESCRIPTORS - 1) /* bit 25: last descriptor of the ring */
				card->tx_buffer[4*desc+1] |= cpu_to_le32(1<<25);  

			card->tx_buffer[4*desc+1] |= cpu_to_le32(0xF0000000);
						 /* 0xF0... means want interrupts*/
			card->tx_skb[desc] = skb;

			wmb();
			/* This gives the descriptor to the card */
			card->tx_buffer[4*desc] = cpu_to_le32(0x80000000);
			trigger_transmit(card);
			if (card->tx_buffer[nextdescriptor*4] & cpu_to_le32(0x8000000)) {
				/* next descriptor is occupied... */
				netif_stop_queue(dev);
			}
			card->transmit_used = nextdescriptor;
			spin_unlock_irqrestore(&card->lock,flags);
			return NETDEV_TX_OK;
	}

	/* Uh oh... no free descriptor... drop the packet */
	netif_stop_queue(dev);
	spin_unlock_irqrestore(&card->lock,flags);
	trigger_transmit(card);

	return NETDEV_TX_BUSY;
}