#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xircom_private {scalar_t__* tx_buffer; TYPE_2__** tx_skb; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  collisions; int /*<<< orphan*/  tx_bytes; } ;
struct net_device {TYPE_1__ stats; } ;
struct TYPE_4__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_irq (TYPE_2__*) ; 
 int le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static void
investigate_write_descriptor(struct net_device *dev,
			     struct xircom_private *card,
			     int descnr, unsigned int bufferoffset)
{
	int status;

	status = le32_to_cpu(card->tx_buffer[4*descnr]);
#if 0
	if (status & 0x8000) {	/* Major error */
		pr_err("Major transmit error status %x\n", status);
		card->tx_buffer[4*descnr] = 0;
		netif_wake_queue (dev);
	}
#endif
	if (status > 0) {	/* bit 31 is 0 when done */
		if (card->tx_skb[descnr]!=NULL) {
			dev->stats.tx_bytes += card->tx_skb[descnr]->len;
			dev_kfree_skb_irq(card->tx_skb[descnr]);
		}
		card->tx_skb[descnr] = NULL;
		/* Bit 8 in the status field is 1 if there was a collision */
		if (status & (1 << 8))
			dev->stats.collisions++;
		card->tx_buffer[4*descnr] = 0; /* descriptor is free again */
		netif_wake_queue (dev);
		dev->stats.tx_packets++;
	}
}