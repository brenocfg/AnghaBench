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
struct sk_buff {int* data; scalar_t__ len; } ;
struct net_local {scalar_t__ send_cmd; } ;
struct net_device {scalar_t__ mem_start; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 size_t ETH_ALEN ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  PP_BusST ; 
 int /*<<< orphan*/  PP_TxCMD ; 
 scalar_t__ PP_TxFrame ; 
 int /*<<< orphan*/  PP_TxLength ; 
 int READY_FOR_TX_NOW ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 struct net_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct net_local*,int /*<<< orphan*/ ,struct net_device*,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int readreg (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,void*,scalar_t__) ; 
 int /*<<< orphan*/  tx_queued ; 
 int /*<<< orphan*/  writereg (struct net_device*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static netdev_tx_t
net_send_packet(struct sk_buff *skb, struct net_device *dev)
{
	struct net_local *lp = netdev_priv(dev);
	unsigned long flags;

	netif_dbg(lp, tx_queued, dev, "sent %d byte packet of type %x\n",
		  skb->len, skb->data[ETH_ALEN + ETH_ALEN] << 8 |
		  skb->data[ETH_ALEN + ETH_ALEN + 1]);

	/* keep the upload from being interrupted, since we
	   ask the chip to start transmitting before the
	   whole packet has been completely uploaded. */
	local_irq_save(flags);
	netif_stop_queue(dev);

	/* initiate a transmit sequence */
	writereg(dev, PP_TxCMD, lp->send_cmd);
	writereg(dev, PP_TxLength, skb->len);

	/* Test to see if the chip has allocated memory for the packet */
	if ((readreg(dev, PP_BusST) & READY_FOR_TX_NOW) == 0) {
		/* Gasp!  It hasn't.  But that shouldn't happen since
		   we're waiting for TxOk, so return 1 and requeue this packet. */
		local_irq_restore(flags);
		return NETDEV_TX_BUSY;
	}

	/* Write the contents of the packet */
	skb_copy_from_linear_data(skb, (void *)(dev->mem_start + PP_TxFrame),
				  skb->len+1);

	local_irq_restore(flags);
	dev_kfree_skb (skb);

	return NETDEV_TX_OK;
}