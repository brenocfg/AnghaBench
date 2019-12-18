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
struct TYPE_2__ {int /*<<< orphan*/  tx_window_errors; int /*<<< orphan*/  tx_heartbeat_errors; int /*<<< orphan*/  tx_carrier_errors; int /*<<< orphan*/  tx_errors; } ;
struct net_device {long base_addr; TYPE_1__ stats; } ;

/* Variables and functions */
 scalar_t__ EN0_TSR ; 
 unsigned char ENTSR_ABT ; 
 unsigned char ENTSR_CDH ; 
 unsigned char ENTSR_CRS ; 
 unsigned char ENTSR_FU ; 
 unsigned char ENTSR_ND ; 
 unsigned char ENTSR_OWC ; 
 int /*<<< orphan*/  ei_tx_intr (struct net_device*) ; 
 unsigned char inb_p (scalar_t__) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,unsigned char) ; 
 int /*<<< orphan*/  pr_cont (char*) ; 

__attribute__((used)) static void ei_tx_err(struct net_device *dev)
{
	long e8390_base = dev->base_addr;
	unsigned char txsr = inb_p(e8390_base+EN0_TSR);
	unsigned char tx_was_aborted = txsr & (ENTSR_ABT+ENTSR_FU);

#ifdef VERBOSE_ERROR_DUMP
	netdev_dbg(dev, "transmitter error (%#2x):", txsr);
	if (txsr & ENTSR_ABT)
		pr_cont(" excess-collisions");
	if (txsr & ENTSR_ND)
		pr_cont(" non-deferral");
	if (txsr & ENTSR_CRS)
		pr_cont(" lost-carrier");
	if (txsr & ENTSR_FU)
		pr_cont(" FIFO-underrun");
	if (txsr & ENTSR_CDH)
		pr_cont(" lost-heartbeat");
	pr_cont("\n");
#endif

	if (tx_was_aborted)
		ei_tx_intr(dev);
	else 
	{
		dev->stats.tx_errors++;
		if (txsr & ENTSR_CRS) dev->stats.tx_carrier_errors++;
		if (txsr & ENTSR_CDH) dev->stats.tx_heartbeat_errors++;
		if (txsr & ENTSR_OWC) dev->stats.tx_window_errors++;
	}
}