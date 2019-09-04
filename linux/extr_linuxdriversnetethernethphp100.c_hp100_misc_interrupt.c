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
struct TYPE_2__ {int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  rx_errors; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */

__attribute__((used)) static void hp100_misc_interrupt(struct net_device *dev)
{
#ifdef HP100_DEBUG_B
	int ioaddr = dev->base_addr;
#endif

#ifdef HP100_DEBUG_B
	int ioaddr = dev->base_addr;
	hp100_outw(0x4216, TRACE);
	printk("hp100: %s: misc_interrupt\n", dev->name);
#endif

	/* Note: Statistics counters clear when read. */
	dev->stats.rx_errors++;
	dev->stats.tx_errors++;
}