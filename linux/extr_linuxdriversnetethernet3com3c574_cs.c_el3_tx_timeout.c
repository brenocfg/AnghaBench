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
struct net_device {unsigned int base_addr; TYPE_1__ stats; } ;

/* Variables and functions */
 scalar_t__ EL3_CMD ; 
 int /*<<< orphan*/  TxEnable ; 
 int /*<<< orphan*/  TxReset ; 
 int /*<<< orphan*/  dump_status (struct net_device*) ; 
 int /*<<< orphan*/  netdev_notice (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tc574_wait_for_completion (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void el3_tx_timeout(struct net_device *dev)
{
	unsigned int ioaddr = dev->base_addr;
	
	netdev_notice(dev, "Transmit timed out!\n");
	dump_status(dev);
	dev->stats.tx_errors++;
	netif_trans_update(dev); /* prevent tx timeout */
	/* Issue TX_RESET and TX_START commands. */
	tc574_wait_for_completion(dev, TxReset);
	outw(TxEnable, ioaddr + EL3_CMD);
	netif_wake_queue(dev);
}