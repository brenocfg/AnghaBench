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
struct TYPE_2__ {int /*<<< orphan*/  tx_errors; } ;
struct net_device {int base_addr; TYPE_1__ stats; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ EL3_CMD ; 
 scalar_t__ EL3_STATUS ; 
 scalar_t__ TX_FREE ; 
 scalar_t__ TX_STATUS ; 
 int /*<<< orphan*/  TxEnable ; 
 int /*<<< orphan*/  TxReset ; 
 int /*<<< orphan*/  inb (scalar_t__) ; 
 int /*<<< orphan*/  inw (scalar_t__) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
el3_tx_timeout (struct net_device *dev)
{
	int ioaddr = dev->base_addr;

	/* Transmitter timeout, serious problems. */
	pr_warn("%s: transmit timed out, Tx_status %2.2x status %4.4x Tx FIFO room %d\n",
		dev->name, inb(ioaddr + TX_STATUS), inw(ioaddr + EL3_STATUS),
		inw(ioaddr + TX_FREE));
	dev->stats.tx_errors++;
	netif_trans_update(dev); /* prevent tx timeout */
	/* Issue TX_RESET and TX_START commands. */
	outw(TxReset, ioaddr + EL3_CMD);
	outw(TxEnable, ioaddr + EL3_CMD);
	netif_wake_queue(dev);
}