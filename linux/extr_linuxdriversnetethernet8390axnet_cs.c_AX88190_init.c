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
struct net_device {long base_addr; int* dev_addr; } ;
struct ei_device {int tx_start_page; int rx_start_page; int stop_page; int current_page; scalar_t__ txing; scalar_t__ tx2; scalar_t__ tx1; scalar_t__ word16; } ;
struct e8390_pkt_hdr {int dummy; } ;
struct axnet_dev {int flags; int duplex_flag; } ;

/* Variables and functions */
 scalar_t__ AXNET_GPIO ; 
 scalar_t__ E8390_CMD ; 
 int E8390_NODMA ; 
 int E8390_PAGE0 ; 
 int E8390_PAGE1 ; 
 int E8390_RXCONFIG ; 
 int E8390_RXOFF ; 
 int E8390_START ; 
 int E8390_STOP ; 
 int E8390_TXCONFIG ; 
 int E8390_TXOFF ; 
 scalar_t__ EN0_BOUNDARY ; 
 scalar_t__ EN0_DCFG ; 
 scalar_t__ EN0_IMR ; 
 scalar_t__ EN0_ISR ; 
 scalar_t__ EN0_RCNTHI ; 
 scalar_t__ EN0_RCNTLO ; 
 scalar_t__ EN0_RXCR ; 
 scalar_t__ EN0_STARTPG ; 
 scalar_t__ EN0_STOPPG ; 
 scalar_t__ EN0_TPSR ; 
 scalar_t__ EN0_TXCR ; 
 scalar_t__ EN1_CURPAG ; 
 scalar_t__ EN1_PHYS_SHIFT (int) ; 
 int ENDCFG_WTS ; 
 int ENISR_ALL ; 
 int IS_AX88790 ; 
 struct axnet_dev* PRIV (struct net_device*) ; 
 int /*<<< orphan*/  do_set_multicast_list (struct net_device*) ; 
 int inb_p (scalar_t__) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 struct ei_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outb_p (int,scalar_t__) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void AX88190_init(struct net_device *dev, int startp)
{
	struct axnet_dev *info = PRIV(dev);
	long e8390_base = dev->base_addr;
	struct ei_device *ei_local = netdev_priv(dev);
	int i;
	int endcfg = ei_local->word16 ? (0x48 | ENDCFG_WTS) : 0x48;
    
	if(sizeof(struct e8390_pkt_hdr)!=4)
    		panic("8390.c: header struct mispacked\n");    
	/* Follow National Semi's recommendations for initing the DP83902. */
	outb_p(E8390_NODMA+E8390_PAGE0+E8390_STOP, e8390_base+E8390_CMD); /* 0x21 */
	outb_p(endcfg, e8390_base + EN0_DCFG);	/* 0x48 or 0x49 */
	/* Clear the remote byte count registers. */
	outb_p(0x00,  e8390_base + EN0_RCNTLO);
	outb_p(0x00,  e8390_base + EN0_RCNTHI);
	/* Set to monitor and loopback mode -- this is vital!. */
	outb_p(E8390_RXOFF|0x40, e8390_base + EN0_RXCR); /* 0x60 */
	outb_p(E8390_TXOFF, e8390_base + EN0_TXCR); /* 0x02 */
	/* Set the transmit page and receive ring. */
	outb_p(ei_local->tx_start_page, e8390_base + EN0_TPSR);
	ei_local->tx1 = ei_local->tx2 = 0;
	outb_p(ei_local->rx_start_page, e8390_base + EN0_STARTPG);
	outb_p(ei_local->stop_page-1, e8390_base + EN0_BOUNDARY);	/* 3c503 says 0x3f,NS0x26*/
	ei_local->current_page = ei_local->rx_start_page;		/* assert boundary+1 */
	outb_p(ei_local->stop_page, e8390_base + EN0_STOPPG);
	/* Clear the pending interrupts and mask. */
	outb_p(0xFF, e8390_base + EN0_ISR);
	outb_p(0x00,  e8390_base + EN0_IMR);
    
	/* Copy the station address into the DS8390 registers. */

	outb_p(E8390_NODMA + E8390_PAGE1 + E8390_STOP, e8390_base+E8390_CMD); /* 0x61 */
	for(i = 0; i < 6; i++) 
	{
		outb_p(dev->dev_addr[i], e8390_base + EN1_PHYS_SHIFT(i));
		if(inb_p(e8390_base + EN1_PHYS_SHIFT(i))!=dev->dev_addr[i])
			netdev_err(dev, "Hw. address read/write mismap %d\n", i);
	}

	outb_p(ei_local->rx_start_page, e8390_base + EN1_CURPAG);
	outb_p(E8390_NODMA+E8390_PAGE0+E8390_STOP, e8390_base+E8390_CMD);

	netif_start_queue(dev);
	ei_local->tx1 = ei_local->tx2 = 0;
	ei_local->txing = 0;

	if (info->flags & IS_AX88790)	/* select Internal PHY */
		outb(0x10, e8390_base + AXNET_GPIO);

	if (startp) 
	{
		outb_p(0xff,  e8390_base + EN0_ISR);
		outb_p(ENISR_ALL,  e8390_base + EN0_IMR);
		outb_p(E8390_NODMA+E8390_PAGE0+E8390_START, e8390_base+E8390_CMD);
		outb_p(E8390_TXCONFIG | info->duplex_flag,
		       e8390_base + EN0_TXCR); /* xmit on. */
		/* 3c503 TechMan says rxconfig only after the NIC is started. */
		outb_p(E8390_RXCONFIG | 0x40, e8390_base + EN0_RXCR); /* rx on, */
		do_set_multicast_list(dev);	/* (re)load the mcast table */
	}
}