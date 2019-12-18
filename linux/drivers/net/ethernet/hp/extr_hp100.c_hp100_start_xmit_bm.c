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
typedef  int u32 ;
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct TYPE_3__ {int tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {int base_addr; TYPE_1__ stats; int /*<<< orphan*/  name; } ;
struct hp100_private {scalar_t__ chip; scalar_t__ txrhead; int lan_type; scalar_t__ hub_status; int /*<<< orphan*/  lock; int /*<<< orphan*/  txrcommit; int /*<<< orphan*/  pci_dev; TYPE_2__* txrtail; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_4__ {scalar_t__ next; int* pdl; int /*<<< orphan*/  pdl_paddr; struct sk_buff* skb; } ;
typedef  TYPE_2__ hp100_ring_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ZLEN ; 
 scalar_t__ HP100_CHIPID_SHASTA ; 
 int HP100_LAN_100 ; 
 int HP100_LAN_ERR ; 
 int HP100_MIN_PACKET_SIZE ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  TX_PDA_L ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ dev_trans_start (struct net_device*) ; 
 scalar_t__ hp100_check_lan (struct net_device*) ; 
 int /*<<< orphan*/  hp100_ints_off () ; 
 int /*<<< orphan*/  hp100_ints_on () ; 
 void* hp100_login_to_vg_hub (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_outl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_outw (int,int /*<<< orphan*/ ) ; 
 int hp100_sense_lan (struct net_device*) ; 
 int /*<<< orphan*/  hp100_start_interface (struct net_device*) ; 
 int /*<<< orphan*/  hp100_stop_interface (struct net_device*) ; 
 int /*<<< orphan*/  jiffies ; 
 struct hp100_private* netdev_priv (struct net_device*) ; 
 scalar_t__ pci_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_padto (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static netdev_tx_t hp100_start_xmit_bm(struct sk_buff *skb,
				       struct net_device *dev)
{
	unsigned long flags;
	int i, ok_flag;
	int ioaddr = dev->base_addr;
	struct hp100_private *lp = netdev_priv(dev);
	hp100_ring_t *ringptr;

#ifdef HP100_DEBUG_B
	hp100_outw(0x4210, TRACE);
	printk("hp100: %s: start_xmit_bm\n", dev->name);
#endif
	if (skb->len <= 0)
		goto drop;

	if (lp->chip == HP100_CHIPID_SHASTA && skb_padto(skb, ETH_ZLEN))
		return NETDEV_TX_OK;

	/* Get Tx ring tail pointer */
	if (lp->txrtail->next == lp->txrhead) {
		/* No memory. */
#ifdef HP100_DEBUG
		printk("hp100: %s: start_xmit_bm: No TX PDL available.\n", dev->name);
#endif
		/* not waited long enough since last tx? */
		if (time_before(jiffies, dev_trans_start(dev) + HZ))
			goto drop;

		if (hp100_check_lan(dev))
			goto drop;

		if (lp->lan_type == HP100_LAN_100 && lp->hub_status < 0) {
			/* we have a 100Mb/s adapter but it isn't connected to hub */
			printk("hp100: %s: login to 100Mb/s hub retry\n", dev->name);
			hp100_stop_interface(dev);
			lp->hub_status = hp100_login_to_vg_hub(dev, 0);
			hp100_start_interface(dev);
		} else {
			spin_lock_irqsave(&lp->lock, flags);
			hp100_ints_off();	/* Useful ? Jean II */
			i = hp100_sense_lan(dev);
			hp100_ints_on();
			spin_unlock_irqrestore(&lp->lock, flags);
			if (i == HP100_LAN_ERR)
				printk("hp100: %s: link down detected\n", dev->name);
			else if (lp->lan_type != i) {	/* cable change! */
				/* it's very hard - all network settings must be changed!!! */
				printk("hp100: %s: cable change 10Mb/s <-> 100Mb/s detected\n", dev->name);
				lp->lan_type = i;
				hp100_stop_interface(dev);
				if (lp->lan_type == HP100_LAN_100)
					lp->hub_status = hp100_login_to_vg_hub(dev, 0);
				hp100_start_interface(dev);
			} else {
				printk("hp100: %s: interface reset\n", dev->name);
				hp100_stop_interface(dev);
				if (lp->lan_type == HP100_LAN_100)
					lp->hub_status = hp100_login_to_vg_hub(dev, 0);
				hp100_start_interface(dev);
			}
		}

		goto drop;
	}

	/*
	 * we have to turn int's off before modifying this, otherwise
	 * a tx_pdl_cleanup could occur at the same time
	 */
	spin_lock_irqsave(&lp->lock, flags);
	ringptr = lp->txrtail;
	lp->txrtail = ringptr->next;

	/* Check whether packet has minimal packet size */
	ok_flag = skb->len >= HP100_MIN_PACKET_SIZE;
	i = ok_flag ? skb->len : HP100_MIN_PACKET_SIZE;

	ringptr->skb = skb;
	ringptr->pdl[0] = ((1 << 16) | i);	/* PDH: 1 Fragment & length */
	if (lp->chip == HP100_CHIPID_SHASTA) {
		/* TODO:Could someone who has the EISA card please check if this works? */
		ringptr->pdl[2] = i;
	} else {		/* Lassen */
		/* In the PDL, don't use the padded size but the real packet size: */
		ringptr->pdl[2] = skb->len;	/* 1st Frag: Length of frag */
	}
	/* Conversion to new PCI API : map skbuf data to PCI bus.
	 * Doc says it's OK for EISA as well - Jean II */
	ringptr->pdl[1] = ((u32) pci_map_single(lp->pci_dev, skb->data, ringptr->pdl[2], PCI_DMA_TODEVICE));	/* 1st Frag: Adr. of data */

	/* Hand this PDL to the card. */
	hp100_outl(ringptr->pdl_paddr, TX_PDA_L);	/* Low Prio. Queue */

	lp->txrcommit++;

	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;

	spin_unlock_irqrestore(&lp->lock, flags);

	return NETDEV_TX_OK;

drop:
	dev_kfree_skb(skb);
	return NETDEV_TX_OK;
}