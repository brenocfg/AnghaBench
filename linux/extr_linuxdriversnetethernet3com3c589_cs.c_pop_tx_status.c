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
typedef  int u_char ;
struct TYPE_2__ {int /*<<< orphan*/  tx_aborted_errors; } ;
struct net_device {unsigned int base_addr; TYPE_1__ stats; } ;

/* Variables and functions */
 scalar_t__ EL3_CMD ; 
 scalar_t__ TX_STATUS ; 
 int /*<<< orphan*/  TxEnable ; 
 int /*<<< orphan*/  TxReset ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tc589_wait_for_completion (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pop_tx_status(struct net_device *dev)
{
	unsigned int ioaddr = dev->base_addr;
	int i;

	/* Clear the Tx status stack. */
	for (i = 32; i > 0; i--) {
		u_char tx_status = inb(ioaddr + TX_STATUS);
		if (!(tx_status & 0x84))
			break;
		/* reset transmitter on jabber error or underrun */
		if (tx_status & 0x30)
			tc589_wait_for_completion(dev, TxReset);
		if (tx_status & 0x38) {
			netdev_dbg(dev, "transmit error: status 0x%02x\n", tx_status);
			outw(TxEnable, ioaddr + EL3_CMD);
			dev->stats.tx_aborted_errors++;
		}
		outb(0x00, ioaddr + TX_STATUS); /* Pop the status stack. */
	}
}