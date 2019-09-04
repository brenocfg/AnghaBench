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
struct TYPE_2__ {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  rx_fifo_errors; int /*<<< orphan*/  tx_window_errors; int /*<<< orphan*/  collisions; int /*<<< orphan*/  tx_heartbeat_errors; int /*<<< orphan*/  tx_carrier_errors; } ;
struct net_device {int base_addr; TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL3WINDOW (int) ; 
 scalar_t__ EL3_CMD ; 
 int /*<<< orphan*/  StatsDisable ; 
 int /*<<< orphan*/  StatsEnable ; 
 int el3_debug ; 
 scalar_t__ inb (int) ; 
 int /*<<< orphan*/  inw (int) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static void update_stats(struct net_device *dev)
{
	int ioaddr = dev->base_addr;

	if (el3_debug > 5)
		pr_debug("   Updating the statistics.\n");
	/* Turn off statistics updates while reading. */
	outw(StatsDisable, ioaddr + EL3_CMD);
	/* Switch to the stats window, and read everything. */
	EL3WINDOW(6);
	dev->stats.tx_carrier_errors 	+= inb(ioaddr + 0);
	dev->stats.tx_heartbeat_errors	+= inb(ioaddr + 1);
	/* Multiple collisions. */	   inb(ioaddr + 2);
	dev->stats.collisions		+= inb(ioaddr + 3);
	dev->stats.tx_window_errors	+= inb(ioaddr + 4);
	dev->stats.rx_fifo_errors	+= inb(ioaddr + 5);
	dev->stats.tx_packets		+= inb(ioaddr + 6);
	/* Rx packets	*/		   inb(ioaddr + 7);
	/* Tx deferrals */		   inb(ioaddr + 8);
	inw(ioaddr + 10);	/* Total Rx and Tx octets. */
	inw(ioaddr + 12);

	/* Back to window 1, and turn statistics back on. */
	EL3WINDOW(1);
	outw(StatsEnable, ioaddr + EL3_CMD);
}