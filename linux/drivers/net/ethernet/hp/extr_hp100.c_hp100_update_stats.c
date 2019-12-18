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
typedef  int u_short ;
struct TYPE_2__ {int rx_errors; int rx_over_errors; int rx_crc_errors; int tx_errors; int tx_aborted_errors; } ;
struct net_device {int base_addr; TYPE_1__ stats; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABORT ; 
 int /*<<< orphan*/  CRC ; 
 int /*<<< orphan*/  DROPPED ; 
 int /*<<< orphan*/  MAC_CTRL ; 
 int /*<<< orphan*/  PERFORMANCE ; 
 int /*<<< orphan*/  TRACE ; 
 int hp100_inb (int /*<<< orphan*/ ) ; 
 int hp100_inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_outw (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hp100_update_stats(struct net_device *dev)
{
	int ioaddr = dev->base_addr;
	u_short val;

#ifdef HP100_DEBUG_B
	hp100_outw(0x4216, TRACE);
	printk("hp100: %s: update-stats\n", dev->name);
#endif

	/* Note: Statistics counters clear when read. */
	hp100_page(MAC_CTRL);
	val = hp100_inw(DROPPED) & 0x0fff;
	dev->stats.rx_errors += val;
	dev->stats.rx_over_errors += val;
	val = hp100_inb(CRC);
	dev->stats.rx_errors += val;
	dev->stats.rx_crc_errors += val;
	val = hp100_inb(ABORT);
	dev->stats.tx_errors += val;
	dev->stats.tx_aborted_errors += val;
	hp100_page(PERFORMANCE);
}