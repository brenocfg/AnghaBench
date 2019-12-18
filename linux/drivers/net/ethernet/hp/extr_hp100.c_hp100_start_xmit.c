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
typedef  int /*<<< orphan*/  u_short ;
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {int base_addr; int /*<<< orphan*/  name; TYPE_1__ stats; } ;
struct hp100_private {int lan_type; scalar_t__ hub_status; int mode; int /*<<< orphan*/  lock; int /*<<< orphan*/  mem_ptr_virt; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  DATA32 ; 
 int /*<<< orphan*/  FRAGMENT_LEN ; 
 int HP100_LAN_100 ; 
 int HP100_LAN_ERR ; 
 int HP100_MIN_PACKET_SIZE ; 
 scalar_t__ HP100_REG_DATA32 ; 
 int HP100_SET_LB ; 
 int HP100_TX_CMD ; 
 int HP100_TX_COMPLETE ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  IRQ_MASK ; 
 int /*<<< orphan*/  IRQ_STATUS ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  OPTION_MSW ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  TX_MEM_FREE ; 
 int /*<<< orphan*/  TX_PKT_CNT ; 
 int /*<<< orphan*/  dev_consume_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ dev_trans_start (struct net_device*) ; 
 scalar_t__ hp100_check_lan (struct net_device*) ; 
 int hp100_inb (int /*<<< orphan*/ ) ; 
 int hp100_inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_ints_off () ; 
 int /*<<< orphan*/  hp100_ints_on () ; 
 int /*<<< orphan*/  hp100_inw (int /*<<< orphan*/ ) ; 
 void* hp100_login_to_vg_hub (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_outl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_outw (int,int /*<<< orphan*/ ) ; 
 int hp100_sense_lan (struct net_device*) ; 
 int /*<<< orphan*/  hp100_start_interface (struct net_device*) ; 
 int /*<<< orphan*/  hp100_stop_interface (struct net_device*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  memcpy_toio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct hp100_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outsl (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static netdev_tx_t hp100_start_xmit(struct sk_buff *skb,
				    struct net_device *dev)
{
	unsigned long flags;
	int i, ok_flag;
	int ioaddr = dev->base_addr;
	u_short val;
	struct hp100_private *lp = netdev_priv(dev);

#ifdef HP100_DEBUG_B
	hp100_outw(0x4212, TRACE);
	printk("hp100: %s: start_xmit\n", dev->name);
#endif
	if (skb->len <= 0)
		goto drop;

	if (hp100_check_lan(dev))
		goto drop;

	/* If there is not enough free memory on the card... */
	i = hp100_inl(TX_MEM_FREE) & 0x7fffffff;
	if (!(((i / 2) - 539) > (skb->len + 16) && (hp100_inb(TX_PKT_CNT) < 255))) {
#ifdef HP100_DEBUG
		printk("hp100: %s: start_xmit: tx free mem = 0x%x\n", dev->name, i);
#endif
		/* not waited long enough since last failed tx try? */
		if (time_before(jiffies, dev_trans_start(dev) + HZ)) {
#ifdef HP100_DEBUG
			printk("hp100: %s: trans_start timing problem\n",
			       dev->name);
#endif
			goto drop;
		}
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
				/* it's very hard - all network setting must be changed!!! */
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
				mdelay(1);
			}
		}
		goto drop;
	}

	for (i = 0; i < 6000 && (hp100_inb(OPTION_MSW) & HP100_TX_CMD); i++) {
#ifdef HP100_DEBUG_TX
		printk("hp100: %s: start_xmit: busy\n", dev->name);
#endif
	}

	spin_lock_irqsave(&lp->lock, flags);
	hp100_ints_off();
	val = hp100_inw(IRQ_STATUS);
	/* Ack / clear the interrupt TX_COMPLETE interrupt - this interrupt is set
	 * when the current packet being transmitted on the wire is completed. */
	hp100_outw(HP100_TX_COMPLETE, IRQ_STATUS);
#ifdef HP100_DEBUG_TX
	printk("hp100: %s: start_xmit: irq_status=0x%.4x, irqmask=0x%.4x, len=%d\n",
			dev->name, val, hp100_inw(IRQ_MASK), (int) skb->len);
#endif

	ok_flag = skb->len >= HP100_MIN_PACKET_SIZE;
	i = ok_flag ? skb->len : HP100_MIN_PACKET_SIZE;

	hp100_outw(i, DATA32);	/* tell card the total packet length */
	hp100_outw(i, FRAGMENT_LEN);	/* and first/only fragment length    */

	if (lp->mode == 2) {	/* memory mapped */
		/* Note: The J2585B needs alignment to 32bits here!  */
		memcpy_toio(lp->mem_ptr_virt, skb->data, (skb->len + 3) & ~3);
		if (!ok_flag)
			memset_io(lp->mem_ptr_virt, 0, HP100_MIN_PACKET_SIZE - skb->len);
	} else {		/* programmed i/o */
		outsl(ioaddr + HP100_REG_DATA32, skb->data,
		      (skb->len + 3) >> 2);
		if (!ok_flag)
			for (i = (skb->len + 3) & ~3; i < HP100_MIN_PACKET_SIZE; i += 4)
				hp100_outl(0, DATA32);
	}

	hp100_outb(HP100_TX_CMD | HP100_SET_LB, OPTION_MSW);	/* send packet */

	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;
	hp100_ints_on();
	spin_unlock_irqrestore(&lp->lock, flags);

	dev_consume_skb_any(skb);

#ifdef HP100_DEBUG_TX
	printk("hp100: %s: start_xmit: end\n", dev->name);
#endif

	return NETDEV_TX_OK;

drop:
	dev_kfree_skb(skb);
	return NETDEV_TX_OK;

}