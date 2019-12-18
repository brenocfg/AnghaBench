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
struct net_device {unsigned int base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL3WINDOW (int) ; 
 unsigned int EL3_STATUS ; 
 unsigned int RxStatus ; 
 unsigned int TxFree ; 
 scalar_t__ TxStatus ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 
 int /*<<< orphan*/  inw (unsigned int) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dump_status(struct net_device *dev)
{
	unsigned int ioaddr = dev->base_addr;
	EL3WINDOW(1);
	netdev_info(dev, "  irq status %04x, rx status %04x, tx status %02x, tx free %04x\n",
		    inw(ioaddr+EL3_STATUS),
		    inw(ioaddr+RxStatus), inb(ioaddr+TxStatus),
		    inw(ioaddr+TxFree));
	EL3WINDOW(4);
	netdev_info(dev, "  diagnostics: fifo %04x net %04x ethernet %04x media %04x\n",
		    inw(ioaddr+0x04), inw(ioaddr+0x06),
		    inw(ioaddr+0x08), inw(ioaddr+0x0a));
	EL3WINDOW(1);
}