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
struct net_device {int base_addr; int irq; int if_port; int /*<<< orphan*/  name; int /*<<< orphan*/ * dev_addr; } ;

/* Variables and functions */
 int AckIntr ; 
 int /*<<< orphan*/  EL3WINDOW (int) ; 
 int EL3_CMD ; 
 int FD_ENABLE ; 
 int IntLatch ; 
 int IntReq ; 
 int MEDIA_TP ; 
 int RxBroadcast ; 
 int RxComplete ; 
 int RxEarly ; 
 int RxEnable ; 
 int RxStation ; 
 int SetIntrEnb ; 
 int SetRxFilter ; 
 int SetStatusEnb ; 
 int StartCoax ; 
 int StatsDisable ; 
 int StatsEnable ; 
 int StatsFull ; 
 int TxAvailable ; 
 int TxComplete ; 
 int TxEnable ; 
 int WN0_IRQ ; 
 int WN4_MEDIA ; 
 int WN4_NETDIAG ; 
 int el3_debug ; 
 int /*<<< orphan*/  inb (int) ; 
 int inw (int) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outw (int,int) ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int read_eeprom (int,int) ; 

__attribute__((used)) static void
el3_up(struct net_device *dev)
{
	int i, sw_info, net_diag;
	int ioaddr = dev->base_addr;

	/* Activating the board required and does no harm otherwise */
	outw(0x0001, ioaddr + 4);

	/* Set the IRQ line. */
	outw((dev->irq << 12) | 0x0f00, ioaddr + WN0_IRQ);

	/* Set the station address in window 2 each time opened. */
	EL3WINDOW(2);

	for (i = 0; i < 6; i++)
		outb(dev->dev_addr[i], ioaddr + i);

	if ((dev->if_port & 0x03) == 3) /* BNC interface */
		/* Start the thinnet transceiver. We should really wait 50ms...*/
		outw(StartCoax, ioaddr + EL3_CMD);
	else if ((dev->if_port & 0x03) == 0) { /* 10baseT interface */
		/* Combine secondary sw_info word (the adapter level) and primary
			sw_info word (duplex setting plus other useless bits) */
		EL3WINDOW(0);
		sw_info = (read_eeprom(ioaddr, 0x14) & 0x400f) |
			(read_eeprom(ioaddr, 0x0d) & 0xBff0);

		EL3WINDOW(4);
		net_diag = inw(ioaddr + WN4_NETDIAG);
		net_diag = (net_diag | FD_ENABLE); /* temporarily assume full-duplex will be set */
		pr_info("%s: ", dev->name);
		switch (dev->if_port & 0x0c) {
			case 12:
				/* force full-duplex mode if 3c5x9b */
				if (sw_info & 0x000f) {
					pr_cont("Forcing 3c5x9b full-duplex mode");
					break;
				}
				/* fall through */
			case 8:
				/* set full-duplex mode based on eeprom config setting */
				if ((sw_info & 0x000f) && (sw_info & 0x8000)) {
					pr_cont("Setting 3c5x9b full-duplex mode (from EEPROM configuration bit)");
					break;
				}
				/* fall through */
			default:
				/* xcvr=(0 || 4) OR user has an old 3c5x9 non "B" model */
				pr_cont("Setting 3c5x9/3c5x9B half-duplex mode");
				net_diag = (net_diag & ~FD_ENABLE); /* disable full duplex */
		}

		outw(net_diag, ioaddr + WN4_NETDIAG);
		pr_cont(" if_port: %d, sw_info: %4.4x\n", dev->if_port, sw_info);
		if (el3_debug > 3)
			pr_debug("%s: 3c5x9 net diag word is now: %4.4x.\n", dev->name, net_diag);
		/* Enable link beat and jabber check. */
		outw(inw(ioaddr + WN4_MEDIA) | MEDIA_TP, ioaddr + WN4_MEDIA);
	}

	/* Switch to the stats window, and clear all stats by reading. */
	outw(StatsDisable, ioaddr + EL3_CMD);
	EL3WINDOW(6);
	for (i = 0; i < 9; i++)
		inb(ioaddr + i);
	inw(ioaddr + 10);
	inw(ioaddr + 12);

	/* Switch to register set 1 for normal use. */
	EL3WINDOW(1);

	/* Accept b-case and phys addr only. */
	outw(SetRxFilter | RxStation | RxBroadcast, ioaddr + EL3_CMD);
	outw(StatsEnable, ioaddr + EL3_CMD); /* Turn on statistics. */

	outw(RxEnable, ioaddr + EL3_CMD); /* Enable the receiver. */
	outw(TxEnable, ioaddr + EL3_CMD); /* Enable transmitter. */
	/* Allow status bits to be seen. */
	outw(SetStatusEnb | 0xff, ioaddr + EL3_CMD);
	/* Ack all pending events, and set active indicator mask. */
	outw(AckIntr | IntLatch | TxAvailable | RxEarly | IntReq,
		 ioaddr + EL3_CMD);
	outw(SetIntrEnb | IntLatch|TxAvailable|TxComplete|RxComplete|StatsFull,
		 ioaddr + EL3_CMD);

	netif_start_queue(dev);
}